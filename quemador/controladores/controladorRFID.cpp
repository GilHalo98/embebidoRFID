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
    if(!autentificarTarjetaEscritura(1)) {
        estado = ESTADOS::ERROR_AUTENTIFICACION;
        return false;
    }

    if(!autentificarTarjetaEscritura(2)) {
        // Si los datos fueron autentificados exitosamente
        // se pasa al estado de lectura de tarjeta.
        estado = ESTADOS::ERROR_AUTENTIFICACION;

        return false;
    }

    // Si no, entonces se pasa al estado de error de autentificacion
    // de bloques de tarjeta.
    estado = ESTADOS::GUARDAR_DATOS_TARJETA;

    return true;
};

bool guardarDatosTarjeta(void) {
    /*
     * Lee los datos del empleado de la tarjeta.
     * */

    // Serial.print("Se escribiran los siguientes datos: ");
    // Serial.print(ID_EMPLEADO);
    // Serial.print(" ");
    // Serial.println(PERMISO_EMPLEADO);

    // Realizamos la escritura de los datos de la tarjeta.
    bool escrituraOK = false;

    // Guardamos en el bloque 1, que representa el id del empleado.
    escrituraOK = escrituraRFID(1, ID_EMPLEADO);

    // Guardamos en el bloque 2, que representa los permisos del empleado.
    escrituraOK = escrituraRFID(2, PERMISO_EMPLEADO);

    // Guardamos en el bloque 3, que representa el rol del empleado.
    escrituraOK = escrituraRFID(3, PERMISO_EMPLEADO);

    // Si la lectura fallo.
    if(!escrituraOK) {
        // Esperamos a que ingrese nuevamente la tarjeta.
        estado = ESTADOS::ERROR_ESCRITURA;
    }

    // Cambiamos al estado de escritura finalizda.
    estado = ESTADOS::ESCRITURA_FINALIZADA;

    return true;
};
