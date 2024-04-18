/*
* Rutinas para la comunicacion Serial.
* */

bool COMS_SERIAL::inicializarSerial(void) {
    /*
    * Inicializa la comunicacion serial.
    * */

    // Inicializa la comunicacion con el baudRate dado.
    Serial.begin(BAUD);

    Serial.println("\nSerial inicializado");

    return true;
};

int COMS_SERIAL::checarPorEvento(void) {
    /*
     * Checa si se ha recivido algun evento sobre el bus Serial.
     * */

    if(Serial.available() > 0) {
        return Serial.parseInt();
    }

    return -1;
};

bool COMS_SERIAL::checarPorConfiguracionBOOT() {
    /*
    * Enviamos el evento de configuracion por Serial
    * si se responde con OK, retornamos true.
    * */


    // Enviamos por serial la flag de que se termino
    // la inicializacion del dispositivo.
    Serial.println(FLAGS::INICIALIZACION_TERMINADA);

    // Mandamos un evento de espera por confirmacion de configuracion.
    Serial.println("Espera por evento...");

    delay(1000);

    // Si hay datos en buffer recividos.
    if(Serial.available() > 0) {
        // Leemos el evento recivo.
        int eventoPorSerial = Serial.parseInt();

        Serial.print("Evento Recivido: ");
        Serial.println(eventoPorSerial);

        // Si se recivio un evento de configuracion.
        if(eventoPorSerial == EVENTOS::INICIAR_CONFIGURACION) {
            Serial.println(FLAGS::ESCRITURA_TERMINADA);

            // Si se recive el evento de configuracion
            // de variables por serial, entonces se envia al ESTADO
            // de configuracion de variables.
            ESTADO = ESTADOS::CONFIGURAR_VARIABLES;

            return true;
        }
    }

    return false;
};