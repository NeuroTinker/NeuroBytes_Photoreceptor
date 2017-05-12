#ifndef HAL_H_
#define HAL_H_

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/adc.h>


#include "comm.h"

#define PORT_LED_LIGHT	GPIOB
#define PIN_LED_LIGHT	GPIO7

#define PORT_LED_DARK	GPIOA
#define PIN_LED_DARK	GPIO2

#define PORT_LIGHT_OUT	GPIOC
#define PIN_LIGHT_EX	GPIO15
#define PIN_LIGHT_IN	GPIO14

#define PORT_DARK_OUT	GPIOA
#define PIN_DARK_EX	    GPIO1
#define PIN_DARK_IN	    GPIO0

#define PORT_SPAN		GPIOB
#define PIN_SPAN		GPIO0

#define PORT_ZERO		GPIOA
#define PIN_ZERO		GPIO10

#define PORT_SENSE		GPIOB
#define PIN_SENSE		GPIO1

extern volatile uint8_t tick;
extern volatile uint8_t main_tick;

void systick_setup(int freq);
void clock_setup(void);
void gpio_setup(void);
void tim_setup(void);
void adc_setup(void);
void setLED(uint8_t led, uint16_t val);
void setAsInput(uint32_t port, uint32_t pin);
void setAsOutput(uint32_t port, uint32_t pin);
uint8_t readButton(uint8_t button);

#endif
