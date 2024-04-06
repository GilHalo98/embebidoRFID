/*
* Funciones para los protocolos de comunicacion.
* */

// Inicia comunicacion Serial.
bool inicializarSerial(void);

// Checa si se recivio algun evento por medio del bus Serial.
int checarPorEvento(void);

// Cecha si se recivo el evento de configurar las variables.
bool checarPorConfiguracion();

// Cecha si se recivo el evento de configurar las variables
// en tiempo de boot.
bool checarPorConfiguracionBOOT();

// Inicializa la comunicacion por SPI.
bool inicializarSPI(void);

// Inicializa la conexion a WiFi.
bool inicializarWiFi(void);

// Manejo de los eventos recividos por medio de sockets.
void handlerEventosSocket(socketIOmessageType_t, uint8_t*, size_t);

// Inicializa la comunicacion con el servidor de sockets.
bool inicializarSockets(void);

// Reporta el status actual del dispositivo.
bool reportarEstatusDispositivo(void);

// Reporta el intento de acceso y la resolucion de
// este por medio de sockets.
bool enviarPeticionAcceso(void);

// Procesamos los eventos personalizados que lleguen por sockets,
// esto se hace con un interruptor.
bool procesarEventosPersonalizados(void);

// Importamos las funciones.
#include "./comsSerial.cpp"
#include "./comsSPI.cpp"
#include "./comsWiFi.cpp"
#include "./comsSocket.cpp"
