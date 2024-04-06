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
        // Si se detecto una tarjeta, se manda al estado de lectura de datos.
        estado = ESTADOS::AUTENTIFICACION_TARJETA;
    }

    return true;
};

bool autentificarTarjeta(void) {
    /*
     * Autentifica las llaves de la tarjeta ingresada.
     * */

    // Autentificamos los bloques de los datos del empleado en la tarjeta.
    if(autentificarTarjetaLectura(1)) {
        if(autentificarTarjetaLectura(2)) {
            // Si los datos fueron autentificados exitosamente
            // se pasa al estado de lectura de tarjeta.
            estado = ESTADOS::LEER_DATOS_TARJETA;

            return true;
        }
    }

    // Si no, entonces se pasa al estado de error de autentificacion
    // de bloques de tarjeta.
    estado = ESTADOS::REPORTE_ERROR_AUTENTIFICACION;

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
        estado = ESTADOS::ESPERA_TARJETA;
    }

    // Enviamos el estado a validar los datos
    // de la tarjeta con los del registro.
    estado = ESTADOS::VERIFICAR_EMPLEADO;

    return true;
};
