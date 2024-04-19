/*
* Rutinas para la comunicacion Serial.
* */

bool COMS_SERIAL::inicializarSerial(void) {
    /*
    * Inicializa la comunicacion serial.
    * */

    // Inicializa la comunicacion con el baud rate dado.
    Serial.begin(BAUD_RATE);

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

int COMS_SERIAL::recivirDato(void) {
    /*
    * Recive un dato por serial.
    */
    if(Serial.available() > 0) {
        return Serial.parseInt();
    }

    return -1;
}

void COMS_SERIAL::vaciarBuffer(void) {
    // Vaciamos el buffer serial.
    while(Serial.available() > 0) {
        Serial.parseInt();
    }

    // Esperamos a que se envien los datos
    // en el buffer.
    Serial.flush();
};