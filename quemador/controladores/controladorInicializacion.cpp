/*
* Inicializa el NODEMCU.
**/

bool inicializarComs(void) {
    /*
    * Inicializa los buses de comunicacion.
    */

    // Inicializamos el bus Serial.
    inicializarSerial();

    // Inicializamos el bus SPI.
    inicializarSPI();

    // Cambiamos al estado de inicializacion de perifericos.
    estado = ESTADOS::INICIALIZAR_PERIFERICOS;

    return true;
};

bool inicializarPerifericos(void) {
    /*
    * Inicializa los perifericos del embebido.
    */

    bool initOK = false;

    // Inicializamos el RC522.
    initOK = inicializarRFID();

    // Verificamos que la inicializacion de los perifericos fue
    // exitosa.
    if(initOK) {
        // Cambiamos al estado de espera de tarjeta.
        estado = ESTADOS::ESPERA_EVENTO;

        // Respondemos por serial con el bit
        // de inicialización terminada.
        Serial.println("\r\n");
        Serial.println(FLAGS::INICIALIZACION_TERMINADA);

    } else {
        // Cambiamos al estado de generacion de reporte de perifericos.
        estado = ESTADOS::ERROR_PERIFERICOS;

        // Respondemos por serial con el bit
        // de error con dispositivo.
        Serial.println("\r\n");
        Serial.println(FLAGS::ERROR_CON_DISPOSITIVO);
    }

    return true;
};
