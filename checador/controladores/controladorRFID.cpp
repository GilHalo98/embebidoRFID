/*
 * Controladores del RFID.
 * */

bool esperaTarjeta(void) {
    /*
     * Espera el ingreso de la tarjeta.
    **/

    // Limpiamos el buffer del RC522.
    limpiarBufferRFID();

    // Verificamos que haya una tarjeta presente en el RC522.
    if(hayTarjetaPresente()) {
        // Si se detecto una tarjeta, se manda al ESTADO de lectura de datos.
        ESTADO = ESTADOS::AUTENTIFICACION_TARJETA;

        // Y se cambia el estatus del dispositivo a ocupado.
        ESTATUS_DISPOSITIVO = ESTATUS::OCUPADO;

    } else {
        // Se cambia el estadus del dispositivo a nominal.
        ESTATUS_DISPOSITIVO = ESTATUS::DESOCUPADO;
    }

    return true;
};

bool autentificarTarjeta(void) {
    /*
     * Autentifica las llaves de la tarjeta ingresada.
     * */

    // Autentificamos los bloques de los datos del empleado en la tarjeta.
    if(autentificarTarjetaLectura(BLOCK_ID)) {
        // Si los datos fueron autentificados exitosamente
        // se pasa al ESTADO de lectura de tarjeta.
        ESTADO = ESTADOS::LEER_DATOS_TARJETA;

        return true;
    }

    // Si no, entonces se pasa al ESTADO de error de autentificacion
    // de bloques de tarjeta.
    ESTADO = ESTADOS::REPORTE_ERROR_AUTENTIFICACION;

    return true;
};

bool leerDatosTarjeta(void) {
    /*
     * Lee los datos del empleado de la tarjeta.
     * */

    // Realizamos la lectura de los datos de la tarjeta.
    bool lecturaOK = lecturaRFID();

    // Si la lectura fallo.
    if(!lecturaOK) {
        // Esperamos a que ingrese nuevamente la tarjeta.
        ESTADO = ESTADOS::ESPERA_TARJETA;
    }

    // Enviamos el ESTADO a validar los datos
    // de la tarjeta con los del registro.
    ESTADO = ESTADOS::VERIFICAR_EMPLEADO;

    return true;
};
