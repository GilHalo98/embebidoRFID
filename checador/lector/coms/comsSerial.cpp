/*
* Rutinas para la comunicacion Serial.
* */

bool inicializarSerial(void) {
    /*
    * Inicializa la comunicacion serial.
    * */

    // Inicializa la comunicacion con el baud rate dado.
    Serial.begin(baud);

    Serial.println("\nSerial inicializado");

    return true;
};

int checarPorEvento(void) {
    /*
     * Checa si se ha recivido algun evento sobre el bus Serial.
     * */

    if(Serial.available() > 0) {
        return Serial.parseInt();
    }

    return -1;
};

bool checarPorConfiguracion(void) {
    /*
    * Enviamos el evento de configuracion por Serial
    * si se responde con OK, retornamos true.
    * */

    // Mandamos un evento de espera por confirmacion de configuracion.
    Serial.println("Espera por evento...");
    Serial.write(EVENTOS::ESPERA_CONFIGURACION);

    // Esperamos medio segundo.
    delay(2000);
    Serial.println("Espera terminada");

    // Si hay datos en buffer recividos.
    if(Serial.available() > 0) {
        // Leemos el evento recivo.
        int eventoPorSerial = Serial.parseInt();

        Serial.print("Evento Recivido: ");
        Serial.println(eventoPorSerial);

        // Si se recivio un evento de configuracion.
        if(eventoPorSerial == EVENTOS::INICIAR_CONFIGURACION) {
            return true;
        }
    }

    return false;
};
