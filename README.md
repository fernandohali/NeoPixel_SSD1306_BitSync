# NeoPixel_SSD1306_BitSync - Comunicação Serial no RP2040

## Componentes Utilizados
- **Placa BitDogLab** (RP2040)
- **Matriz 5x5 de LEDs WS2812** (GPIO 7)
- **LED RGB** (GPIOs 11, 12 e 13)
- **Botão A** (GPIO 5)
- **Botão B** (GPIO 6)
- **Display OLED SSD1306** via I2C (GPIOs 14 e 15)

## Funcionalidades Implementadas

### 1. Modificação da Biblioteca `font.h`
- Adição de caracteres minúsculos personalizados para exibição no display OLED.

### 2. Entrada de Caracteres via Serial Monitor
- O usuário pode digitar caracteres no **Serial Monitor do VS Code**.
- Cada caractere digitado é exibido no display SSD1306.
- Caso um número de **0 a 9** seja digitado, um símbolo correspondente ao número será mostrado na matriz de LEDs WS2812.

### 3. Interação com os Botões
#### **Botão A (GPIO 5)**
- Alterna o estado do LED **Verde** (ligado/desligado).
- Atualiza o display SSD1306 com uma mensagem informativa.
- Envia uma mensagem descritiva para o Serial Monitor.

#### **Botão B (GPIO 6)**
- Alterna o estado do LED **Azul** (ligado/desligado).
- Atualiza o display SSD1306 com uma mensagem informativa.
- Envia uma mensagem descritiva para o Serial Monitor.

## Requisitos Técnicos
- **Uso de interrupções (IRQ):** Os botões são tratados por meio de interrupções para garantir respostas rápidas e precisas.
- **Debouncing via Software:** Implementado para evitar múltiplas leituras de um único pressionamento de botão.
- **Controle de LEDs:** O projeto utiliza tanto LEDs comuns quanto LEDs endereçáveis WS2812.
- **Uso do protocolo I2C:** Comunicação entre o RP2040 e o display SSD1306.
- **Envio de dados via UART:** Comunicação serial para interação do usuário.
- **Código estruturado e comentado:** O código segue boas práticas de programação, facilitando o entendimento e manutenção.

## Demonstração
Um vídeo de demonstração do funcionamento do projeto pode ser acessado no seguinte link:
[📹 Vídeo do Projeto](https://www.dropbox.com/scl/fi/m7btelmruk2fhl3sj3vgu/Video_NeoPixel_SSD1306_BitSync-Feito-com-o-Clipchamp.mp4?rlkey=2fza01g7vu6lwoybjwggu22vx&st=sg9omlcu&dl=0)

## Como Executar o Projeto
1. **Clone o repositório** ou baixe os arquivos do projeto.
2. **Abra o código no VS Code** e configure o ambiente para o RP2040.
3. **Conecte a placa BitDogLab** ao computador via USB.
4. **Compile e carregue o código** para a placa.
5. **Abra o Serial Monitor** para interagir com o sistema.

## Estrutura do Repositório
```
📂 Projeto_BitSync
 ├── 📁 src          # Código-fonte do projet
 |    |
 |    |-📁 inc      
 |    | ├── font.h         # Biblioteca de fontes modificada
 |    |
 |    |-📁 led
 |    |-📁 matriz_Numeros
 |    |-📁 display
 |    |-📁 buttons
 |    ├── NeoPixel_SSD1306_BitSync.cpp       # Código principal do projeto
 ├── README.md      # Documentação do projeto
```

## Tecnologias Utilizadas
- **Linguagem:** C/C++
- **Microcontrolador:** RP2040 (BitDogLab)
- **Protocolo de Comunicação:** I2C, UART
- **Ambiente de Desenvolvimento:** VS Code com extensão para RP2040

## Autor
**Fernando Hali Santos Andrade**
