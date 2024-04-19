#include "./comun.hpp"
#include "./coms/coms.hpp"
#include "./perifericos/perifericos.hpp"
#include "./controladores/controladores.hpp"

void setup(void) {
    // Establecemos el estado a inicializacion.
    ESTADO = ESTADOS::INICIALIZACION;

    // Inicializamos los buses de comunicacion.
    CONTROLADOR_INICIALIZAR::inicializar();
};


void loop(void) {
    // Muestra el estado actual del dispositivo.
    if(ESTADO != ESTADO_ANTERIOR) {
        Serial.print("Estado actual: ");
        Serial.println(ESTADO);

        // Actualizamos el estado anterior.
        ESTADO_ANTERIOR = ESTADO;
    }

    // Cada que transcurra 100ms se actualizara el estado
    // del dispositivo.
    if(millis() % FRECUENCIA_ACTUALIZACION_MAIN == 0) {
        switch(ESTADO) {
            case ESTADOS::INICIALIZAR_PERIFERICOS: {
                CONTROLADOR_INICIALIZAR::inicializarPerifericos();
                break;

            } case ESTADOS::ERROR_PERIFERICOS: {
                CONTROLADOR_ERROR::errorPerifericos();
                break;

            } case ESTADOS::ESPERA_EVENTO: {
                CONTROLADOR_EVENTOS::esperarEvento();
                break;

            } case ESTADOS::ESPERA_TARJETA: {
                CONTROLADOR_RFID::esperaTarjeta();
                break;

            } case ESTADOS::AUTENTIFICACION_TARJETA: {
                CONTROLADOR_RFID::autentificarTarjeta();
                break;

            } case ESTADOS::ERROR_AUTENTIFICACION: {
                CONTROLADOR_ERROR::errorAutentificacion();
                break;

            } case ESTADOS::GUARDAR_DATOS_TARJETA: {
                CONTROLADOR_RFID::guardarDatosTarjeta();
                break;

            } case ESTADOS::ERROR_ESCRITURA: {
                CONTROLADOR_ERROR::errorEscritura();
                break;

            } case ESTADOS::ESCRITURA_FINALIZADA: {
                CONTROLADOR_EVENTOS::escrituraFinalizada();
                break;

            } default: {
                CONTROLADOR_ERROR::halt();
                break;
            }
        }
    }
};
