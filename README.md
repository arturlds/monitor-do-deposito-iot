 Monitor do Depósito — Projeto IoT

Projeto desenvolvido como atividade final da disciplina de Internet das Coisas (IoT), utilizando ESP32 e sensor DHT22 para monitorar a temperatura e a umidade de um ambiente.

O sistema identifica temperaturas acima do limite estabelecido, ativa um alerta visual por meio de um LED e envia os dados coletados para a plataforma ThingSpeak, permitindo o acompanhamento remoto das condições do ambiente.

 Objetivo do projeto

Desenvolver um sistema de monitoramento de temperatura e umidade para um depósito, permitindo identificar situações de temperatura elevada e disponibilizar os dados para acompanhamento remoto.

 Problema que o projeto procura resolver

Em depósitos, o aumento da temperatura pode comprometer produtos e materiais armazenados. Sem um monitoramento constante, uma alteração nas condições do ambiente pode passar despercebida.

O Monitor do Depósito busca reduzir esse problema por meio de leituras periódicas, um alerta local e o envio das informações para uma plataforma em nuvem.

 Componentes utilizados

| Componente | Função |
|---|---|
| ESP32 | Processamento das informações e conexão Wi-Fi. |
| Sensor DHT22 | Medição da temperatura e umidade. |
| LED vermelho | Indicação visual de temperatura elevada. |
| Resistor de 220 Ω | Limitação da corrente do LED. |

 Funcionamento do sistema

O sensor DHT22 realiza a leitura da temperatura e da umidade do ambiente. A ESP32 recebe essas informações, verifica se a leitura é válida e avalia a temperatura em relação ao limite configurado.

Os dados são enviados pela rede Wi-Fi utilizando o protocolo HTTP para a plataforma ThingSpeak, onde podem ser visualizados em gráficos.

 Fluxo de funcionamento

DHT22 → ESP32 → Wi-Fi → HTTP → ThingSpeak

- Percepção: o DHT22 coleta temperatura e umidade.
- Processamento: a ESP32 interpreta os dados e controla o alerta.
- Comunicação: a ESP32 envia os dados pela rede Wi-Fi utilizando HTTP.
- Aplicação: o ThingSpeak recebe e apresenta as informações em gráficos.

 Limite de temperatura e funcionamento do alarme

O limite de temperatura configurado no projeto é de **28 °C**.

- Temperatura normal: o LED permanece desligado.
- Temperatura acima de 28 °C: o LED vermelho é ligado.
- Temperatura abaixo de 27 °C: o LED é desligado.

Foi utilizada uma lógica de histerese, com dois limites diferentes para ligar e desligar o alerta. Isso evita que o LED fique alternando rapidamente quando a temperatura estiver próxima de 28 °C.

O sistema realiza leituras a cada 2 segundos e envia os dados para o ThingSpeak a cada 20 segundos.

 Tecnologias utilizadas

- Linguagem C++ (ambiente Arduino).
- ESP32.
- Sensor DHT22.
- Protocolo HTTP.
- Rede Wi-Fi.
- ThingSpeak.
- Simulador Wokwi.

### Bibliotecas

- `WiFi.h`: conexão da ESP32 à rede Wi-Fi.
- `DHTesp.h`: comunicação com o sensor DHT22.
- `ThingSpeak.h`: envio de informações para a plataforma ThingSpeak.

 Testes realizados

Foram realizados três testes para verificar o comportamento do sistema em diferentes condições de temperatura.

| Teste | Temperatura observada | Resultado |
|---|---|---|
| T1 — Temperatura normal | 24 °C | Alarme desligado. |
| T2 — Temperatura elevada | 29,9 °C e 31 °C | Alarme ligado. |
| T3 — Retorno à normalidade | 21,4 °C, 22,5 °C e 26,7 °C | Alarme desligado. |

### Resultados da comunicação

Durante os testes, o Monitor Serial apresentou respostas HTTP 200, indicando que as requisições foram aceitas pelo ThingSpeak.

A plataforma recebeu quatro registros na captura analisada, apresentando temperaturas próximas de 24 °C a 31 °C e umidade de 40%.

Os testes demonstraram o funcionamento da leitura do sensor, da lógica de acionamento do alarme e da comunicação com a plataforma em nuvem.

 Links do projeto

- Simulação no Wokwi: https://wokwi.com/projects/480074379308578817
- Canal ThingSpeak: https://thingspeak.com/channels/3570079

 Segurança

A chave de escrita da API do ThingSpeak não deve ser publicada no repositório. Antes de disponibilizar o projeto publicamente, as credenciais reais devem ser removidas do código e substituídas por valores de exemplo.

 Autor

**Artur Lobo**

Estudante de Análise e Desenvolvimento de Sistemas — Embarque Digital.

Projeto desenvolvido para a atividade final de Internet das Coisas (IoT).
