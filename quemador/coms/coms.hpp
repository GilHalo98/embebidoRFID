/*
* Funciones para los protocolos de comunicacion.
* */

// Inicia comunicacion Serial.
bool inicializarSerial(void);

// Checa si se recivio algun evento por medio del bus Serial.
int checarPorEvento(void);

// recivimos un dato del serial.
int recivirDato(void);

// Vaciamos el buffer serial.
void vaciarBuffer(void);

// Inicializa la comunicacion por SPI.
bool inicializarSPI(void);

// Importamos las funciones.
#include "./comsSerial.cpp"
#include "./comsSPI.cpp"
