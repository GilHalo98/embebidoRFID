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

    // Inicializamos los buses de comunicacion y la
    // memoria EEPROM y checamos por configuracion de variables.
    CONTROLADOR_INICIALIZAR::inicializar();
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
        COMS_SOCKETS::reportarEstatusDispositivo();

        // Mostramos el estatus actual desde la torreta.
        GPIO::mostrarEstatusTorreta();

        // El estatus anterior lo tomamos del estatus actual.
        ESTATUS_DISPOSITIVO_ANTERIOR = ESTATUS_DISPOSITIVO;

        // Si el estatus es ocupado, entonces apagamos el led indicador.
        if(ESTATUS_DISPOSITIVO == ESTATUS::OCUPADO) {
            digitalWrite(LED_IDENTIFICACION, HIGH);
        } else {
            digitalWrite(LED_IDENTIFICACION, LOW);
        }
    }

    // Si el dispositivo recivo el evento de identificarse
    // parpadeamos el led del node.
    if(IDENTIFICARSE) {
        if(millis() - TEMPORIZADOR >= FRECUENCIA_PARPADEO) {
            // Realizamos un toggle del led indicador.
            GPIO::toggleGPIO(LED_IDENTIFICACION);

            // Actualizamos el tiempo.
            TEMPORIZADOR = millis();
        }
    }

    // Cada que transcurra 100ms se actualizara el estado
    // del dispositivo.
    if(millis() % FRECUENCIA_ACTUALIZACION_MAIN == 0) {
        switch(ESTADO) {
            case ESTADOS::CONFIGURAR_VARIABLES: {
                CONTROLADOR_CONFIGURACION::configurarVariables();
                break;

            } case ESTADOS::CARGAR_CONFIGURACION_EEPROM: {
                CONTROLADOR_INICIALIZAR::cargarConfiguracionEEPROM();
                break;

            } case ESTADOS::CONEXION_RED: {
                CONTROLADOR_INICIALIZAR::conexionRed();
                break;

            } case ESTADOS::INICIALIZAR_CONEXION_SOCKETS: {
                CONTROLADOR_INICIALIZAR::inicializarConexionSockets();
                break;

            } case ESTADOS::ESPERA_CONEXION_SOCKETS: {
                CONTROLADOR_SOCKETS::esperaConfirmacionSockets();
                break;

            } case ESTADOS::INICIALIZAR_PERIFERICOS: {
                CONTROLADOR_INICIALIZAR::inicializarPerifericos();
                break;

            } case ESTADOS::ERROR_PERIFERICOS: {
                CONTROLADOR_ERROR::errorInicializacionPerifericos();
                break;

            } case ESTADOS::ESPERA_EVENTO: {
                CONTROLADOR_SOCKETS::esperarPorEvento();
                break;

            } case ESTADOS::ABRIR_PUERTA: {
                CONTROLADOR_PERIFERICOS::abrirPuerta();
                break;

            } case ESTADOS::ESPERAR_USO_PUERTA: {
                CONTROLADOR_PERIFERICOS::esperarUsoPuerta();
                break;

            } case ESTADOS::CERRAR_PUERTA: {
                CONTROLADOR_PERIFERICOS::cerrarPuerta();
                break;

            } default: {
                CONTROLADOR_ERROR::halt();
                break;
            }
        }
    }
};
