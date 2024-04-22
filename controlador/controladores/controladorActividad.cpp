/*
* Controlaodres de actividad del dispositivo.
**/

bool CONTROLADOR_ACTIVIDAD::validarInicioActividad(void) {
    /*
    * Valida las credenciales del empelado
    * para el inicio de la actividad.
    **/

    // Valida los permisos de acceso del empleado con
    // el pedido por el dispositivo.
    if((ROL_EMPLEADO & ROL_PEDIDO) > 0) {
        // Si el bitwise es mayor que 0, se garantiza el acceso.
        CREDENCIALES_VALIDAS = true;

    } else {
        // De lo contrario se niega el acceso.
        CREDENCIALES_VALIDAS = false;
    }

    // Cambiamos el ESTADO al envio del repore de actividad inciada.
    ESTADO = ESTADOS::REPORTE_ACTIVIDAD_INICIADA;

    return true;
};

bool CONTROLADOR_ACTIVIDAD::inicioActividad(void) {
    /*
    * Realizamos el inicio de la actividad, esto es, si se requiere
    * inicializar algo, sincronizarlo, etc.
    */

    // Activamos un relevados.
    digitalWrite(RELE_1, LOW);

    // Cambiamos el estado.
    ESTADO = ESTADOS::EN_ACTIVIDAD;

    return true;
};

bool CONTROLADOR_ACTIVIDAD::enActividad(void) {
    /*
    * En esta controlador, mientras sigua detectando la misma
    * tarjeta ingresada la actividad sigue en ejecucion, pero si la deja
    * de detectar parla la actividad.
    */

    // Si la actividad fue forzada, no checamos la presencia de
    // la tarjeta en el lector.
    if(!ACTIVIDAD_FORZADA) {
        // Si no hay tarjeta presente.
        if(!RFID::lecturaContinua()) {
            // Se cambia el estatus al de terminarActividad.
            ESTADO = ESTADOS::TERMINAR_ACTIVIDAD;
        }   
    }

    return true;
};

bool CONTROLADOR_ACTIVIDAD::terminarActividad(void) {
    /*
    * En esta controlador, terminamos la actividad, esto es, si
    * se requiere cambiar de estado algun relevador, GPIO o enviar una
    * señal.
    */

    // Activamos un relevados.
    digitalWrite(RELE_1, HIGH);

    // Si la actividad esta fue forzada y se termino, se pasa
    // directamente al estado de espera de tarjeta.
    if(ACTIVIDAD_FORZADA) {
        // Cambiamos el estado.
        ESTADO = ESTADOS::ESPERA_TARJETA;

        // Cambiamos el indicador de actividad forzada a falso.
        ACTIVIDAD_FORZADA = false;

    } else {
        // Cambiamos el estado.
        ESTADO = ESTADOS::REPORTE_ACTIVIDAD_FINALIZADA;
    }

    return true;
};