/*
* Inicializa el NODEMCU.
**/

bool CONTROLADOR_INICIALIZAR::inicializar(void) {
    /*
    * Inicializa los buses de comunicacion.
    */

    // Inicializamos el bus Serial.
    COMS_SERIAL::inicializarSerial();

    // Inicializamos la memoria EEPROM.
    EEPROM_MEM::inicializarEEPROM();

    // Esperamos por incio de configuracion en tiempo de boot.
    if(COMS_SERIAL::checarPorConfiguracionBOOT()) {
        // Cambiamos el estado a carga de configuracion desde la EEPROM.
        ESTADO = ESTADOS::CONFIGURAR_VARIABLES;

    } else {
        // Cambiamos el estado a carga de configuracion desde la EEPROM.
        ESTADO = ESTADOS::CARGAR_CONFIGURACION_EEPROM;
    }

    return true;
};

bool CONTROLADOR_INICIALIZAR::inicializarPerifericos(void) {
    /*
    * Inicializa los perifericos del embebido.
    */

    // Bandera de inicializacion ok.
    bool initOK = false;

    // Inicializamos los GPIO.
    initOK = GPIO::inicializarGPIO();

    // Verificamos si los perifericos
    // fueron inciados correctamente.
    if(initOK) {
        // Cambiamos al ESTADO de espera de tarjeta.
        ESTADO = ESTADOS::ESPERA_EVENTO;

        // Cambiamos el status del dispositivo.
        ESTATUS_DISPOSITIVO = ESTATUS::LIBRE;

    } else {
        // Cambiamos al ESTADO de error de perifericos.
        ESTADO = ESTADOS::ERROR_PERIFERICOS;

        // Cambiamos el status del dispositivo.
        ESTATUS_DISPOSITIVO = ESTATUS::ERROR;
    }

    return true;
};

bool CONTROLADOR_INICIALIZAR::conexionRed(void) {
    /*
    * Inicializa la conexion a la red WiFi.
    **/

    // Si la conexion fue exitosa, inicializamos la conexion
    // con el servidor de sockets.
    if(COMS_WIFI::inicializarWiFi()) {
        ESTADO = ESTADOS::INICIALIZAR_CONEXION_SOCKETS;
    }

    return true;
};

bool CONTROLADOR_INICIALIZAR::cargarConfiguracionEEPROM(void) {
	/*
	 * Carga los datos de la configuracion desde la EEPROM.
	 * */

    // Cargamos la configuracion de la EEPROM.
    EEPROM_MEM::cargarConfiguracion();

	// Pasamos al ESTADO de conexion de red.
	ESTADO = ESTADOS::CONEXION_RED;

	return true;
};

bool CONTROLADOR_INICIALIZAR::inicializarConexionSockets(void) {
    /*
     * Inicializa la conexion con el servidor de sockets.
     * */

    // Inicializamos la conexion con los sockets.
    COMS_SOCKETS::inicializarSockets();

    // Una vez inicializada la conexion con el servidor de sockets, pasamos
    // a la inicializacion de los perifericos.
    ESTADO = ESTADOS::ESPERA_CONEXION_SOCKETS;

    return true;
};
