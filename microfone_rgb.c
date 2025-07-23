#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "mic/mic.h"
#include "led/led.h"
#include "utils/utils.h"

typedef enum {
    NIVEL_BAIXO,
    NIVEL_MEDIO,
    NIVEL_ALTO
} NivelSom;

int main() {
    stdio_init_all();
    mic_init();
    led_init();

    sleep_ms(1000);
    calibrar_limites_automaticamente(10000);

    sleep_ms(500);

    absolute_time_t last_print_time = get_absolute_time();
    const int64_t print_interval_us = 200000;
    float soma = 0.0f;
    int contador = 0;

    printf("--- Iniciando detecção ---\n");
    fflush(stdout);

    while (1) {
        float sound_level = mic_get_level();

        NivelSom nivel;

        if (sound_level >= LIMITE_SOM_ALTO)
            nivel = NIVEL_ALTO;
        else if (sound_level >= LIMITE_SOM_BAIXO)
            nivel = NIVEL_MEDIO;
        else
            nivel = NIVEL_BAIXO;

        switch (nivel) {
            case NIVEL_ALTO:
                led_set_rgb(0, 0, 150);
                break;
            case NIVEL_MEDIO:
                led_set_rgb(0, 150, 0);
                break;
            case NIVEL_BAIXO:
                led_set_rgb(150, 0, 0);
                break;
        }

        absolute_time_t current_time = get_absolute_time();
        if (absolute_time_diff_us(last_print_time, current_time) > print_interval_us) {
            printf("Nível: %.2f\n", sound_level);
            fflush(stdout);
            last_print_time = current_time;
        }
        // Acumulador e média de 20 amostras
        soma += sound_level;
        contador++;

        if (contador == 20) {
            float media = soma / 20.0f;
            printf("[20 amostras] Média de Nível: %.2f\n", media);
            fflush(stdout);
            soma = 0.0f;
            contador = 0;
        }

        sleep_ms(300); // 300 ms entre leituras — OK se deseja menos frequência
    }

    return 0;
}
