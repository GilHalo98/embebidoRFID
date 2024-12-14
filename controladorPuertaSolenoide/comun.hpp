/*
    Ver 0.1.0: Primera version estable del firmware.
*/

#pragma ONCE

// Version.
#define VERSION "0.1.0"

// Pines de salida usados.
#define ESP_LED 2 // Color AZUL
#define NODE_LED 16   // Color ROJO
#define LED_IDENTIFICACION 2

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

    // Estado de halt.
    HALT,

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

    // Evento de espera del uso de la puerta.
    ESPERAR_USO_PUERTA,

    // Evento de cerrar puerta.
    CERRAR_PUERTA
};

enum EVENTOS {
    /*
    * Eventos que se pasan por medio de I2C.
    * */

    // Evento de espera por confirmacion de configuracion.
    ESPERA_CONFIGURACION,

    // Evento de verificacion de configuracion.
    INICIAR_CONFIGURACION,

    // Evento para cambiar el SSID de la red.
    CAMBIAR_SSID,

    // Cambia la password del SSID.
    CAMBIAR_PASSWORD,

    // Cambia el puerto del servidor API.
    CAMBIAR_PUERTO_API,

    // Cambia la ip del servidor API.
    CAMBIAR_IP_API,

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

    // Estatus de conexion con el servidor sockets.
    CONECTADO = 0b00000001,

    // Estatus de libre para realizar operacion.
    LIBRE = 0b00000010,

    // Estatus de error con dispositivo.
    ERROR = 0b00000100,

    // Estatus de dispositivo ocupado.
    OCUPADO = 0b00001000,

    // Estatus de dispositivo bloqueado.
    BLOQUEADO = 0b00010000,

    // Banderas libres.
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

// Tiempo de espera por intento de conexion.
const int TIEMPO_ESPERA_CONEXION = 2000;

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

// Indica si el dispositivo recivio el evento de identificarse.
bool IDENTIFICARSE = false;

// Indica si se ejecutara la secuencia completa de apertura/cerrado
// de la puerta.
bool EJECUTAR_SECUENCIA_COMPLETA = true;

// Indica si la puerta sera bloqueada.
bool BLOQUEAR_PUERTA = false;

// Indica si la puerta sera desbloqueada.
bool DESBLOQUEAR_PUERTA = false;

// Frecuencia de actualizacion del manager de estados.
unsigned long int FRECUENCIA_ACTUALIZACION_MAIN = 100;

// Frecuencia del parpadeo del led del node.
unsigned long int FRECUENCIA_PARPADEO = 250;

// Tiempo de espera para el uso de la puerta.
unsigned long int TIEMPO_ESPERA_USO_PUERTA = 5000;

// Tiempo de temporizador.
unsigned long int TEMPORIZADOR;

// Indica si se trata de una reconexion.
bool RECONEXION = false;