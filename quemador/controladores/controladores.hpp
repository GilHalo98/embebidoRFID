/*
* Rutinas de los controladores de los estados del dispositivo quemador.
*/

// Inicializa los buses de comunicacion.
bool inicializarComs(void);

// Inicializa los perifericos.
bool inicializarPerifericos(void);

// Espera por un evento por medio del bus Serial.
bool esperarEvento(void);

// Espera el ingreso de una tarjeta.
bool esperaTarjeta(void);

// Autentificia la tarjeta para ser escrita.
bool autentificarTarjeta(void);

// Escribe los datos en la tarjeta.
bool guardarDatosTarjeta(void);

// Indica la finalización de la escritura de la tarjeta de manera exitosa.
bool escrituraFinalizada(void);

// Incluimos las funciones del control de estados.
#include "./controladorEventos.cpp"
#include "./controladorInicializacion.cpp"
#include "./controladorRFID.cpp"
#include "./controladorDispositivo.cpp"
