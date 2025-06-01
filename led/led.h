// Evita inclusão múltipla do header
#ifndef LED_H  
#define LED_H

#include <stdint.h> // Para o tipo uint8_t

// Inicializa o hardware do LED RGB
void led_init();

// Define a cor do LED RGB (valores r, g, b: 0-255)
void led_set_rgb(uint8_t r, uint8_t g, uint8_t b);

#endif // LED_H