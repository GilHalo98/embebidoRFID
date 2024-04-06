/*
 * Controlador de perifericos del actuador.
 * */

// Inicializa el RC522.
bool inicializarRFID(void);

// Limpiamos el buffer del RC522.
bool limpiarBufferRFID(void);

// Lee la tarjeta por el RC522.
bool escrituraRFID(void);

// Detectamos si hay una tarjeta presente.
bool hayTarjetaPresente(void);

// Autentificamos la tarjeta para la lectura.
bool autentificarTarjetaEscritura(int);

// Incluimos las funciones.
#include "./rc522.cpp"
