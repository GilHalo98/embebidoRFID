/*
 * Controlador de perifericos del actuador.
 * */

// Inicializa los GPIO.
bool inicializarGPIO(void);

// Realiza un toggle sobre el pin dado.
bool toggleGPIO(int);

// Incluimos las funciones.
#include "./gpio.cpp"
