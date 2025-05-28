#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "led.h"

#define RED_PIN 11
#define GREEN_PIN 12
#define BLUE_PIN 13

static void pwm_setup(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice, 255);
    pwm_set_enabled(slice, true);
}

void led_init() {
    pwm_setup(RED_PIN);
    pwm_setup(GREEN_PIN);
    pwm_setup(BLUE_PIN);
}

void led_set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    pwm_set_gpio_level(RED_PIN, r);
    pwm_set_gpio_level(GREEN_PIN, g);
    pwm_set_gpio_level(BLUE_PIN, b);
}