/*
* Rutinas de los controladores de los estados del esp8266
*/

namespace CONTROLADOR_CONFIGURACION {
    /*
    * Controladores de configuracion del dispositivo.
    */

    // Recive y almacena la configuracion recivida por serial.
    bool configurarVariables(void);
};

namespace CONTROLADOR_INICIALIZAR {
    /*
    * Controladores de inicializacion del dispositivo.
    */

    // Inicializa la conexion con el server sockets.
    bool inicializarConexionSockets(void);

    // Carga la configuracion del dispositivo almacenada en la EEPROM.
    bool cargarConfiguracionEEPROM(void);

    // Inicializa los perifericos del dispositivo.
    bool inicializarPerifericos(void);

    // Inicializa los buses de comunicacion del dispositivo.
    bool inicializar(void);

    // Inicializa el modulo wifi del dispositivo.
    bool conexionRed(void);
};

namespace CONTROLADOR_ERROR {
    /*
    * Controladores de lector ERROR del dispositivo.
    */

    // Error con la inicializacion deperifericos del dispositivo.
    bool errorInicializacionPerifericos(void);

    // HALT.
    bool halt(void);
};

namespace CONTROLADOR_SOCKETS {
    /*
    * Controladores de la api.
    */

    // Esperamos por un evento por medio de sockets.
    bool esperarPorEvento(void);

    // Espera la confirmacion de la conexion al servidor sockets.
    bool esperaConfirmacionSockets(void);
};

namespace CONTROLADOR_PERIFERICOS {
    /*
    * Controladores de los perifericos.
    */

    // Mandamos a home la puerta.
    bool enviarPuertaHome(void);

    // Esperamos un tiempo y despues cerramos la puerta.
    bool esperarPase(void);

    // Realizamos la accion del actuador.
    bool realizarAccion(void);

    // Abrimos la puerta.
    bool abrirPuerta(void);

    // Esperamos a que la puerta sea abierta.
    bool esperarApertura(void);

    // cerramos la puerta.
    bool cerrarPuerta(void);

    // Esperamos a que la puerta sea cerrada.
    bool esperarCierre(void);
};

// Importamos las funciones de los controladores
#include "./controladorInicializacion.cpp"
#include "./controladorPerifericos.cpp"
#include "./controladorEventos.cpp"
#include "./controladorConfig.cpp"
#include "./controladorError.cpp"
