#include "pico/stdlib.h"  // SDK padrão do Pico
#include "hardware/adc.h" // Funções do Conversor Analógico-Digital (ADC)
#include "mic.h"          // Header deste módulo de microfone
#include <math.h>         // Funções matemáticas (não usado diretamente aqui, mas incluído)

// Define o canal ADC para o microfone. GP28 é ADC2.
#define MIC_ADC_CHANNEL 2

// Inicializa o ADC para leitura do microfone
void mic_init() {
    adc_init();                // Inicializa o periférico ADC
    adc_gpio_init(28);         // Habilita ADC no GPIO28
    adc_select_input(MIC_ADC_CHANNEL); // Seleciona o canal ADC para leitura
}

// Lê o nível de som do microfone e tenta converter para uma escala dB (simplificada)
float mic_read_db() {
    const int samples = 100; // Número de amostras para média
    uint32_t sum = 0;        // Soma das leituras ADC

    // Coleta e soma múltiplas amostras ADC
    for (int i = 0; i < samples; i++) {
        sum += adc_read(); // Lê o valor do ADC (0-4095)
        sleep_us(100);     // Pequena pausa entre leituras
    }
    float average = sum / (float)samples; // Calcula a média das amostras

    // Converte a média ADC para tensão (0-3.3V)
    float voltage = average * 3.3f / 4095.0f;

    // Fórmula empírica/simplificada para estimar dB.
    // Assume um offset DC de ~0.5V e mapeia a variação para uma faixa de dB.
    // O resultado NÃO é um valor dB SPL padrão, mas uma representação relativa.
    // Valores (0.5V, 100.0, 60.0) podem precisar de ajuste para seu microfone específico.
    float db = (voltage - 0.5f) * 100.0f + 60.0f;
    return db;
}