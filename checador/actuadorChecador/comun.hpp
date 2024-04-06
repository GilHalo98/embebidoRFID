#pragma ONCE

// Pines del LCD.
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

#include <Wire.h>
#include <LiquidCrystal.h>

enum ESTADOS {
    /*
    * Estados del actuador.
    **/

    // Estado de espera por evento.
    ESPERAR_EVENTO,

    // Estado de chequeo ok.
    CHEQUEO_OK,

    // Estado de chequeo fallido.
    CHEQUEO_FALLIDO,
};

enum EVENTOS {
    /*
    * Eventos que se pasan por medio de I2C.
    * */

    // Evento de chequeo ok.
    OK_CHEQUEO,

    // Evento de fallo en el chequeo.
    NO_OK_CHEQUEO,

    // Evento de espera por confirmacion de configuracion.
    ESPERA_CONFIGURACION,

    // Evento de verificacion de configuracion.
    CONFIGURACION,
};

// Instanciamos el lcd.
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Estado Actual.
ESTADOS estado = ESTADOS::ESPERAR_EVENTO;

// Direccion hexadecimal del arduino nano en el bus I2C.
byte direccion = 0x0A;

// Dimenciones del LCD.
unsigned int COLUMNAS_LCD = 20;
unsigned int FILAS_LCD = 4;

// Baud rate de comunicacion serial.
unsigned long baud = 9600;
