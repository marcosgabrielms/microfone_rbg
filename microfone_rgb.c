#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "mic/mic.h"
#include "led/led.h"
#include "utils/utils.h"

int main() {
    // 1. Inicialização
    stdio_init_all(); 
    mic_init();       
    led_init();       
    sleep_ms(2000);
    absolute_time_t last_print_time = get_absolute_time();
    const int64_t print_interval_us = 200000;
    printf("--- Lógica de LED e Limites Revisada ---\n");
    fflush(stdout);

    // 2. Loop Principal Infinito
    while (true) {
        float sound_level = mic_get_level();

        // --- Lógica de Decisão Final e Clara ---
        // Este código assume uma fiação PADRÃO (R->Vermelho, G->Verde, B->Azul)

        if (sound_level >= LIMITE_SOM_ALTO) {
            // NÍVEL ALTO: Deve acender o LED Vermelho
            led_set_rgb(0, 0, 255); 
        } 
        else if (sound_level >= LIMITE_SOM_BAIXO) {
            // NÍVEL MÉDIO: Deve acender o LED Verde
            led_set_rgb(255, 0, 0); 
        } 
        else {
            // NÍVEL BAIXO: Deve acender o LED Azul
            led_set_rgb(0, 255, 0); 
        }

        // Lógica de impressão no monitor
        absolute_time_t current_time = get_absolute_time();
        if (absolute_time_diff_us(last_print_time, current_time) > print_interval_us) {
            printf("Nível: %.2f\n", sound_level);
            fflush(stdout);
            last_print_time = current_time;
        }

        sleep_ms(10); 
    }

    return 0; 
}