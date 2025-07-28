#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "mic/mic.h"
#include "led/led.h"
#include "utils/utils.h"
#include "matriz/matriz.h"

int main() {
    stdio_init_all();
    mic_init();
    inicializar_matriz();

    limpar_matriz();
    renderizar();

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

        int qtd_leds_acessos = 0;

        absolute_time_t current_time = get_absolute_time();
        if (absolute_time_diff_us(last_print_time, current_time) > print_interval_us) {
            printf("Nível: %.2f\n", sound_level);
            fflush(stdout);
            last_print_time = current_time;
        }
        // Acumulador e média de 20 amostras
        soma += sound_level;
        contador++;
        float media;

        if (contador == 5) {
            media = soma / 5.0f;
            printf("[20 amostras] Média de Nível: %.2f\n", media);
            fflush(stdout);
            soma = 0.0f;
            contador = 0;
        }

        if (LIMITE_SOM_ALTO > LIMITE_SOM_BAIXO)
        {
            qtd_leds_acessos = ((media - LIMITE_SOM_BAIXO) / (LIMITE_SOM_ALTO - LIMITE_SOM_BAIXO) * QTD_LEDS);
        }
        
        if (qtd_leds_acessos > QTD_LEDS)
        {
            qtd_leds_acessos = QTD_LEDS;
        }

        if (qtd_leds_acessos < 0)
        {
            qtd_leds_acessos = 0;
        }

        atualizar_ledbar(qtd_leds_acessos);
        renderizar();

        sleep_ms(300); // 300 ms entre leituras — OK se deseja menos frequência
    }

    return 0;
}
