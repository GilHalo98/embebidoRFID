/*
* Rutinas para la comunicacion SPI.
* */

bool inicializarSPI(void) {
    /*
    * Inicializa la comunicacion SPI.
    * */

    // Inicializa la comunicacion SPI.
    SPI.begin();

    Serial.println("SPI Inicializado");

    return true;
};
