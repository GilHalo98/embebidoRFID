/*
 * Controlador de perifericos del actuador.
 * */

namespace GPIO {
    /*
    * Funciones para el uso de los GPIOs
    */

    // Inicializa los GPIO.
    bool inicializarGPIO(void);

    // Realiza un toggle sobre el pin dado.
    bool toggleGPIO(int);

    // Activa el led de error e inicia su timer.
    bool identificarError(void);

    // Activa el led de OK e inicia su timer.
    bool identificarOK(void);
};

namespace RFID {
    /*
    * Funciones para el uso del modulo RC522.
    */

    // Inicializa el RC522.
    bool inicializarRFID(void);

    // Limpiamos el buffer del RC522.
    bool limpiarBufferRFID(void);

    // Lee la tarjeta por el RC522.
    bool lecturaRFID(void);

    // Detectamos si hay una tarjeta presente.
    bool hayTarjetaPresente(void);

    // Autentificamos la tarjeta para la lectura.
    bool autentificarTarjetaLectura(int);
};

// Incluimos las funciones.
#include "./rc522.cpp"
#include "./gpio.cpp"