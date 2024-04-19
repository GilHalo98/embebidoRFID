/*
* Rutinas para la comunicacion SPI.
* */

bool COMS_SPI::inicializarSPI(void) {
    /*
    * Inicializa la comunicacion SPI.
    * */

    // Inicializa la comunicacion SPI.
    SPI.begin();

    return true;
};
