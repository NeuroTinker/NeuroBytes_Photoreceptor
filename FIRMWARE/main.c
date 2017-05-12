#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/adc.h>


#include "comm.h"
#include "HAL.h"

#define MAX_FIRE_TIME	5000 // 1000 ms
#define	MIN_FIRE_TIME	1000	 // 200 ms
#define FIRE_TIME_RANGE	6000 // 1200 ms

#define BLINK_TIME			100
#define DATA_TIME			10
#define DEND_PING_TIME		3000 // 1000 ms
#define	NID_PING_TIME		5000 // 1000 ms
#define SEND_PING_TIME		2000
#define BUTTON_PRESS_TIME	2

int temp, output;

int scale10bit(int val, int zero, int span) 
{
	/*	Scales input based on zero and span calibration points. Returns unsigned
		10-bit integer as output (i.e. 0-1023). */

	if (zero < span) 
	{
		if ((val > zero) && (val < span))
		{
			return ((val - zero) * 1023) / (span - zero);
		}
		else if (val <= zero)
		{
			return 0;
		}
		else 
		{
			return 1023;
		}
	}
	else 
	{
		return val;
	}
}


int main(void)
{
	int dark_fire_time = 0;
	int light_fire_time = 0;
	int fire_time = 0;

	int zero = 450;
	int span = 1450;

	uint16_t	send_ping_time = 0;

	clock_setup();
	gpio_setup();
	tim_setup();
	adc_setup();
	systick_setup(100000); // tick @ 0.1 ms
	
	for(;;)
	{
		if (main_tick == 1){
			//gpio_toggle(PORT_LIGHT_OUT, PIN_LIGHT_EX);
			main_tick = 0;

			adc_start_conversion_regular(ADC1);
			while (!(adc_eoc(ADC1)));
			temp = adc_read_regular(ADC1);

			if (readButton(0) > 0)
			{
				zero = temp;
			}

			if (readButton(1) > 0)
			{
				span = temp;
			}

			output = scale10bit(temp, zero, span);

			if (dark_fire_time == 0){
				dark_fire_time = MIN_FIRE_TIME + ((FIRE_TIME_RANGE * output) / 1023);
				addWrite(DOWNSTREAM_BUFF, PULSE_MESSAGE);
				downstream_port[downstream_port_i] = 1;
				downstream_port_i += 1;
			} else {
				dark_fire_time -= 1;
			}

			if (light_fire_time == 0){
				light_fire_time = MIN_FIRE_TIME + ((FIRE_TIME_RANGE * (1023-output)) / 1023);
				addWrite(DOWNSTREAM_BUFF, PULSE_MESSAGE);
				downstream_port[downstream_port_i] = 2;
				downstream_port_i += 1;
			} else {
				light_fire_time -= 1;
			}

			setLED(0, 1023 - output); // dark led
			setLED(1, output); // light led
		

			if (nid_ping_time == 0){
				nid_keep_alive = NID_PING_KEEP_ALIVE;
				nid_pin = 0;
				nid_pin_out = 0;
			}else {
				nid_ping_time -= 1;
			}
				
			if (send_ping_time++ > SEND_PING_TIME){
				addWrite(DOWNSTREAM_BUFF, DEND_PING);
				downstream_port[downstream_port_i] = 3;
				downstream_port_i += 1;
				send_ping_time = 0;
			}

			// TODO: add identify button functionality
			/*
			if (nid_channel != 0){
				if (data_time++ > DATA_TIME){
					data_time = 0;
					//message = DATA_MESSAGE | (nid_channel << 19) | (uint16_t) neuron.potential | (nid_keep_alive << 22);
					message = DATA_MESSAGE | (uint16_t) output | (nid_channel << 19) | (nid_keep_alive << 22);
					addWrite(NID_BUFF,message);
				}
			}

			if (blink_flag != 0){
				setLED(0, 1023);
				setLED(1, 1023);
				blink_time = 1;
				blink_flag = 0;
			} else if (blink_time > 0){
				if (++blink_time == BLINK_TIME){
					blink_time = 0;
				}
			}
			*/

		}
	}
}
