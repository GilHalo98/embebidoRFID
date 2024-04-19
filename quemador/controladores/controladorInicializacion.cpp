/*
* Inicializa el NODEMCU.
**/

bool CONTROLADOR_INICIALIZAR::inicializar(void) {
    /*
    * Inicializa los buses de comunicacion.
    */

    // Inicializamos el bus Serial.
    COMS_SERIAL::inicializarSerial();

    // Inicializamos el bus SPI.
    COMS_SPI::inicializarSPI();

    // Cambiamos al estado de inicializacion de perifericos.
    ESTADO = ESTADOS::INICIALIZAR_PERIFERICOS;

    return true;
};

bool CONTROLADOR_INICIALIZAR::inicializarPerifericos(void) {
    /*
    * Inicializa los perifericos del embebido.
    */

    // Indica el estado de la inicializacion.
    bool initOK = false;

    // Inicializamos el lcd.
    initOK = LCD::inicializarLCD();

    // Mostramos el proceso de inicializacion.
    LCD::mostrarTexto("LECTOR:", 0, 1);

    // Verificamos que la inicializacion de los perifericos fue
    // exitosa.
    if(initOK) {
        LCD::mostrarTexto("OK", 8, 1);
    } else {
        LCD::mostrarTexto("ERROR", 8, 1);
    }

    // Inicializamos el RC522.
    initOK = RFID::inicializarRFID();

    // Mostramos el proceso de inicializacion.
    LCD::mostrarTexto("RFID:", 0, 2);

    // Verificamos que la inicializacion de los perifericos fue
    // exitosa.
    if(initOK) {
        LCD::mostrarTexto("OK", 6, 2);
    } else {
        LCD::mostrarTexto("ERROR", 6, 2);
    }

    // Esperamos un momento.
    delay(500);

    if(initOK) {
        // Mostramos en el lcd esperando a guardar configuracion.
        LCD::mostrarTexto(
            "Esperando a recivir",
            0,
            0,
            true
        );

        LCD::mostrarTexto(
            "configuracion...",
            0,
            1
        );

        // Respondemos por serial con el bit
        // de inicialización terminada.
        Serial.println("\r\n");
        Serial.println(FLAGS::INICIALIZACION_TERMINADA);

        // Cambiamos al estado de espera de evento serial.
        ESTADO = ESTADOS::ESPERA_EVENTO;

    } else {
        // Respondemos por serial con el bit
        // de error con dispositivo.
        Serial.println("\r\n");
        Serial.println(FLAGS::ERROR_CON_DISPOSITIVO);

        // Cambiamos al estado de generacion de reporte de perifericos.
        ESTADO = ESTADOS::ERROR_PERIFERICOS;
    }

    return true;
};
