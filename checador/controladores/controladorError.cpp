/*
* Controlador de estadis de errores.
**/

bool CONTROLADOR_ERROR::errorAPI(void) {
    /*
    * Control del ESTADO de error de conexion con API.
    **/

    // Imprimimos que ocurrio un error con la API.
    Serial.println("Error al conectar con API");

    // Hacemos que el led del node parpadee.
    digitalWrite(ESP_LED, !digitalRead(ESP_LED));

    // Esperamos 1 segundo para probar el estado del api.
    delay(1000);

    // Cambiamos el estado a probar la conexion con el api.
    ESTADO = ESTADOS::PROBAR_CONEXION_API;

    return true;
};

bool CONTROLADOR_ERROR::errorRegistroReporte(void) {
    /*
    * Control del ESTADO de error de registro de reporte en DB.
    **/

    // Imprimimos que ocurrio un error al registrar un reporte.
    Serial.println("Error al intentar registrar un reporte");

    // Activamos el led de error.
    GPIO::identificarError();

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