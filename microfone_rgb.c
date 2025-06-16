#include <stdio.h>          // Para printf (saída padrão)
#include "pico/stdlib.h"    // Biblioteca padrão do Pico (essencial)
#include "mic/mic.h"        // Funções do módulo de microfone
#include "led/led.h"        // Funções do módulo de LED RGB
#include "utils/utils.h"    // Funções utilitárias (se houver)

int main() {
    stdio_init_all(); // Inicializa a comunicação serial/USB para printf
    mic_init();       // Inicializa o microfone
    led_init();       // Inicializa o LED RGB

    while (true) { // Loop principal infinito
        float db = mic_read_db(); // Lê o nível de som (em uma escala tipo dB)
        printf("Decibéis: %.2f dB\n", db); // Imprime o valor lido

        // Define a cor do LED com base no nível de som
        if (db < LIMITE_DB_BAIXO) {
            led_set_rgb(0, 255, 0); // Azul para som baixo
        } else if (db < LIMITE_DB_ALTO) {
            led_set_rgb(255, 0, 0); // Verde para som moderado
        } else {
            led_set_rgb(0, 0,255); // Vermelho para som alto
        }
        sleep_ms(300); // Aguarda 300 milissegundos antes da próxima leitura
    }
    
    return 0; 
}