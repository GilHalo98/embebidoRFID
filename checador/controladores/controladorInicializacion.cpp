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

    // Cambiamos el estado a carga de configuracion desde la EEPROM.
    ESTADO = ESTADOS::CARGAR_CONFIGURACION_EEPROM;

    return true;
};

bool inicializarPerifericos(void) {
    /*
    * Inicializa los perifericos del embebido.
    */

    // Bandera de inicializacion ok.
    bool initOK = false;

    // Inicializamos el lcd.
    initOK = inicializarLCD();

    // Inicializamos los GPIO.
    initOK = inicializarGPIO();

    // Inicializamos el RC522.
    initOK = inicializarRFID();

    // Verificamos si los perifericos
    // fueron inciados correctamente.
    if(initOK) {
        // Cambiamos al ESTADO de espera de tarjeta.
        ESTADO = ESTADOS::ESPERA_TARJETA;

    } else {
        // Cambiamos al ESTADO de error de perifericos.
        ESTADO = ESTADOS::ERROR_PERIFERICOS;

        // Cambiamos el status del dispositivo.
        ESTATUS_DISPOSITIVO = ESTATUS::PERIFERICOS_NO_INICIALIZADOS;
    }

    return true;
};

bool conexionRed(void) {
    /*
    * Inicializa la conexion a la red WiFi.
    **/

    // Si la conexion fue exitosa, inicializamos la conexion
    // con el servidor de sockets.
    if(inicializaWiFi()) {
        ESTADO = ESTADOS::INICIALIZAR_CONEXION_SOCKETS;
    }

    return true;
};

bool cargarConfiguracionEEPROM(void) {
	/*
	 * Carga los datos de la configuracion desde la EEPROM.
	 * */

    // Cargamos la configuracion de la EEPROM.
    cargarConfiguracion();

	// Pasamos al ESTADO de conexion de red.
	ESTADO = ESTADOS::CONEXION_RED;

	return true;
};

bool inicializarConexionSockets(void) {
    /*
     * Inicializa la conexion con el servidor de sockets.
     * */

    // Inicializamos la conexion con los sockets.
    inicializarSockets();

    // Una vez inicializada la conexion con el servidor de sockets, pasamos
    // a la inicializacion de los perifericos.
    ESTADO = ESTADOS::ESPERA_CONEXION_SOCKETS;

    return true;
};
