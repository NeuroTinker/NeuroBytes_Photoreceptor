#ifndef HAL_H_
#define HAL_H_

#define PORT_LED_LIGHT	GPIOB
#define PIN_LED_LIGHT	GPIO0

#define PORT_LED_DARK	GPIOA
#define PIN_LED_DARK	GPIO5

#define PORT_LIGHT_OUT	GPIOB
#define PIN_LIGHT_OUT	GPIO1

#define PORT_DARK_OUT	GPIOA
#define PIN_DARK_OUT	GPIO4

#define PORT_BUTTONS	GPIOA
#define PIN_SPAN		GPIO2
#define PIN_ZERO		GPIO3

#define PORT_SENSE		GPIOA
#define PIN_SENSE		GPIO1

extern volatile uint8_t tick;

void systick_setup(int freq);
void clock_setup(void);
void gpio_setup(void);
void tim_setup(void);
void adc_setup(void);
void setLED(uint8_t led, uint16_t val);
uint8_t readButton(uint8_t button);

#endif
