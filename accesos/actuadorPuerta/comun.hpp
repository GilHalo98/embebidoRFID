#pragma ONCE

// Pines de salida usados.
#define ESP_LED 2 // Color AZUL
#define NODE_LED 16   // Color ROJO

// Pines del GPIO a usar.
#define RELE_1 5
#define RELE_2 4
#define RELE_3 14
#define RELE_4 12

// Librerias incluidas
#include <EEPROM.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SocketIOclient.h>
#include <ESP8266HTTPClient.h>

// Estructura que almacena la informacion de configuración del
// dispositivo y la red.
struct CONFIGURACION_DISPOSITIVO {
    // Puerto del servidor API.
    int portApi;

    // Access token.
    char accessToken[255];

    // SSID de la red.
    char ssid[255];

    // Password de la red.
    char password[255];

    // IP del servidor API.
    char ipApi[255];
};

enum ESTADOS {
    /*
    * Estados posibles del lector RFID.
    */

    // Estado inicial del esp8266.
    INICIALIZACION,

    // Estado de configuracion de variables en EEPROM.
    CONFIGURAR_VARIABLES,

    // Cargamos los datos de la EEPROM.
    CARGAR_CONFIGURACION_EEPROM,

    // Estado de conexion con la red.
    CONEXION_RED,

    // Estado de inicializacion de conexion
    // con servidor sockets.
    INICIALIZAR_CONEXION_SOCKETS,

    // Estado de espera de conexion con socket server exitosa.
    ESPERA_CONEXION_SOCKETS,

    // Estado de inicializacion de perifericos.
    INICIALIZAR_PERIFERICOS,

    // Estado de error con inicializacion de perifericos.
    ERROR_PERIFERICOS,

    // Estado de espera por evento por medio de sockets.
    ESPERA_EVENTO,

    // Evento de abrir puerta.
    ABRIR_PUERTA,

    // Evento de espera de apertura puerta.
    ESPEAR_APERTURA,

    // Evento de espera con la puerta abierta.
    ESPERA_PUERTA_ABIERTA,

    // Evento de cerrar puerta.
    CERRAR_PUERTA,

    // Evento de espera de cierre puerta.
    ESPEAR_CIERRE,
};

enum EVENTOS {
    /*
    * Eventos que se pasan por medio de I2C.
    * */

    // Evento de espera por confirmacion de configuracion.
    ESPERA_CONFIGURACION,

    // Evento de verificacion de configuracion.
    INICIAR_CONFIGURACION,

    // Cambia el bit de permiso pedido por el dispositivo.
    CAMBIAR_PERMISO_PEDIDO,

    // Evento para cambiar el SSID de la red.
    CAMBIAR_SSID,

    // Cambia la password del SSID.
    CAMBIAR_PASSWORD,

    // Cambia el puerto del servidor API.
    CAMBIAR_PUERTO_API,

    // Cambia la ip del servidor API.
    CAMBIAR_IP_API,

    // Cambia el url de la version del API a usar.
    CAMBIAR_VERSION_API,

    // Cambia el access token del dispositvo.
    CAMBIAR_ACCESS_TOKEN,

    // Evento de finalizacion de configuracion
    FINALIZAR_CONFIGURACION
};

enum FLAGS {
    /*
    * Banderas del estado del dispositivo y las operaciones de este.
    */

    // Error detectado.
    ERROR_CON_DISPOSITIVO = 0b00000000,

    // Inicialización terminada.
    INICIALIZACION_TERMINADA = 0b00000001,

    // Indica cuando una configuracion se guardo exitosamente.
    ESCRITURA_TERMINADA = 0b00000010,

    // Banderas libres.
    FLAG_3 = 0b00000100,
    FLAG_4 = 0b00001000,
    FLAG_5 = 0b00010000,
    FLAG_6 = 0b00100000,

    // Operación terminada.
    OPERACION_TERMINADA = 0b01000000,

    // Conexión cerrada.
    CONEXION_CERRADA = 0b10000000,
};

enum ESTATUS {
    // Status de dispositivo no inicializado.
    DESCONECTADO = 0b00000000,

    CONECTADO = 0b00000001,
    DESOCUPADO = 0b00000010,
    PERIFERICOS_NO_INICIALIZADOS = 0b00000100,
    OCUPADO = 0b00001000,

    LIBRE_2 = 0b00010000,
    LIBRE_3 = 0b00100000,
    LIBRE_4 = 0b01000000,
    LIBRE_5 = 0b10000000,
};

// Instanciamos el cliente socketIO.
SocketIOclient Socket;

// Establece el ESTADO actual del esp8266.
ESTADOS ESTADO;
ESTADOS ESTADO_ANTERIOR;

// Establece el ESTATUS actual del esp8266.
ESTATUS ESTATUS_DISPOSITIVO;
ESTATUS ESTATUS_DISPOSITIVO_ANTERIOR;

// Evento recivido por medio de sockets.
String EVENTO_RECIVIDO;

// Definimos la dimencion del vector de direcciones a usar en la EEPROM
const int DIMENCION_EEPROM = 2048;

// Intentos maximos de conexion a red.
const int INTENTOS_MAXIMOS = 20;

// Tiempo de espera por intento.
const int TIEMPO_ESPERA = 2000;

// BaudRate de comunicacion serial.
unsigned long BAUD = 115200;

// Configuracion de la red.
String SSID = "";
String PASSWORD = "";

// Access token de la api.
String ACCESS_TOKEN = "";

// Puerto del servidor api.
int PORT_API = 0;

// IP del servidor api
String IP_API = "";

// Frecuencia de actualizacion del manager de estados.
int FRECUENCIA_ACTUALIZACION_MAIN = 100;

// Indica si el dispositivo recivio el evento de identificarse.
bool IDENTIFICARSE = false;

// Frecuencia del parpadeo del led del node.
int FRECUENCIA_PARPADEO = 250;

// Indica si se ejecutara la secuencia completa de apertura/cerrado
// de la puerta.
bool EJECUTAR_SECUENCIA_COMPLETA = true;