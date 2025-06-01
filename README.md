# Projeto Microfone RGB com RP2040 (BitDogLab)

Este projeto utiliza um microfone para capturar o nível de som ambiente e um LED RGB para indicar visualmente essa intensidade. Foi desenvolvido para a placa BitDogLab, que utiliza o microcontrolador RP2040.

## ❯ Funcionalidades Principais

* Leitura contínua do nível de som ambiente através de um módulo de microfone conectado ao ADC.
* Cálculo de uma representação simplificada do nível de som em decibéis (dB).
* Exibição do valor de "dB" no monitor serial para depuração e visualização.
* Controle de um LED RGB para mudar de cor com base na intensidade do som detectado:
    * **Azul:** Som baixo (definido no código como < 45.0 na escala dB interna).
    * **Verde:** Som moderado (definido no código como <= 75.0 na escala dB interna).
    * **Vermelho:** Som alto (definido no código como > 75.0 na escala dB interna).

## ⚙️ Hardware Utilizado

* Placa BitDogLab (com RP2040)
* Módulo de Microfone (conectado a um pino ADC, especificamente GP28/ADC2 conforme o código)
* LED RGB (conectado aos pinos PWM: GP11 para Vermelho, GP12 para Verde, GP13 para Azul, conforme o código)

## 💡 Como Funciona

O microcontrolador RP2040, através do seu conversor analógico-digital (ADC), lê os valores do sensor de microfone. Esses valores são processados para obter uma média que é então convertida para uma escala arbitrária de decibéis. Com base nessa leitura, o programa principal (`microfone_rgb.c`) atualiza a cor de um LED RGB. As intensidades de cada cor (Vermelho, Verde, Azul) são controladas usando modulação por largura de pulso (PWM). O valor de decibéis também é enviado para o monitor serial.

## 📁 Estrutura do Código

O projeto é organizado em alguns módulos para melhor clareza:

* `microfone_rgb.c`: Arquivo principal com a lógica do programa (`main`).
* `mic/`: Contém os arquivos `mic.c` e `mic.h` para as funcionalidades do microfone (inicialização e leitura).
* `led/`: Contém os arquivos `led.c` e `led.h` para as funcionalidades do LED RGB (inicialização e controle de cor via PWM).
* `utils/`: Contém arquivos de utilidades `utils.c` e `utils.h` (atualmente com estrutura básica).
* `CMakeLists.txt`: Arquivo de configuração para compilação do projeto com CMake.
* `.vscode/`: Contém configurações específicas para o ambiente de desenvolvimento Visual Studio Code (tasks, launch, settings).

## 🚀 Como Compilar e Usar

Este projeto é configurado para ser compilado usando o SDK do Raspberry Pi Pico e CMake.

1.  **Configurar o Ambiente:**
    * Certifique-se de ter o [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) instalado e configurado corretamente no seu sistema.
    * As ferramentas de compilação (como ARM GCC Compiler, CMake, Ninja) também devem estar instaladas e no PATH do sistema. O arquivo `CMakeLists.txt` e as configurações do VSCode neste repositório já apontam para um ambiente Pico SDK configurado.

2.  **Compilar o Projeto:**
    * Crie um diretório `build` dentro da pasta do projeto.
    * Navegue até o diretório `build` e execute `cmake ..`
    * Em seguida, execute `ninja` (ou `make`, dependendo do seu gerador CMake).
    * Se estiver usando VS Code com as extensões recomendadas (`raspberry-pi.raspberry-pi-pico`), você pode usar as tasks de build configuradas.

3.  **Carregar na BitDogLab:**
    * Conecte sua placa BitDogLab ao computador enquanto pressiona o botão BOOTSEL.
    * A placa será montada como um dispositivo de armazenamento em massa.
    * Arraste o arquivo `.uf2` gerado no diretório `build` para a placa.
    * Alternativamente, use `picotool load seu_programa.uf2 -fx` se tiver o picotool configurado.

4.  **Visualizar a Saída:**
    * Abra um monitor serial conectado à porta USB da BitDogLab (configurado para 115200 baud) para ver as leituras de "Decibéis".

---
