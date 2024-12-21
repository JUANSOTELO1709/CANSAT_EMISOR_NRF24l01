#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>

// Definiciones para el sensor DHT11
#define DHTPIN 9      // Pin al que está conectado el DHT11
#define DHTTYPE DHT11 // Tipo de sensor

// Crear objeto DHT
DHT dht(DHTPIN, DHTTYPE);

// Crear objeto RF24, pines CE y CSN
RF24 radio(8, 10);

// Crear objeto BMP280
Adafruit_BMP280 bmp;

const byte direccion[6] = "00001";

float TEMPERATURA;      // Variable para almacenar valor de temperatura
float PRESION, P0;      // Variables para almacenar valor de presion atmosferica
float ALTITUD;          // Variable para almacenar la altitud actual
float HUMEDAD;          // Variable para almacenar el valor de humedad
float ALTITUD_MAXIMA = 0; // Variable para almacenar la altitud máxima alcanzada

bool haAlcanzadoMaximo = false; // Variable para marcar si se ha alcanzado la altitud máxima

const int pinSalida = 2;  // Pin digital que se activará/desactivará

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {  // Cambia 0x76 a 0x77 si tu módulo usa otra dirección I2C
    Serial.println("No se encontró el sensor BMP280, verifica conexiones.");
    while (1);
  }
  
  pinMode(pinSalida, OUTPUT);
  digitalWrite(pinSalida, HIGH);  // Comienza encendido
  
  // Inicializar el sensor BMP280
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de operación */
                  Adafruit_BMP280::SAMPLING_X16,    /* Sobremuestreo de temperatura */
                  Adafruit_BMP280::SAMPLING_X16,    /* Sobremuestreo de presión */
                  Adafruit_BMP280::FILTER_X16,      /* Filtro */
                  Adafruit_BMP280::STANDBY_MS_1);   /* Duración en espera */
  P0 = bmp.readPressure() / 100;  // Almacena en P0 el valor actual de presion en hectopascales para calculo de altitud relativa
  Serial.println("Sensor BMP280 inicializado correctamente con alta resolución");
  
  // Inicializar el sensor DHT11
  dht.begin();
  Serial.println("Sensor DHT11 inicializado correctamente");
  
  // Inicializar el módulo RF24
  if (!radio.begin()) {
    Serial.println("Error: No se pudo inicializar el módulo RF24");
    while (true); // Detener la ejecución si falla la inicialización
  }
  
  radio.openWritingPipe(direccion);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.println("Módulo RF24 inicializado correctamente");
}

void loop() {
  // Leer datos del BMP280
  TEMPERATURA = bmp.readTemperature();
  PRESION = bmp.readPressure() / 100;   // Convertir Pa a hPa
  ALTITUD = bmp.readAltitude(P0);       // Estándar de presión al nivel del mar
  
  // Leer datos del DHT11
  HUMEDAD = dht.readHumidity();

  // Verificar si la lectura fue exitosa
  if (isnan(HUMEDAD)) {
    Serial.println("Error al leer del sensor DHT11");
    return;
  }
  
  Serial.print("Altitud: ");
  Serial.println(ALTITUD);

  // Almacena la altitud máxima alcanzada
  if (ALTITUD > ALTITUD_MAXIMA) {
    ALTITUD_MAXIMA = ALTITUD;
    haAlcanzadoMaximo = true;  // Marca que se ha superado la altitud inicial
  }

  // Verifica si el dispositivo ha descendido 1 metro desde la altitud máxima
  if (haAlcanzadoMaximo && (ALTITUD_MAXIMA - ALTITUD) >= 1.0) {
    digitalWrite(pinSalida, LOW);  // Apaga D2
    Serial.println("¡Descenso detectado! Pin D2 apagado.");

    // Enviar 10 mensajes "ha caido!"
    for (int i = 0; i < 10; i++) {
      const char mensaje[] = "ha caido!";
      radio.write(&mensaje, sizeof(mensaje));
      Serial.println("Mensaje enviado: ha caido!");
    }
  } else {
    digitalWrite(pinSalida, HIGH);  // Mantiene D2 encendido durante el ascenso o mientras no descienda 1 metro
  }

  // Crear un array de datos para enviar
  float datos[4] = {TEMPERATURA, PRESION, ALTITUD, HUMEDAD};
  
  // Verificar la conexión antes de enviar datos
  if (radio.isChipConnected()) {
    radio.write(&datos, sizeof(datos));
    Serial.print("Datos enviados - Temperatura: "); Serial.print(TEMPERATURA);
    Serial.print(" °C, Presión: "); Serial.print(PRESION);
    Serial.print(" hPa, Altitud: "); Serial.print(ALTITUD);
    Serial.print(" m, Humedad: "); Serial.print(HUMEDAD);
    Serial.println(" %");
  } else {
    Serial.println("Error: Módulo RF24 no conectado");
  }
  
  delay(500);  // Pausa para no saturar el sensor
}
