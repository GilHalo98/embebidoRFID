/*
* Rutinas de los controladores de los estados del esp8266
*/

// Controlador de configuracion de variables.
bool configurarVariables(void);

// Controlador de inicializacion de buses de comunicacion.
bool inicializarComs(void);

// Controlador de inicializacion de perifericos.
bool inicializarPerifericos(void);

// Controlador de inicializacion de sockets.
bool inicializarConexionSockets(void);

// Esperamos por la confirmacion de conexion al socket server.
bool esperaConfirmacionSockets(void);

// Controlador de carga de datos de la EEPROM.
bool cargarConfiguracionEEPROM(void);

// Controlador de iniciar conexion a red.
bool conexionRed(void);

// Cotrolador de datos de tarjeta.
bool leerDatosTarjeta(void);

// Controlador de autentificacion de tarjeta.
bool autentificarTarjeta(void);

// Controlador de espera de tarjeta.
bool esperaTarjeta(void);

// Controlador de error con conexion a API.
bool errorAPI(void);

// Error de registro de reporte a la DB.
bool errorRegistroReporte(void);

// Error de inicializacion de perifericos.
bool errorInicializacionPerifericos(void);

// Valida que el registro empleado exista en la DB.
bool validarExistenciaEmpleado(void);

// Registra un reporte de acceso.
bool reporteAcceso(void);

// Registra un reporte de fallos con perifericos.
bool reporteFalloPerifericos(void);

// Registra un reporte de autentificacion de tarjeta fallida
bool reporteErrorAutentificacionTarjeta(void);

// Registra un reprte de registro de empleado no existe.
bool reporteEmpleadoInexistente(void);

// Valida el acceso al empleado.
bool validarAcceso(void);

// Envia el evento de acceso por sockets.
bool enviarEventoAcceso(void);

// Importamos las funciones de los controladores
#include "./controladorConfig.cpp"
#include "./controladorInicializacion.cpp"
#include "./controladorRFID.cpp"
#include "./controladorError.cpp"
#include "./controladorAPI.cpp"
#include "./controladorAccesos.cpp"
#include "./controladorEventos.cpp"
