/*
 * Controladores del RFID.
 * */

bool esperaTarjeta(void) {
    /*
     * Espera el ingreso de la tarjeta.
    **/

    if(millis() % 50 == 0) {
        if(toggleIndicador) {
            mostrarTexto(">", 0, 0);
            mostrarTexto("<", 19, 0);
        } else {
            mostrarTexto(" ", 0, 0);
            mostrarTexto(" ", 19, 0);
        }

        toggleIndicador = !toggleIndicador;
    }

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
    // Si los datos fueron autentificados exitosamente
    // se pasa al estado de lectura de tarjeta.
    if(!autentificarTarjetaEscritura(4)) {
        estado = ESTADOS::ERROR_AUTENTIFICACION;
        return false;
    }

    if(!autentificarTarjetaEscritura(5)) {
        estado = ESTADOS::ERROR_AUTENTIFICACION;
        return false;
    }

    if(!autentificarTarjetaEscritura(6)) {
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

    // Realizamos la escritura de los datos de la tarjeta.
    bool escrituraOK = false;

    // Guardamos en el bloque 1, que representa el id del empleado.
    escrituraOK = escrituraRFID(
        BLOCK_ID,
        ID_EMPLEADO
    );

    if(escrituraOK) {
        mostrarTexto("OK", 17, 1);
    } else {
        mostrarTexto("ERR", 17, 1);
    }

    // Guardamos en el bloque 2, que representa los permisos del empleado.
    escrituraOK = escrituraRFID(
        BLOCK_PERMISOS,
        PERMISO_EMPLEADO
    );

    if(escrituraOK) {
        mostrarTexto("OK", 17, 2);
    } else {
        mostrarTexto("ERR", 17, 2);
    }

    // Guardamos en el bloque 3, que representa el rol del empleado.
    escrituraOK = escrituraRFID(
        BLOCK_ROL,
        ROL_EMPLEADO
    );

    if(escrituraOK) {
        mostrarTexto("OK", 17, 3);
    } else {
        mostrarTexto("ERR", 17, 3);
    }

    // Si la lectura fallo.
    if(!escrituraOK) {
        // Esperamos a que ingrese nuevamente la tarjeta.
        estado = ESTADOS::ERROR_ESCRITURA;
    }

    // Cambiamos al estado de escritura finalizda.
    estado = ESTADOS::ESCRITURA_FINALIZADA;

    return true;
};
