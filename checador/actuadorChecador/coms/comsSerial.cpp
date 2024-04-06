/*
* Rutinas para la comunicacion Serial.
* */

bool inicializarSerial(void) {
    /*
    * Inicializa la comunicacion serial.
    * */

    // Inicializa la comunicacion con el baud rate dado.
    Serial.begin(baud);

    return true;
};
