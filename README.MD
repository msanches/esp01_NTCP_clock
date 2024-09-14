# Projeto ESP01 com Sensor DHT11 e Tela OLED

Este projeto utiliza o módulo **ESP01**, um sensor **DHT11** e uma tela **OLED** para exibir informações como dia da semana, data completa, hora, temperatura e umidade. A sincronização de data e hora é feita por meio de um servidor NTP, e os dados de temperatura e umidade são obtidos a partir do sensor DHT11.

## Funcionalidades

- Exibição do dia da semana, data e hora sincronizados via servidor NTP.
- Monitoramento de temperatura e umidade ambiente através do sensor DHT11.
- Exibição das informações em uma tela OLED.

## Componentes Utilizados

- **ESP01**
- **Sensor DHT11** (Conectado à porta TX/GPIO1)
- **Tela OLED** (Conectada à GPIO2 (SCL) e GPIO0 (SDA))
- **Resistor de 4.7kΩ** (Conectado entre o pino de 3.3V e o pino de comunicação do DHT11)
- **Resistor de 10kΩ** (Conectado entre o **CH_PD** e **VCC** no ESP01 para mantê-lo ativo)
- **Servidor NTP** para sincronização de data e hora.

## Diagrama de Conexões

- **DHT11**
  - Pino de dados -> TX (GPIO1)
  - **Resistor de 4.7kΩ** -> Entre o pino de 3.3V e o pino de dados
- **OLED**
  - SCL -> GPIO2
  - SDA -> GPIO0
- **ESP01**
  - **CH_PD** -> VCC (via resistor de 10kΩ)

## Requisitos

- Plataforma Arduino IDE com suporte ao ESP8266
- Biblioteca DHT para leitura do sensor DHT11
- Biblioteca para comunicação com a tela OLED (ex: U8g2 ou Adafruit_SSD1306)
- Biblioteca para sincronização com o servidor NTP (ex: NTPClient)

## Instalação

1. Clone este repositório:

   ```bash
   git clone https://github.com/msanches/esp01_NTCP_clock
