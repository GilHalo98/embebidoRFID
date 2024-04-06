/*
* Rutinas para la comunicacion Serial.
* */

bool inicializarSerial(void) {
    /*
    * Inicializa la comunicacion serial.
    * */

    // Inicializa la comunicacion con el baud rate dado.
    Serial.begin(BAUD_RATE);

    // Serial.println("\nSerial inicializado");

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

int recivirDato(void) {
    /*
    * Recive un dato por serial.
    */
    if(Serial.available() > 0) {
        return Serial.parseInt();
    }

    return NULL;
}