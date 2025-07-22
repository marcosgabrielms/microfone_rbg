// Evita inclusão múltipla deste header
#ifndef MIC_H      
#define MIC_H

//Novos limites baseados na amplitude (0 a 4095).
//Esses valores são apenas para testes, necessitando ajustá-los.

#define LIMITE_SOM_BAIXO 600.0f
#define LIMITE_SOM_ALTO 1700.0f

void mic_init();
float mic_get_level();

#endif //MIC_H.
