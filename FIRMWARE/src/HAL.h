#ifndef HAL_H_
#define HAL_H_

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/adc.h>
//#include <libopencm3/stm32/flash_common_f234.h>


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

#define EEPROM_ADDRESS  0x08080000 // 0x08000080 & 0x08080000
#define SPAN_ADDRESS    EEPROM_ADDRESS + 0x20
#define ZERO_ADDRESS    EEPROM_ADDRESS + 0x00
#define FLASH_PRGKEY1   0x8C9DAEBF
#define FLASH_PRGKEY2   0x13141516
#define FLASH_PRGKEYR   0x10
#define FLASH_PEKEY1    0x89ABCDEF
#define FLASH_PEKEY2    0x02030405
#define FLASH_PEKEYR    0x0C

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
void eepromProgram(uint32_t address, uint32_t data);
uint32_t eepromRead(uint32_t address);

#endif
