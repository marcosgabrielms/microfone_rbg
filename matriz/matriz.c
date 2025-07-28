#include "matriz.h"


void inicializar_matriz()
{
    ws2812b_init(CANAL_PIO, PINO_MATRIZ, QTD_LEDS);
    ws2812b_set_global_dimming(5);
}

void atualizar_ledbar(int qnt_leds)
{
    const int limite_verde = 10;
    const int limite_amarelo = 20;

    for (int i = 0; i < QTD_LEDS; i++)
    {
        if (i < qnt_leds)
        {
            if (i < limite_verde)
            {
                ws2812b_fill(i, i, GRB_GREEN);
            }
            else if (i < limite_amarelo)
            {
                ws2812b_fill(i, i, GRB_YELLOW);
            }
            else
            {
                ws2812b_fill(i, i, GRB_RED);
            }
        }
        else
        {
            ws2812b_fill(i, i, GRB_BLACK);
        }
    }
}

void renderizar()
{
    ws2812b_render();
}

void limpar_matriz()
{
    ws2812b_clear();
}