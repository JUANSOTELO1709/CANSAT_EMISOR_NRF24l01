# CANSAT EMISOR 🚀  
NRFl01


## Monitoreo Ambiental con Sensores y Comunicación Inalámbrica

Este proyecto utiliza sensores y módulos de comunicación inalámbrica para recopilar datos ambientales (temperatura, presión, altitud y humedad) y transmitirlos de manera eficiente. La implementación incluye la activación de un pin digital en función de cambios en la altitud, con notificaciones en caso de descenso.  

---

# ⚠️ **Precaución** ⚠️  

El circuito debe ser energizado con **3.3V**, ya que tanto el sensor **BMP280** como el módulo **nRF24L01** tienen una alta probabilidad de dañarse si se energizan con un voltaje mayor.  

Para alimentar todo el circuito de manera segura, se puede usar una batería de **3.7V** acompañada de un regulador de voltaje adecuado para obtener los 3.3V requeridos.  

👉 **Nota:** Asegúrate de verificar las conexiones y los niveles de voltaje antes de energizar el circuito.  

## 📝 **Descripción del Proyecto**  

El sistema integra los siguientes componentes:  

1. **Sensor DHT11**: Para medir la humedad relativa del ambiente.  
2. **Sensor BMP280**: Para obtener datos de temperatura, presión atmosférica y altitud.  
3. **Módulo RF24**: Para transmitir los datos recopilados a otro dispositivo mediante comunicación inalámbrica.  

Además, el proyecto cuenta con un mecanismo que detecta cambios en la altitud máxima alcanzada y activa/desactiva un pin digital como respuesta.  

---
## 📝 **Diagrama electronico**  
![diagrama cansat](https://github.com/user-attachments/assets/a1aa45de-5a73-4d1d-ba18-ff72bd92f186)
En donde:

A1= Arduino Nano.

![nano](https://github.com/user-attachments/assets/a5ae518b-7f34-4086-98e2-f9b97b801249)


U1= Es el modulo de comunicacion NRF24l01.

![Rf](https://github.com/user-attachments/assets/b813a95f-a3b0-462d-b19d-cb16d41a7621)

U2= Es un sensor DHT11.

![DHT11](https://github.com/user-attachments/assets/7ab375e9-dfb1-4cf1-b39a-dbe3e5556c67)

J4= Representa el sensor BMP280 para la conexion electronica.


![bmp280](https://github.com/user-attachments/assets/d03ecbb5-0734-4dd8-b53a-986d7a76c404)

## 📂 **Estructura del Código**  

### **Librerías Importadas**  
- `Wire.h` y `Adafruit_Sensor.h` para comunicación I2C y manejo del sensor BMP280.  
- `Adafruit_BMP280.h` para funciones específicas del sensor BMP280.  
- `SPI.h` y `nRF24L01.h` para comunicación con el módulo RF24.  
- `DHT.h` para la gestión del sensor DHT11.  

### **Variables Principales**  
- **Sensores**:  
  - BMP280: Mide temperatura, presión y altitud.  
  - DHT11: Mide humedad relativa.  
- **Comunicación RF24**:  
  - Dirección: `"00001"`.  
  - Configuración mínima de potencia para transmisión.  
- **Control**:  
  - `ALTITUD_MAXIMA`: Variable para registrar la mayor altitud alcanzada.  
  - Pin `D2`: Controla la salida digital según las condiciones de descenso.  

---

## 🚀 **Flujo de Ejecución**  

### **1. Inicialización**  
- Los sensores BMP280 y DHT11 son inicializados y validados para garantizar su correcto funcionamiento.  
- El módulo RF24 es configurado y preparado para transmitir datos.  

### **2. Bucle Principal (`loop`)**  
- **Lectura de Datos**:  
  - Se obtiene la temperatura, presión, altitud y humedad del entorno.  
- **Detección de Altitud**:  
  - Se registra la mayor altitud alcanzada.  
  - Si el dispositivo desciende más de 1 metro desde la altitud máxima:  
    - Se apaga el pin `D2`.  
    - Se envían 10 mensajes de alerta (`"ha caido!"`) mediante RF24.  
  - En caso contrario, el pin `D2` permanece encendido.  
- **Transmisión de Datos**:  
  - Los datos recopilados son enviados como un paquete (temperatura, presión, altitud, humedad) al dispositivo receptor.  

---

## 🛠️ **Requisitos**  

1. **Hardware**:  
   - Sensor BMP280.  
   - Sensor DHT11.  
   - Módulo nRF24L01.  
   - Microcontrolador compatible con Arduino.  
2. **Software**:  
   - Arduino IDE.  
   - Librerías necesarias:  
     - `Adafruit_BMP280`  
     - `DHT`  
     - `RF24`  

---

## 💡 **Características Principales**  

1. **Medición Ambiental**:  
   - Temperatura en grados Celsius.  
   - Presión en hectopascales (hPa).  
   - Altitud relativa en metros.  
   - Humedad relativa en porcentaje (%).  
2. **Detección de Descensos**:  
   - Activación de alertas cuando el dispositivo desciende significativamente.  
3. **Transmisión Inalámbrica**:  
   - Comunicación eficiente utilizando el módulo RF24.  

---

## 📌 **Cómo Usar**  

1. **Preparar el Hardware**:  
   - Conectar los sensores y el módulo RF24 al microcontrolador según las especificaciones.  
2. **Cargar el Código**:  
   - Subir el sketch al microcontrolador desde el Arduino IDE.  
3. **Verificar Resultados**:  
   - Monitorear los datos transmitidos mediante un dispositivo receptor.  

---

## 🤝 **Contribución**  

Este proyecto está abierto a mejoras y sugerencias. Si tienes ideas o encuentras errores, no dudes en crear un [issue](https://github.com/JUANSOTELO1709) o enviar un pull request.  

---

### 🖼️ **Vista Previa del Sistema**  
*Datos transmitidos y monitorizados en consola.*  
![visual](https://github.com/user-attachments/assets/0887719c-3cce-433a-a828-5a42d40822a9)
---

**Autor**: [Juan David Sotelo Rozo](https://github.com/JUANSOTELO1709)  
📅 Última Actualización: 24 de Diciembre de 2024  
