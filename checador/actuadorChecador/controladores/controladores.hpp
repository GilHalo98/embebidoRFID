/*
 * Rutina del controlador de los eventos del arduino nano.
 * */

// Control de inicializacion.
bool inicializacion(void);

// Controlador de chequeo ok.
bool chequeoOK(void);

// Controlador de chequeo fallido.
bool chequeoFallido(void);

// Incluimos las funciones.
#include "./controladorEventos.cpp"
#include "./controladorInicializacion.cpp"
