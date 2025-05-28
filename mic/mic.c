#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "mic.h"
#include <math.h>

#define MIC_ADC_CHANNEL 2 //GP28 NA BITDOGLAB

void mic_init() {
    adc_init();
    adc_gpio_init(28);
    adc_select_input(MIC_ADC_CHANNEL);
}

float mic_read_db() {
    const int samples = 100;
    uint32_t sum = 0;
    for (int i = 0; i < samples; i++){
        sum += adc_read();
        sleep_us(100);
    }
    float average = sum / (float)samples;

    float voltage = average * 3.3f / 4095.0f;

    float db = (voltage - 0.5f) * 100.0f + 60.0f;
    return db; 
}