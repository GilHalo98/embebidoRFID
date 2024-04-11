/*
 * Controlador de perifericos del actuador.
 * */

// Inicializa los GPIO.
bool inicializarGPIO(void);

// Realiza un toggle sobre el pin dado.
bool toggleGPIO(int);

// Mostramos el estatus del dispositivo desde la torreta.
bool mostrarEstatusTorreta(void);

// Incluimos las funciones.
#include "./gpio.cpp"
