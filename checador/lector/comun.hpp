#pragma ONCE

// Pines de salida usados.
#define NODE_LED 16 // Color ROJO
#define ESP_LED 2   // Color AZUL

// Pines del RC522.
#define RST_PIN 0  // D3
#define SS_PIN 15  // D8

#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

namespace NETWORKING {
    /*
    * Namespace para las propiedades de la red.
    * NOTA: La información del SSID y la PASSWORD pasarla a
    * la EEPROM
    */

    // SSID de la red.
    const char* ssid = "Totalplay-CBAA"; // "IZZI-0442";

    // Password de la red.
    const char* password = "CBAAA5EATY6mzS4z"; // "509551F40442";

    // IP del servidor.
    const char* ipApi = "192.168.100.61"; // "192.168.0.7";

    // Puerto del servidor.
    const unsigned int portApi = 3001;

    // Version de la api a llamar.
    const char* versionApi = "/apiv1.0/";

    // Intentos maximos de conexion a red.
    const unsigned int intentosMaximos = 20;

    // Tiempo de espera por intento.
    const unsigned int tiempoEsperaPorIntento = 1000;
};

enum ESTADOS {
    /*
    * Estados posibles del lector RFID.
    */

    // Estado inicial del esp8266.
    INICIALIZACION,

    // Estado de configuracion de variables en EEPROM.
    CONFIGURAR_VARIABLES,

    // Estado de conexion con la red.
    CONEXION_RED,

    // Estado de inicializacion de perifericos.
    INICIALIZAR_PERIFERICOS,

    // Estado de registro de reporte de error con perifericos.
    REPORTE_ERROR_PERIFERICOS,

    // Estado de error de conexion con API.
    ERROR_CONEXION_API,

    // Estado error con perifericos.
    ERROR_PERIFERICOS,

    // Estado de registro de reporte fallido.
    REGISTRO_REPORTE_FALLIDO,

    // Estado de espera por tarjeta.
    ESPERA_TARJETA,

    // Estado de autentificacion de tarjeta.
    AUTENTIFICACION_TARJETA,

    // Estado de reporte de error de autentificacion.
    REPORTE_ERROR_AUTENTIFICACION,

    // Estado de lectura de datos de tarjeta.
    LEER_DATOS_TARJETA,

    // Estado de verificacion de empleado en registros de la DB.
    VERIFICAR_EMPLEADO,

    // Estado de reporte de datos no se encuentran en registro.
    REPORTE_DATOS_NO_COINCIDEN_CON_REGISTRO,

    // Estado de validacion de acceso.
    VALIDAR_ACCESO_EMPLEADO,

    // Estado de envio de evento de estado de acceso por medio del bus I2C.
    ENVIAR_EVENTO_ACCESO,

    // Estado de reporte de registro de reporte del estado de
    // acceso del empleado.
    REPORTE_ACCESO,
};

enum EVENTOS {
    /*
    * Eventos que se pasan por medio de I2C.
    * */

    // Evento de acceso garantizado emitido por master.
    GARANTIZAR_ACCESO,

    // Evento de acceso negado emitido por master.
    NEGAR_ACCESO,

    // Evento de espera por confirmacion de configuracion.
    ESPERA_CONFIGURACION,

    // Evento de verificacion de configuracion.
    INICIAR_CONFIGURACION,

    // Evento de finalizacion de configuracion
    FINALIZAR_CONFIGURACION
};

enum DIRECCIONES_PERIFERICOS {
    /*
    * Direcciones de perifericos para comunicacion por I2C.
    */

    // Periferico de control de actuadores.
    ACTUADOR = 0x0A,
};

enum TIPOS_REPORTES {
    /*
     * Enumerador de los tipos de reportes.
     * */

    // El index 0 en los tipos de reportes no existe.
    REPORTE_INEXISTENTE,

    // Reporte de quemado de datos en tarjeta.
    QUEMADO_TARJETA,

    // Reporte de acceso garantizado a zona.
    EMPLEADO_ACCESO_GARANTIZADO,

    // Reporte de acceso negado a zona.
    EMPLEADO_ACCESO_NEGADO,

    // Reporte de tarjeta invalida ingresada.
    INGRESO_TARJETA_INVALIDA,

    // Reporte de datos de la tarjeta no coiniciden con registro.
    DATOS_NO_COINCIDEN,

    // Reporte de error de perifericos.
    ERROR_INICIALIZACION_PERIFERICOS
};

// Instanciamos el sensor RC522.
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Instanciamos una llave para el RFID.
MFRC522::MIFARE_Key keyA;
MFRC522::MIFARE_Key keyB;

// Instanciamos un status para el RFID.
MFRC522::StatusCode statusRC522;

// Establece el estado actual del esp8266.
ESTADOS estado;
ESTADOS estadoAnterior;

// Buffer para el sensor RFID.
byte bufferID[18];
byte bufferPermisos[18];

// Datos que se guardaran en la tarjeta.
String idEmpleado;
byte accesos;

// Datos de los accesos pedidos por el node.
// Esto tambien se lee desde la eeprom.
byte permisoPedido = 64;

// Indica si el permiso de acceso fue garantizado o negado.
bool accesoGarantizado = false;

// Baud rate de comunicacion serial.
unsigned long baud = 115200;
