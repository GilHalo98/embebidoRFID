/*
           |______________________|
    [ ] A0 | ADC           GPIO16 | D0 [X] ---> NODE_LED
    [ ] GN | RESERV        GPIO05 | D1 [X] ---> LED_OK
    [ ] VV | RESERV        GPIO04 | D2 [X] ---> LED_ERROR
    [ ] S3 | GPIO10        GPIO00 | D3 [X] ---> LECTOR RFID
    [ ] S2 | GPIO09        GPIO02 | D4 [X] ---> ESP_LED
    [ ] S1 | GPIO08          3.3V | 3V [=]
    [ ] SC | GPIO11           GND | GN [=]
    [ ] SO | GPIO07        GPIO14 | D5 [X] ---> LECTOR RFID
    [ ] SK | GPIO06        GPIO12 | D6 [X] ---> LECTOR RFID
    [=] GN | GND           GPIO13 | D7 [X] ---> LECTOR RFID
    [=] 3V | 3.3V          GPIO15 | D8 [X] ---> LECTOR RFID
    [ ] EN | RST           GPIO03 | RX [ ]
    [ ] RS | RST           GPIO01 | TX [ ]
    [ ] GN | GND              GND | GN [=]
    [ ] Vi | VCC             3.3V | 3V [=]
           |______________________|

    Ver 0.1.0: Primera version estable del firmware.

    Ver 0.1.1: Bugfix, al realizar la reconexion con el servidor,
        se muestra como estatus desconectado.

    Ver 0.1.2: Bugfix, al recivir respuesta del servidor API revisa
        el codigo de respuesta de manera correcta.

    Ver 0.1.3: Se agrego la opcion de generar un reporte de
        salida de zona.

    Ver 0.1.4: Se agregaron leds para mostrar estado de dispositivo.
*/

#pragma ONCE

// Version.
#define VERSION "0.1.4"

// Pines de salida usados.
#define ESP_LED 2 // Color AZUL
#define NODE_LED 16 // Color ROJO
#define LED_IDENTIFICACION 2
#define LED_OK 5 // Color Verde
#define LED_ERROR 4 // Color ROJO

// Pines del RC522.
#define RST_PIN 0  // D3
#define SS_PIN 15  // D8

// Librerias incluidas
#include <SPI.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SocketIOclient.h>
#include <ESP8266HTTPClient.h>

// Estructura que almacena la informacion de configuración del
// dispositivo y la red.
struct CONFIGURACION_DISPOSITIVO {
    // Permiso requerido por el dispositivo.
    int permisoPedido;

    // Puerto del servidor API.
    int portApi;

    // Acciones opcionales.
    int accionOpcional;

    // Indica si registrar un reporte de salida de zona.
    bool registrarReporteSalida;

    // Access token.
    char accessToken[255];

    // SSID de la red.
    char ssid[255];

    // Password de la red.
    char password[255];

    // IP del servidor API.
    char ipApi[255];

    // URI de la vercion del servidor API.
    char versionApi[255];
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

    // Realiza una prueba con el servidor API.
    PROBAR_CONEXION_API,

    // Estado de inicializacion de conexion
    // con servidor sockets.
    INICIALIZAR_CONEXION_SOCKETS,

    // Estado de espera de conexion con socket server exitosa.
    ESPERA_CONEXION_SOCKETS,

    // Estado de inicializacion de perifericos.
    INICIALIZAR_PERIFERICOS,

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

    // Estado de envio de evento de ESTADO de acceso por medio del bus I2C.
    ENVIAR_EVENTO_ACCESO,

    // Estado de reporte de registro de reporte del ESTADO de
    // acceso del empleado.
    REPORTE_ACCESO,
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

    // Cambia la accion opcional del dispositivo.
    CAMBIAR_ACCION_OPCIONAL,

    // Cambia la opcion de generar un reporte de salida de zona.
    CAMBIAR_REGISTRAR_REPORTE_SALIDA,

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

enum ACCIONES_OPCIONALES {
    /*
    * Acciones opcionales del dispositivo.
    */

    // No realiza ninguna accion opcional.
    NINGUNA,

    // Bloquea la puerta.
    BLOQUEAR_PUERTA_AL_CERRAR,

    // Desbloquea la puerta.
    DESBLOQUEAR_PUERTA_AL_ABRIR
};

// Instanciamos el cliente socketIO.
SocketIOclient Socket;

// Instanciamos el sensor RC522.
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Instanciamos una llave para el RFID.
MFRC522::MIFARE_Key keyA;
MFRC522::MIFARE_Key keyB;

// Bloques de datos.
int BLOCK_ID = 4;
int BLOCK_PERMISOS = 5;
int BLOCK_ROL = 6;

// Instanciamos un status para el RFID.
MFRC522::StatusCode STATUS_RC522;

// Establece el ESTADO actual del esp8266.
ESTADOS ESTADO;
ESTADOS ESTADO_ANTERIOR;

// Establece el ESTATUS actual del esp8266.
ESTATUS ESTATUS_DISPOSITIVO;
ESTATUS ESTATUS_DISPOSITIVO_ANTERIOR;

// Evento recivido por medio de sockets.
String EVENTO_RECIVIDO;

// Buffer para el sensor RFID.
byte bufferID[18];
byte bufferPermisos[18];

// Datos que se encuentran en la tarjeta.
String ID_EMPLEADO;
byte ACCESOS;

// Definimos la dimencion del vector de direcciones a usar en la EEPROM
const int DIMENCION_EEPROM = 2048;

// Intentos maximos de conexion a red.
const int INTENTOS_MAXIMOS = 20;

// Tiempo de espera por intento.
const int TIEMPO_ESPERA_CONEXION = 2000;

// BaudRate de comunicacion serial.
unsigned long BAUD = 115200;

// Indica si el permiso de acceso fue garantizado o negado.
bool ACCESO_GARANTIZADO = false;

// Accion opcional del lector.
int ACCION_OPCIONAL = 0;

// Indica si registrar un reporte de salida de zona.
bool REGISTRAR_REPORTE_SALIDA = false;

// Bit de acceso pedido.
int PERMISO_PEDIDO = 0;

// Configuracion de la red.
String SSID = "";
String PASSWORD = "";

// Access token de la api.
String ACCESS_TOKEN = "";

// Puerto del servidor api.
int PORT_API = 0;

// IP del servidor api
String IP_API = "";

// URL de la version del api a usar.
String VERSION_API = "";

// Indica si el dispositivo recivio el evento de identificarse.
bool IDENTIFICARSE = false;

// Frecuencia de actualizacion del manager de estados.
unsigned long int FRECUENCIA_ACTUALIZACION_MAIN = 100;

// Frecuencia del parpadeo del led del node.
unsigned long int FRECUENCIA_PARPADEO = 250;

// Tiempo de temporizador.
unsigned long int TEMPORIZADOR;

// Indica si se trata de una reconexion.
bool RECONEXION = false;

// Timer para el apagado del led de error.
unsigned long int TIMER_LED_ERROR = 0;

// Tiempo que dura el led encendido.
unsigned int TIEMPO_ENCENDIDO_LED_ERROR = 1000;

// Timer para el apagado del led de ok.
unsigned long int TIMER_LED_OK = 0;

// Tiempo que dura el led encendido.
unsigned int TIEMPO_ENCENDIDO_LED_OK = 1000;