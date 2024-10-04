/*
 * Rutinas para la comunicacion por medio de sockets.
 * */

void COMS_SOCKETS::handlerEventosSocket(
    socketIOmessageType_t type,
    uint8_t* payload,
    size_t length
) {
    switch(type) {
        case sIOtype_DISCONNECT:
            Serial.printf("[IOc] Disconnected!\n");

            // Hacemos que el led del node parpadee.
            digitalWrite(ESP_LED, !digitalRead(ESP_LED));

            // Establecemos el estatus como desconectado.
            ESTATUS_DISPOSITIVO =  ESTATUS::DESCONECTADO;

            // Esperamos 1 segundo para intentar la reconexino con
            // el servidor socket.
            delay(2000);

            // Desactivamos la identificacion.
            IDENTIFICARSE = false;

            // Activamos la reconexion del dispositivo al servidor.
            RECONEXION = true;

            // Esperamos la reconexion al servidor socket.
            ESTADO = ESTADOS::ESPERA_CONEXION_SOCKETS;

            break;

        case sIOtype_CONNECT:
            Serial.printf("[IOc] Connected to url: %s\n", payload);

            // join default namespace (no auto join in Socket.IO V3)
            Socket.send(sIOtype_CONNECT, "/");

            // Establecemos el estatus como conectado.
            ESTATUS_DISPOSITIVO =  ESTATUS::CONECTADO;

            // Cada que se recive el evento de conexion con el socket
            // server, se espera 1s para enviar el estatus de conectado.
            delay(2000);

            // Apagamos el led del node.
            digitalWrite(ESP_LED, LOW);

            if(RECONEXION) {
                /*
                * Esto podria ser mejor enviar un evento de reconexion
                * el cual haria que el servidor pregunte por el estatus
                * del dispositivo.
                */
                Serial.println("Iniciando Reconexion");

                // Si es una reconexion, esperamos 2
                // segundos adicionales.
                delay(2000);

                // Desactivamos la reconexion.
                RECONEXION = true;
            }

            // Si se reintento la conexion, se pasa al estado
            // de inicializacion de perifericos.
            ESTADO = ESTADOS::INICIALIZAR_PERIFERICOS;

            break;

        case sIOtype_EVENT:
            Serial.printf("[IOc] get event: %s\n", payload);
            
            // Recuperamos el evento recivido y sus argumentos.
            EVENTO_RECIVIDO = (char *) payload;

            // Procesa los eventos personalizados recividos por sockets.
            procesarEventosPersonalizados();

            break;

        case sIOtype_ACK:
            Serial.printf("[IOc] get ack: %u\n", length);
            hexdump(payload, length);
            break;

        case sIOtype_ERROR:
            Serial.printf("[IOc] get error: %u\n", length);
            hexdump(payload, length);
            break;

        case sIOtype_BINARY_EVENT:
            Serial.printf("[IOc] get binary: %u\n", length);
            hexdump(payload, length);
            break;

        case sIOtype_BINARY_ACK:
            Serial.printf("[IOc] get binary ack: %u\n", length);
            hexdump(payload, length);
            break;
    }
};

bool COMS_SOCKETS::inicializarSockets(void) {
    Socket.setAuthorization(ACCESS_TOKEN);
    Socket.begin(IP_API, PORT_API, "/socket.io/?EIO=4");
    Socket.onEvent(handlerEventosSocket);
    return true;
};

bool COMS_SOCKETS::reportarEstatusDispositivo(void) {
    // creat JSON message for Socket.IO (event)
    DynamicJsonDocument buffer(1024);
    JsonArray array = buffer.to<JsonArray>();

    // add evnet name
    // Hint: socket.on('event_name', ....
    array.add("reportar_status");

    // add payload (parameters) for the event
    JsonObject param1 = array.createNestedObject();
    param1["status"] = (uint32_t) ESTATUS_DISPOSITIVO;

    // JSON to String (serializion)
    String output;
    serializeJson(buffer, output);
    serializeJson(buffer, Serial);
    Serial.println();

    // Send event
    Socket.sendEVENT(output);

    return true;
};

bool COMS_SOCKETS::enviarPeticionAcceso(void) {
    // creat JSON message for Socket.IO (event)
    DynamicJsonDocument buffer(1024);
    JsonArray array = buffer.to<JsonArray>();

    // add evnet name
    // Hint: socket.on('event_name', ....
    array.add("peticion_acceso");

    // add payload (parameters) for the event
    JsonObject param1 = array.createNestedObject();
    param1["resolucion"] = (uint8_t) ACCESO_GARANTIZADO;

    // JSON to String (serializion)
    String output;
    serializeJson(buffer, output);

    // Send event
    Socket.sendEVENT(output);

    return true;
};

bool COMS_SOCKETS::enviarPeticionAccesoBloqueo(void) {
    // creat JSON message for Socket.IO (event)
    DynamicJsonDocument buffer(1024);
    JsonArray array = buffer.to<JsonArray>();

    // add evnet name
    // Hint: socket.on('event_name', ....
    array.add("peticion_acceso_bloquear");

    // add payload (parameters) for the event
    JsonObject param1 = array.createNestedObject();
    param1["resolucion"] = (uint8_t) ACCESO_GARANTIZADO;

    // JSON to String (serializion)
    String output;
    serializeJson(buffer, output);

    // Send event
    Socket.sendEVENT(output);

    return true;
};

bool COMS_SOCKETS::enviarPeticionAccesoDesbloqueo(void) {
    // creat JSON message for Socket.IO (event)
    DynamicJsonDocument buffer(1024);
    JsonArray array = buffer.to<JsonArray>();

    // add evnet name
    // Hint: socket.on('event_name', ....
    array.add("peticion_acceso_desbloquear");

    // add payload (parameters) for the event
    JsonObject param1 = array.createNestedObject();
    param1["resolucion"] = (uint8_t) ACCESO_GARANTIZADO;

    // JSON to String (serializion)
    String output;
    serializeJson(buffer, output);

    // Send event
    Socket.sendEVENT(output);

    return true;
};

bool COMS_SOCKETS::procesarEventosPersonalizados(void) {
    /*
    * Procesamos los eventos personalizados que lleguen por sockets.
    */

    // Instanicamos un json buffer.
    JsonDocument buffer;

    // Deserealizamos el evento recivido.
    DeserializationError error = deserializeJson(buffer, EVENTO_RECIVIDO);

    // Si no existe error en la deserealizacion.
    if(!error) {
        // Mostramos el evento por el serial.
        serializeJson(buffer, Serial);
        Serial.println();

        // Recuperamos el nombre del evento en cuestion.
        String evento = buffer[0];

        // Si el evento es de tipo toggle_identificarse.
        if(evento == "toggle_identificarse") {
            if(IDENTIFICARSE) {
                digitalWrite(LED_IDENTIFICACION, LOW);
            }

            // Hacemos toggle a la variable que indica al dispostivo
            // identificarse.
            IDENTIFICARSE = !IDENTIFICARSE;

            // Si se deja de identificar.
            if(!IDENTIFICARSE) {
                // Si el estatus es ocupado, entonces apagamos el led indicador.
                if(ESTATUS_DISPOSITIVO == ESTATUS::OCUPADO) {
                    digitalWrite(LED_IDENTIFICACION, HIGH);
                } else {
                    digitalWrite(LED_IDENTIFICACION, LOW);
                }
            }
        }
    }


    // Al terminar de procesar el evento, el evento recivido se
    // asigna a nulo.
    EVENTO_RECIVIDO = "";

    return true;
};