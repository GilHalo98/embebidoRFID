#pragma ONCE

// Pines del RC522.
#define RST_PIN 9
#define SS_PIN 10
#define LED_IDENTIFICACION 2

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

enum ESTADOS {
    // Estado inicial del arduino.
    INICIALIZACION,

    // Estado de inicializacion de perifericos.
    INICIALIZAR_PERIFERICOS,

    // Estado error con perifericos.
    ERROR_PERIFERICOS,

    // Estado de espera por evento en serial.
    ESPERA_EVENTO,

    // Estado de pureba de dispositivo.
    PRUEBA_DISPOSITIVO,

    // Estado de espera de ingreso de tarjeta.
    ESPERA_TARJETA,

    // Estado de autentificacion de tarjeta.
    AUTENTIFICACION_TARJETA,

    // Estado de error de autentificacion.
    ERROR_AUTENTIFICACION,

    // Estado de guardar datos en la tarjeta.
    GUARDAR_DATOS_TARJETA,

    // Estado de error de lectura en tarjeta.
    ERROR_ESCRITURA,

    // Estado de finalizacion de escritura.
    ESCRITURA_FINALIZADA
};

enum EVENTOS {
    /*
    * Eventos que se pasan por medio de I2C.
    * */

    // Inicia el grabado de datos.
    INICIAR_GUARDADO_DATOS,

    // Envia el dato del id del empleado.
    ID_ENVIADO,

    // Envia el dato de los permisos del empleado.
    PERMISOS_ENVIADO,

    // Envia el rol del empleado.
    ROL_ENVIADO,

    // Termina el grabado de datos.
    TERMINAR_GUARDADO_DATOS,
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

// Instanciamos el sensor RC522.
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Instanciamos el lcd.
LiquidCrystal_I2C DISPLAY_LCD(0x27, 20, 4);

// Instanciamos una llave para el RFID.
MFRC522::MIFARE_Key keyA;
MFRC522::MIFARE_Key keyB;

// Bloques de datos.
int BLOCK_ID = 4;
int BLOCK_PERMISOS = 5;
int BLOCK_ROL = 6;

// Instanciamos un status para el RFID.
MFRC522::StatusCode statusRC522;

// Establece el estado actual del esp8266.
ESTADOS estado;
ESTADOS estadoAnterior;

// Buffer para el sensor RFID.
byte bufferRFIDEscritura[16];

int ID_EMPLEADO;
int PERMISO_EMPLEADO;
int ROL_EMPLEADO;

// Baud rate de comunicacion serial.
unsigned long BAUD_RATE = 9600;


// Bandera que indica si esta esperando tarjeta.
bool toggleIndicador = false;