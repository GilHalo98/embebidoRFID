#include "./comun.hpp"
#include "./coms/coms.hpp"
#include "./perifericos/perifericos.hpp"
#include "./api/api.hpp"
#include "./controladores/controladores.hpp"

void setup(void) {
    // Establecemos el estado a inicializacion.
    estado = ESTADOS::INICIALIZACION;

    // Inicializamos los pines de los leds integrados.
    pinMode(NODE_LED, OUTPUT);
    pinMode(ESP_LED, OUTPUT);

    // Asignamos los estados a los leds integrados.
    digitalWrite(NODE_LED, HIGH);
    digitalWrite(ESP_LED, HIGH);

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
        case ESTADOS::CONFIGURAR_VARIABLES: {
            configurarVariables();
            break;

        } case ESTADOS::CONEXION_RED: {
            conexionRed();
            break;

        } case ESTADOS::INICIALIZAR_PERIFERICOS: {
            inicializarPerifericos();
            break;

        } case ESTADOS::REPORTE_ERROR_PERIFERICOS: {
            reporteFalloPerifericos();
            break;

        } case ESTADOS::ERROR_CONEXION_API: {
            errorAPI();
            break;

        } case ESTADOS::REGISTRO_REPORTE_FALLIDO: {
            errorRegistroReporte();
            break;

        } case ESTADOS::ERROR_PERIFERICOS: {
            errorInicializacionPerifericos();
            break;

        } case ESTADOS::ESPERA_TARJETA: {
            esperaTarjeta();
            break;

        } case ESTADOS::AUTENTIFICACION_TARJETA: {
            autentificarTarjeta();
            break;

        } case ESTADOS::REPORTE_ERROR_AUTENTIFICACION: {
            reporteErrorAutentificacionTarjeta();
            break;

        } case ESTADOS::LEER_DATOS_TARJETA: {
            leerDatosTarjeta();
            break;

        } case ESTADOS::VERIFICAR_EMPLEADO: {
            validarExistenciaEmpleado();
            break;

        } case ESTADOS::REPORTE_DATOS_NO_COINCIDEN_CON_REGISTRO: {
            reporteEmpleadoInexistente();
            break;

        } case ESTADOS::VALIDAR_ACCESO_EMPLEADO: {
            validarAcceso();
            break;

        } case ESTADOS::ENVIAR_EVENTO_ACCESO: {
            enviarEventoAcceso();
            break;

        } case ESTADOS::REPORTE_ACCESO: {
            registrarReporteAcceso();
            break;

        } default: {
            break;
        }
    }

    // Esperamos 100ms para no generar lecturas falsas de los
    // inputs.
    delay(100);
};
