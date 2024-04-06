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

// Controlador de carga de datos de la EEPROM.
bool cargarConfiguracionEEPROM(void);

// Controlador de iniciar conexion a red.
bool conexionRed(void);

// Controlador de error con conexion a API.
bool errorAPI(void);

// Error de inicializacion de perifericos.
bool errorInicializacionPerifericos(void);

// Esperamos por la confirmacion de la conexion al socket server.
bool esperaConfirmacionSockets(void);

// Esperamos por un evento por medio de sockets.
bool esperarPorEvento(void);

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

// Importamos las funciones de los controladores
#include "./controladorConfig.cpp"
#include "./controladorInicializacion.cpp"
#include "./controladorEventos.cpp"
#include "./controladorPerifericos.cpp"
