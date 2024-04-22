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

    // Mostramos el estatus del dispositivo desde la torreta.
    bool mostrarEstatusTorreta(void);
};

// Incluimos las funciones.
#include "./gpio.cpp"
