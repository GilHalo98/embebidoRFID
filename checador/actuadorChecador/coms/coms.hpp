/*
* Funciones para los protocolos de comunicacion.
* */

// Inicializa el protocolo de comunicacion I2C.
bool inicializarI2C(void);

// Escucha por eventos emitidos en el bus I2C.
bool escucharEventos(int);

// Inicia comunicacion Serial.
bool inicializarSerial(void);

// Importamos las funciones.
#include "./comsI2C.cpp"
#include "./comsSerial.cpp"
