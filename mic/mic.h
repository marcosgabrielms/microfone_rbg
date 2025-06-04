// Evita inclusão múltipla deste header
#ifndef MIC_H      
#define MIC_H

#define LIMITE_DB_BAIXO_MODERADO 40.0f
#define LIMITE_DB_MODERADO_ALTO 100.0f

// Inicializa o hardware do microfone (ADC)
void mic_init();

// Lê o nível de som do microfone e retorna uma estimativa em dB
float mic_read_db();

#endif // MIC_H