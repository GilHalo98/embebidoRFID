/*
* Funciones para los protocolos de comunicacion.
* */

namespace COMS_SERIAL {
    /* Namespace de comunicacion serial. */

    // Inicia comunicacion Serial.
    bool inicializarSerial(void);

    // Checa si se recivio algun evento por medio del bus Serial.
    int checarPorEvento(void);

    // Cecha si se recivo el evento de configurar las variables
    // en tiempo de boot.
    bool checarPorConfiguracionBOOT();
};

namespace COMS_SPI {
    // Inicializa la comunicacion por SPI.
    bool inicializarSPI(void);
};

namespace COMS_WIFI {
    // Inicializa la conexion a WiFi.
    bool inicializarWiFi(void);
};

namespace COMS_SOCKETS {
    // Manejo de los eventos recividos por medio de sockets.
    void handlerEventosSocket(socketIOmessageType_t, uint8_t*, size_t);

    // Inicializa la comunicacion con el servidor de sockets.
    bool inicializarSockets(void);

    // Reporta el status actual del dispositivo.
    bool reportarEstatusDispositivo(void);

    // Reporta el intento de acceso y la resolucion de
    // este por medio de sockets.
    bool enviarPeticionAcceso(void);

    // Reporta el intento de acceso, bloqueo y la resolucion de
    // este por medio de sockets.
    bool enviarPeticionAccesoBloqueo(void);

    // Reporta el intento de acceso, desbloqueo y la resolucion de
    // este por medio de sockets.
    bool enviarPeticionAccesoDesbloqueo(void);

    // Procesamos los eventos personalizados que lleguen por sockets,
    // esto se hace con un interruptor.
    bool procesarEventosPersonalizados(void);
};

// Importamos las funciones.
#include "./comsSerial.cpp"
#include "./comsSPI.cpp"
#include "./comsWiFi.cpp"
#include "./comsSocket.cpp"
