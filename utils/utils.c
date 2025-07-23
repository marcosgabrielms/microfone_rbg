#include "utils.h"       // Inclui funções utilitárias do projeto.
#include "mic/mic.h"     // Inclui funções e definições do módulo de microfone.
#include "pico/stdlib.h" // Inclui a biblioteca padrão do Raspberry Pi Pico (funções básicas).
#include <stdio.h>


float LIMITE_SOM_BAIXO = 500.0f;
float LIMITE_SOM_ALTO = 1000.0f;

void calibrar_limites_automaticamente(int duracao_ms) {
    const int intervalo_ms = 100;
    int num_amostras = duracao_ms / intervalo_ms;
    float soma = 0.0f;

    printf("Calibrando ruído ambiente por %d ms...\n", duracao_ms);
    for (int i = 0; i < num_amostras; i++) {
        float nivel = mic_get_level();
        soma += nivel;
        sleep_ms(intervalo_ms);
    }

    float media = soma / num_amostras;
    LIMITE_SOM_BAIXO = media + 30.0f;
    LIMITE_SOM_ALTO = media + 80.0f;

    printf("Calibração concluída!\n");
    printf("Média ambiente: %.2f\n", media);
    printf("Novo LIMITE_SOM_BAIXO: %.2f\n", LIMITE_SOM_BAIXO);
    printf("Novo LIMITE_SOM_ALTO: %.2f\n", LIMITE_SOM_ALTO);

}