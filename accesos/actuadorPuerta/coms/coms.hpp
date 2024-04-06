/*
* Funciones para los protocolos de comunicacion.
* */

// Inicializa el protocolo de comunicacion I2C.
bool inicializarI2C(void);

// Inicia comunicacion Serial.
bool inicializarSerial(void);

// Checa si se recivio algun evento por medio del bus Serial.
int checarPorEvento(void);

// Cecha si se recivo el evento de configurar las variables.
bool checarPorConfiguracion();

// Inicializa la conexion a WiFi.
bool inicializarWiFi(void);

// Manejo de los eventos recividos por medio de sockets.
void handlerEventosSocket(socketIOmessageType_t, uint8_t*, size_t);

// Inicializa la comunicacion con el servidor de sockets.
bool inicializarSockets(void);

// Reporta el status actual del dispositivo.
bool reportarEstatusDispositivo(void);

// Procesa los eventos personalizados recividos por sockets.
bool procesarEventosPersonalizados(void);

// Importamos las funciones.
#include "./comsSerial.cpp"
#include "./comsWiFi.cpp"
#include "./comsSocket.cpp"
