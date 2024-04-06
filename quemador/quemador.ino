#include "./comun.hpp"
#include "./coms/coms.hpp"
#include "./perifericos/perifericos.hpp"
#include "./controladores/controladores.hpp"

void setup(void) {
    // Establecemos el estado a inicializacion.
    estado = ESTADOS::INICIALIZACION;

    // Inicializamos los buses de comunicacion.
    inicializarComs();
};


void loop(void) {
    if(estado != estadoAnterior) {
        Serial.print("Estado actual: ");
        Serial.println(estado);

        estadoAnterior = estado;
    }

    switch(estado) {
        case ESTADOS::INICIALIZAR_PERIFERICOS: {
            inicializarPerifericos();
            break;

        } case ESTADOS::ERROR_PERIFERICOS: {
            break;

        } case ESTADOS::ESPERA_EVENTO: {
            esperarEvento();
            break;

        } case ESTADOS::ESPERA_TARJETA: {
            esperaTarjeta();
            break;

        } case ESTADOS::AUTENTIFICACION_TARJETA: {
            autentificarTarjeta();
            break;

        } case ESTADOS::ERROR_AUTENTIFICACION: {
            break;

        } case ESTADOS::GUARDAR_DATOS_TARJETA: {
            guardarDatosTarjeta();
            break;

        } case ESTADOS::ERROR_ESCRITURA: {
            break;

        } case ESTADOS::ESCRITURA_FINALIZADA: {
            escrituraFinalizada();
            break;

        } default: {
            break;
        }
    }

    // Esperamos 100ms para no generar lecturas falsas de los
    // inputs.
    delay(100);
};
