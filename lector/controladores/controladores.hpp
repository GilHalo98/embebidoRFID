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

namespace CONTROLADOR_RFID {
    /*
    * Controladores de lector RFID del dispositivo.
    */

    // Autentifica la tarjeta ingresada.
    bool autentificarTarjeta(void);

    // Lee los datos de la tarjeta y los carga en la memoria.
    bool leerDatosTarjeta(void);

    // Espera por ingreso de tarjeta.
    bool esperaTarjeta(void);
};

namespace CONTROLADOR_ERROR {
    /*
    * Controladores de lector ERROR del dispositivo.
    */

    // Error con la inicializacion deperifericos del dispositivo.
    bool errorInicializacionPerifericos(void);

    // Error con el registro de reportes.
    bool errorRegistroReporte(void);

    // Error de conexion con la api.
    bool errorAPI(void);

    // HALT.
    bool halt(void);
};

namespace CONTROLADOR_API {
    /*
    * Controladores de la api.
    */

    // Verifica el estado de la conexion de la api.
    bool verificarEstadoApi(void);

    // Valida que el registro empleado exista en la DB.
    bool validarExistenciaEmpleado(void);

    // Registra un reporte de acceso.
    bool reporteAcceso(void);

    // Registra un reporte de autentificacion de tarjeta fallida
    bool reporteErrorAutentificacionTarjeta(void);

    // Registra un reprte de registro de empleado no existe.
    bool reporteEmpleadoInexistente(void);
};

namespace CONTROLADOR_SOCKETS {
    /*
    * Controladores de la api.
    */

    // Espera la confirmacion de la conexion al servidor sockets.
    bool esperaConfirmacionSockets(void);

    // Envia el evento de acceso por sockets.
    bool enviarEventoAcceso(void);
};

namespace CONTROLADOR_ACCESOS {
    // Valida el acceso al empleado.
    bool validarAcceso(void);
};

// Importamos las funciones de los controladores
#include "./controladorInicializacion.cpp"
#include "./controladorEventos.cpp"
#include "./controladorAccesos.cpp"
#include "./controladorConfig.cpp"
#include "./controladorError.cpp"
#include "./controladorRFID.cpp"
#include "./controladorAPI.cpp"
