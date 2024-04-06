/*
* Funciones para los protocolos de comunicacion.
* */

// Inicializa el protocolo de comunicacion I2C.
bool inicializarI2C(void);

// Envia un evento por medio de I2C.
bool enviarEvento(DIRECCIONES_PERIFERICOS, EVENTOS);

// Inicia comunicacion Serial.
bool inicializarSerial(void);

// Checa si se recivio algun evento por medio del bus Serial.
int checarPorEvento(void);

// Cecha si se recivo el evento de configurar las variables.
bool checarPorConfiguracion(void);

// Inicializa la comunicacion por SPI.
bool inicializarSPI(void);

// Innicializa la conexion a WiFi.
bool inicializarWiFi(void);

// Inicializa la conexion con el servidor de sockets.
bool inicializarSockets(void);

// Importamos las funciones.
#include "./comsI2C.cpp"
#include "./comsSerial.cpp"
#include "./comsSPI.cpp"
#include "./comsWiFi.cpp"
