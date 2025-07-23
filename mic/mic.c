#include "pico/stdlib.h"  // SDK padrão do Pico
#include "hardware/adc.h" // Funções do Conversor Analógico-Digital (ADC)
#include "mic.h"          // Header deste módulo de microfone
#include "utils/utils.h"



#define MIC_ADC_CHANNEL 2  // Canal ADC(GP28 = ADC2)
#define ALPHA 0.3f // Fator de suavização exponencial

// Inicializa o ADC para leitura do microfone
void mic_init() {
    adc_init();                // Inicializa o periférico ADC
    adc_gpio_init(28);         // Habilita ADC no GPIO28
    adc_select_input(MIC_ADC_CHANNEL); // Seleciona o canal ADC para leitura
}

// Lê o nível de som medindo a amplitude pico a pico do sinal.
// O valor retornando é um representação do volume, não um dB real.

float mic_get_level() {
    const int samples = 100;    //Um número maior de amostras para capturar a onda
    uint16_t max_val = 0;
    uint16_t min_val = 4095;

    for (int i = 0; i < samples; i++) {
        uint16_t reading = adc_read();
        if (reading > max_val) max_val = reading;
        if (reading < min_val) min_val = reading;
    }

    //calcula a amplitude pico a pico
    float amplitude = max_val - min_val;

    //Suavização simples para estabilizar a leitura
    static float last_amplitude = 0.0f;
    amplitude = (1.0f - ALPHA) * last_amplitude + ALPHA * amplitude;
    last_amplitude = amplitude;

    //Retorna a amplitude (escala de 0 a 4095)
    //Esse valor será usado para comparação

    return amplitude;
    
}