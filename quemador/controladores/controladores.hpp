/*
* Rutinas de los controladores de los estados del dispositivo quemador.
*/

namespace CONTROLADOR_INICIALIZAR {
    // Inicializa los buses de comunicacion.
    bool inicializar(void);

    // Inicializa los perifericos.
    bool inicializarPerifericos(void);
};

namespace CONTROLADOR_EVENTOS {
    // Espera por un evento por medio del bus Serial.
    bool esperarEvento(void);

    // Indica la finalización de la escritura de la tarjeta de manera exitosa.
    bool escrituraFinalizada(void);
};

namespace CONTROLADOR_ERROR {
    // Error de escritura de tarjeta.
    bool errorEscritura(void);

    // Error con perifericos.
    bool errorPerifericos(void);

    // Error de perifericos.
    bool errorAutentificacion(void);

    // Controlador de halt.
    bool halt(void);
};

namespace CONTROLADOR_RFID {
    // Espera el ingreso de una tarjeta.
    bool esperaTarjeta(void);

    // Autentificia la tarjeta para ser escrita.
    bool autentificarTarjeta(void);

    // Escribe los datos en la tarjeta.
    bool guardarDatosTarjeta(void);
};

// Incluimos las funciones del control de estados.
#include "./controladorInicializacion.cpp"
#include "./controladorEventos.cpp"
#include "./controladorError.cpp"
#include "./controladorRFID.cpp"
