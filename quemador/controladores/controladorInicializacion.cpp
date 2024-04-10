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

    // Indica el estado de la inicializacion.
    bool initOK = false;

    // Inicializamos el lcd.
    initOK = inicializarLCD();

    // Inicializamos el RC522.
    initOK = inicializarRFID();

    mostrarTexto("LECTOR:", 0, 1);

    // Verificamos que la inicializacion de los perifericos fue
    // exitosa.
    if(initOK) {
        mostrarTexto("OK", 8, 1);
        delay(500);

        // Cambiamos al estado de espera de tarjeta.
        estado = ESTADOS::ESPERA_EVENTO;

        // Mostramos en el lcd esperando a guardar configuracion.
        mostrarTexto(
            "Esperando a recivir",
            0,
            0,
            true
        );

        mostrarTexto(
            "configuracion...",
            0,
            1
        );

        // Respondemos por serial con el bit
        // de inicialización terminada.
        Serial.println("\r\n");
        Serial.println(FLAGS::INICIALIZACION_TERMINADA);

    } else {
        mostrarTexto("ERROR", 8, 1);
        delay(500);

        // Cambiamos al estado de generacion de reporte de perifericos.
        estado = ESTADOS::ERROR_PERIFERICOS;

        // Respondemos por serial con el bit
        // de error con dispositivo.
        Serial.println("\r\n");
        Serial.println(FLAGS::ERROR_CON_DISPOSITIVO);
    }

    return true;
};
