#include <stdio.h>
#include "pico/stdlib.h"
#include "mic/mic.h"
#include "led/led.h"
#include "utils/utils.h"

int main() {
    stdio_init_all();
    mic_init();
    led_init();

    while (true) {
        float db = mic_read_db();
        printf("Decibéis: %.2f dB\n", db);
        
        if (db < 45.0f) {
            led_set_rgb(0, 0, 255); // Azul - Som baixo
        } else if (db <= 75.0f) {
            led_set_rgb(0, 255, 0); // Verde - Som moderado
        } else {
            led_set_rgb(255, 0, 0); // Vermelho - Som alto
        }
        sleep_ms(300);
    }
}