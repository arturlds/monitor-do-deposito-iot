
#include <WiFi.h>
#include "DHTesp.h"
#include "ThingSpeak.h"

// ================= CONFIGURACAO =================

const char* MATRICULA = "2026.32.7843";

unsigned long CANAL_ID = 3570079; // Substituir pelo ID do canal

const char* CHAVE_ESCRITA = "ZYA5O6WQXZXZL515";

const int LIMITE = 28;

// =================================================

const unsigned long INTERVALO_ENVIO_MS = 20000;

const int PINO_DHT = 15;
const int PINO_LED = 2;
const int PINO_BUZZER = 4;

DHTesp dht;
WiFiClient cliente;

bool alarme = false;
bool leituraValida = false;

unsigned long ultimaLeitura = 0;
unsigned long ultimoEnvio = 0;

float temperatura = 0;
float umidade = 0;

// Decide quando ligar e desligar o alarme
bool decidirAlarme(float t, bool alarmeAtual) {

  if (!alarmeAtual && t > LIMITE)
    return true;

  if (alarmeAtual && t < LIMITE - 1)
    return false;

  return alarmeAtual;
}

// Atualiza LED e buzzer
void atualizarSaidas(bool ligado) {

  digitalWrite(PINO_LED, ligado ? HIGH : LOW);

  if (ligado)
    tone(PINO_BUZZER, 1000, 200);
}

// Conecta ao Wi-Fi
void conectarWiFi() {

  Serial.print("Conectando ao Wi-Fi");

  WiFi.begin("Wokwi-GUEST", "", 6);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println(" conectado!");
}

// Envia os dados ao ThingSpeak
void enviarParaNuvem() {

  ThingSpeak.setField(1, temperatura);
  ThingSpeak.setField(2, umidade);

  // Envia o status do alarme
  if (alarme) {
    ThingSpeak.setStatus("ALERTA");
  } else {
    ThingSpeak.setStatus("NORMAL");
  }

  int codigo = ThingSpeak.writeFields(CANAL_ID, CHAVE_ESCRITA);

  Serial.printf(
    "COMPROVANTE | mat=%s | limite=%d | HTTP=%d\n",
    MATRICULA, LIMITE, codigo
  );
}

void setup() {

  Serial.begin(115200);

  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);

  dht.setup(PINO_DHT, DHTesp::DHT22);

  Serial.printf(
    "MONITOR DO DEPOSITO | matricula=%s | limite=%d C\n",
    MATRICULA, LIMITE
  );

  conectarWiFi();

  ThingSpeak.begin(cliente);
}

void loop() {

  unsigned long agora = millis();

  // Leitura a cada 2 segundos
  if (agora - ultimaLeitura >= 2000) {

    ultimaLeitura = agora;

    TempAndHumidity leitura = dht.getTempAndHumidity();

    if (dht.getStatus() == DHTesp::ERROR_NONE) {

      temperatura = leitura.temperature;
      umidade = leitura.humidity;

      leituraValida = true;

      alarme = decidirAlarme(temperatura, alarme);

      atualizarSaidas(alarme);

      Serial.printf(
        "T=%.1f C | H=%.0f %% | alarme=%s\n",
        temperatura,
        umidade,
        alarme ? "LIGADO" : "DESLIGADO"
      );

    } else {

      leituraValida = false;

      Serial.println("ERRO: leitura invalida do DHT22");
    }
  }

  // Envio a cada 20 segundos
  if (agora - ultimoEnvio >= INTERVALO_ENVIO_MS) {

    ultimoEnvio = agora;

    if (leituraValida) {
      enviarParaNuvem();
    } else {
      Serial.println("Envio ignorado: sem leitura valida.");
    }
  }
}
