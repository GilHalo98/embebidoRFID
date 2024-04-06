#include "./comun.hpp"
#include "./mem/memoria.hpp"
#include "./coms/coms.hpp"
#include "./perifericos/perifericos.hpp"
#include "./controladores/controladores.hpp"

void setup(void) {
    // Establecemos el ESTADO a inicializacion.
    ESTADO = ESTADOS::INICIALIZACION;

    // Establecemos el ESTATUS de no incializado.
    ESTATUS_DISPOSITIVO =  ESTATUS::DESCONECTADO;

    // Inicializamos los pines de los leds integrados.
    pinMode(NODE_LED, OUTPUT);
    pinMode(ESP_LED, OUTPUT);

    // Asignamos los estados a los leds integrados.
    digitalWrite(NODE_LED, HIGH);
    digitalWrite(ESP_LED, HIGH);

    // Inicializamos la memoria EEPROM.
    inicializarEEPROM();

    // Inicializamos los buses de comunicacion.
    inicializarComs();

    // Esperamos por incio de configuracion en tiempo de boot.
    checarPorConfiguracion();
};

void loop(void) {
    // Loop del socket, maneja los eventos que llegan.
    Socket.loop();

    // Muestra e estado actual del dispositivo.
    if(ESTADO != ESTADO_ANTERIOR) {
        Serial.print("Estado actual: ");
        Serial.println(ESTADO);

        ESTADO_ANTERIOR = ESTADO;
    }

    // Muestra e estado actual del dispositivo.
    if(ESTATUS_DISPOSITIVO != ESTATUS_DISPOSITIVO_ANTERIOR) {
        Serial.print("ESTATUS actual: ");
        Serial.println(ESTATUS_DISPOSITIVO);

        // Mandamos el status del dispositivo.
        reportarEstatusDispositivo();

        // El estatus anterior lo tomamos del estatus actual.
        ESTATUS_DISPOSITIVO_ANTERIOR = ESTATUS_DISPOSITIVO;
    }

    // Si el dispositivo recivo el evento de identificarse
    // parpadeamos el led del node.
    if(IDENTIFICARSE) {
        if(millis() % FRECUENCIA_PARPADEO == 0) {
            toggleGPIO(NODE_LED);
        }
    }

    // Cada que transcurra 100ms se actualizara el estado
    // del dispositivo.
    if(millis() % FRECUENCIA_ACTUALIZACION_MAIN == 0) {
        switch(ESTADO) {
            case ESTADOS::CONFIGURAR_VARIABLES: {
                configurarVariables();
                break;

            } case ESTADOS::CARGAR_CONFIGURACION_EEPROM: {
                cargarConfiguracionEEPROM();
                break;

            } case ESTADOS::CONEXION_RED: {
                conexionRed();
                break;

            } case ESTADOS::INICIALIZAR_CONEXION_SOCKETS: {
                inicializarConexionSockets();
                break;

            } case ESTADOS::ESPERA_CONEXION_SOCKETS: {
                esperaConfirmacionSockets();
                break;

            } case ESTADOS::INICIALIZAR_PERIFERICOS: {
                inicializarPerifericos();
                break;

            } case ESTADOS::ESPERA_EVENTO: {
                esperarPorEvento();
                break;

            } case ESTADOS::ABRIR_PUERTA: {
                abrirPuerta();
                break;

            } case ESTADOS::ESPEAR_APERTURA: {
                esperarApertura();
                break;

            } case ESTADOS::ESPERA_PUERTA_ABIERTA: {
                esperarPase();
                break;

            } case ESTADOS::CERRAR_PUERTA: {
                cerrarPuerta();
                break;

            } case ESTADOS::ESPEAR_CIERRE: {
                esperarCierre();
                break;

            } default: {
                break;
            }
        }
    }
};
