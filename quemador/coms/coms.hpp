/*
* Funciones para los protocolos de comunicacion.
* */

// Inicia comunicacion Serial.
bool inicializarSerial(void);

// Checa si se recivio algun evento por medio del bus Serial.
int checarPorEvento(void);

int recivirDato(void);

// Inicializa la comunicacion por SPI.
bool inicializarSPI(void);

// Importamos las funciones.
#include "./comsSerial.cpp"
#include "./comsSPI.cpp"
