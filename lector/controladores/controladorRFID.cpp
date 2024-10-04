/*
 * Controladores del RFID.
 * */

bool CONTROLADOR_RFID::esperaTarjeta(void) {
    /*
     * Espera el ingreso de la tarjeta.
    **/

    // Limpiamos el buffer del RC522.
    RFID::limpiarBufferRFID();

    // Verificamos que haya una tarjeta presente en el RC522.
    if(RFID::hayTarjetaPresente()) {
        // Si se detecto una tarjeta, se manda al ESTADO de lectura de datos.
        ESTADO = ESTADOS::AUTENTIFICACION_TARJETA;

        // Y se cambia el estatus del dispositivo a ocupado.
        ESTATUS_DISPOSITIVO = ESTATUS::OCUPADO;

    } else {
        // Se cambia el estadus del dispositivo a nominal.
        ESTATUS_DISPOSITIVO = ESTATUS::LIBRE;
    }

    return true;
};

bool CONTROLADOR_RFID::autentificarTarjeta(void) {
    /*
     * Autentifica las llaves de la tarjeta ingresada.
     * */

    // Autentificamos los bloques de los datos del empleado en la tarjeta.
    if(RFID::autentificarTarjetaLectura(BLOCK_ID)) {
        if(RFID::autentificarTarjetaLectura(BLOCK_PERMISOS)) {
            // Si los datos fueron autentificados exitosamente
            // se pasa al ESTADO de lectura de tarjeta.
            ESTADO = ESTADOS::LEER_DATOS_TARJETA;

            return true;
        }
    }

    // Activamos el led de error.
    GPIO::identificarError();

    // Si no, entonces se pasa al ESTADO de error de autentificacion
    // de bloques de tarjeta.
    ESTADO = ESTADOS::REPORTE_ERROR_AUTENTIFICACION;

    return true;
};

bool CONTROLADOR_RFID::leerDatosTarjeta(void) {
    /*
     * Lee los datos del empleado de la tarjeta.
     * */

    // Realizamos la lectura de los datos de la tarjeta.
    bool lecturaOK = RFID::lecturaRFID();

    // Si la lectura fallo.
    if(!lecturaOK) {
        // Activamos el led de error.
        GPIO::identificarError();

        // Esperamos a que ingrese nuevamente la tarjeta.
        ESTADO = ESTADOS::ESPERA_TARJETA;
    }

    // Enviamos el ESTADO a validar los datos
    // de la tarjeta con los del registro.
    ESTADO = ESTADOS::VERIFICAR_EMPLEADO;

    return true;
};
