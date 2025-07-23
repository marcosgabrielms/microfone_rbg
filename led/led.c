#include "pico/stdlib.h"  // SDK padrão do Pico
#include "hardware/pwm.h" // Funções de PWM
#include "led.h"          // Header deste módulo de LED

 // Pinos GPIO para os componentes R, G, B do LED
#define RED_PIN 11
#define GREEN_PIN 12
#define BLUE_PIN 13

 // Configura o PWM para um pino específico
static void pwm_setup(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);      // Define o pino para operar como PWM
    uint slice = pwm_gpio_to_slice_num(pin);    // Obtém o "slice" (unidade PWM) do pino
    pwm_set_wrap(slice, 150);                   // Define o valor máximo do contador PWM (resolução 0-255)
    pwm_set_enabled(slice, true);               // Ativa o PWM para este slice
}

 // Inicializa os pinos do LED RGB para controle PWM
void led_init() {
    pwm_setup(RED_PIN);   // Configura PWM para o pino Vermelho
    pwm_setup(GREEN_PIN); // Configura PWM para o pino Verde
    pwm_setup(BLUE_PIN);  // Configura PWM para o pino Azul
}

 // Define a cor do LED RGB
 // r, g, b: Intensidade para cada cor (0-255)
void led_set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    pwm_set_gpio_level(RED_PIN, r);   // Define intensidade do Vermelho (0=apagado, 255=máximo)
    pwm_set_gpio_level(GREEN_PIN, g); // Define intensidade do Verde
    pwm_set_gpio_level(BLUE_PIN, b);  // Define intensidade do Azul
}