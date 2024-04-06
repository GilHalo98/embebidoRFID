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

    // Inicializamos el bus I2C.
    inicializarI2C();

    if(checarPorConfiguracion()) {
        // Si se recive el evento de configuracion de variables por
        // serial, entonces se envia al estado de configuracion de variables.
        estado = ESTADOS::CONFIGURAR_VARIABLES;

    } else {
        // Si no se recive el evento de configuracion, se pasa al
        // estado de conexion de red.
        estado = ESTADOS::CONEXION_RED;
    }

    return true;
};

bool inicializarPerifericos(void) {
    /*
    * Inicializa los perifericos del embebido.
    */

    bool initOK = false;

    // Inicializamos los GPIO.
    initOK = inicializarGPIO();

    // Inicializamos el RC522.
    initOK = inicializarRFID();

    if(initOK) {
        // Cambiamos al estado de espera de tarjeta.
        estado = ESTADOS::ESPERA_TARJETA;
        
    } else {
        // Cambiamos al estado de generacion de reporte de perifericos.
        estado = ESTADOS::REPORTE_ERROR_PERIFERICOS;
    }

    return true;
};

bool conexionRed(void) {
    /*
    * Inicializa la conexion a la red WiFi.
    **/

    // Si la conexion fue exitosa, pasamos al estado
    // de inicializar perifericos.
    if(inicializaWiFi()) {
        estado = ESTADOS::INICIALIZAR_PERIFERICOS;
    }

    return true;
};