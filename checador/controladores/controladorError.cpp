/*
* Controlador de estadis de errores.
**/

bool CONTROLADOR_ERROR::errorAPI(void) {
    /*
    * Control del ESTADO de error de conexion con API.
    **/

    // Imprimimos que ocurrio un error con la API.
    Serial.println("Error al conectar con API");

    // Cambiamos el estado a halt.
    ESTADO = ESTADOS::HALT;

    return true;
};

bool CONTROLADOR_ERROR::errorRegistroReporte(void) {
    /*
    * Control del ESTADO de error de registro de reporte en DB.
    **/

    // Imprimimos que ocurrio un error al registrar un reporte.
    Serial.println("Error al intentar registrar un reporte");

    // Cambiamos el estado al estado de espera de tarjeta.
    ESTADO = ESTADOS::ESPERA_TARJETA;

    return true;
};

bool CONTROLADOR_ERROR::errorInicializacionPerifericos(void) {
    /*
    * Control del ESTADO de error de inicializacion de perifericos.
    **/

    // Mostramos que ocurrio un error al iniciar los perifericos.
    Serial.println("Error, perifericos no inicializados correctamente");

    // Cambiamos el estado a halt.
    ESTADO = ESTADOS::HALT;

    return true;
};

bool CONTROLADOR_ERROR::halt(void) {
    /*
    * Control de estado de halt, esto es cuando ocurre un problema
    * que altere el flujo de ejecucion.
    */

    // Cambiamos el estatus a errro.
    ESTATUS_DISPOSITIVO = ESTATUS::ERROR;

    return true;
};