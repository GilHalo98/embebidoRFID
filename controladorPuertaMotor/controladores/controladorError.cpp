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