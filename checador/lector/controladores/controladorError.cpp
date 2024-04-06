/*
* Controlador de estadis de errores.
**/

bool errorAPI(void) {
    /*
    * Control del estado de error de conexion con API.
    **/

    // Imprimimos que ocurrio un error con la API.
    Serial.println("Error al conectar con API");

    if(estadoAnterior == ESTADOS::REPORTE_ERROR_PERIFERICOS) {
        estado = ESTADOS::ERROR_PERIFERICOS;
    } else {
        estado = ESTADOS::ESPERA_TARJETA;
    }

    return true;
};

bool errorRegistroReporte(void) {
    /*
    * Control del estado de error de registro de reporte en DB.
    **/

    // Imprimimos que ocurrio un error al registrar un reporte.
    Serial.println("Error al intentar registrar un reporte");

    if(estadoAnterior == ESTADOS::REPORTE_ERROR_PERIFERICOS) {
        estado = ESTADOS::ERROR_PERIFERICOS;
    } else {
        estado = ESTADOS::ESPERA_TARJETA;
    }

    return true;
};

bool errorInicializacionPerifericos(void) {
    /*
    * Control del estado de error de inicializacion de perifericos.
    **/

    // Mostramos que ocurrio un error al iniciar los perifericos.
    Serial.println("Error, perifericos no inicializados correctamente");

    // Esperamos 5 segundos.
    delay(5000);

    return true;
};
