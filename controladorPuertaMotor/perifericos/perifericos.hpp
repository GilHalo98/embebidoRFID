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

    // Indica si la puerta esta abierta.
    bool puertaEstaAbierta(void);

    // Indica si la puerta esta cerrada.
    bool puertaEstaCerrada(void);
};

// Incluimos las funciones.
#include "./gpio.cpp"
