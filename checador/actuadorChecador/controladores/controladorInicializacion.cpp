/*
 * Controladores de inicializacion de dispositivo.
 * */

bool inicializacion(void) {
    /*
     * Controlador que inicializa los perifericos y los buses de
     * comunicacion del dispositivo.
     * */

    // Inicializa el bus serial.
    inicializarSerial();

    // Inicializa el bus I2C.
    inicializarI2C();

    // Inicializa el LCD.
    inicializarLCD();

    return true;
};
