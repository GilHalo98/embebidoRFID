/*
 * Controlador de perifericos del actuador.
 * */

namespace RFID {
    /*
    * Funciones para el uso del modulo RC522.
    */

    // Inicializa el RC522.
    bool inicializarRFID(void);

    // Limpiamos el buffer del RC522.
    bool limpiarBufferRFID(void);

    // Lee la tarjeta por el RC522.
    bool escrituraRFID(int, int);

    // Detectamos si hay una tarjeta presente.
    bool hayTarjetaPresente(void);

    // Autentificamos la tarjeta para la lectura.
    bool autentificarTarjetaEscritura(int);
};


namespace LCD {
    // Inicializamos la pantalla LCD.
    bool inicializarLCD(void);

    // Enviamos un texto para mostrar en el lcd.
    bool mostrarTexto(const char [], int = 0, int = 0, bool = false);
};

// Incluimos las funciones.
#include "./rc522.cpp"
#include "./lcd.cpp"
