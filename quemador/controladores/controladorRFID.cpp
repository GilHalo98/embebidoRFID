/*
 * Controladores del RFID.
 * */

bool CONTROLADOR_RFID::esperaTarjeta(void) {
    /*
     * Espera el ingreso de la tarjeta.
    **/

    if(millis() % 50 == 0) {
        if(TOGGLE_INDICADOR) {
            LCD::mostrarTexto(">", 0, 0);
            LCD::mostrarTexto("<", 19, 0);
        } else {
            LCD::mostrarTexto(" ", 0, 0);
            LCD::mostrarTexto(" ", 19, 0);
        }

        TOGGLE_INDICADOR = !TOGGLE_INDICADOR;
    }

    // Limpiamos el buffer del RC522.
    RFID::limpiarBufferRFID();

    // Verificamos que haya una tarjeta presente en el RC522.
    if(RFID::hayTarjetaPresente()) {
        // Si se detecto una tarjeta, se manda al ESTADO de
        // lectura de datos.
        ESTADO = ESTADOS::AUTENTIFICACION_TARJETA;
    }

    return true;
};

bool CONTROLADOR_RFID::autentificarTarjeta(void) {
    /*
     * Autentifica las llaves de la tarjeta ingresada.
     * */

    // Autentificamos los bloques de los datos del empleado en
    // la tarjeta. Si los datos fueron autentificados exitosamente se
    // pasa al ESTADO de lectura de tarjeta.
    if(!RFID::autentificarTarjetaEscritura(4)) {
        ESTADO = ESTADOS::ERROR_AUTENTIFICACION;
        return false;
    }

    if(!RFID::autentificarTarjetaEscritura(5)) {
        ESTADO = ESTADOS::ERROR_AUTENTIFICACION;
        return false;
    }

    if(!RFID::autentificarTarjetaEscritura(6)) {
        ESTADO = ESTADOS::ERROR_AUTENTIFICACION;
        return false;
    }

    // Si no, entonces se pasa al ESTADO de error de autentificacion
    // de bloques de tarjeta.
    ESTADO = ESTADOS::GUARDAR_DATOS_TARJETA;

    return true;
};

bool CONTROLADOR_RFID::guardarDatosTarjeta(void) {
    /*
     * Lee los datos del empleado de la tarjeta.
     * */

    // Realizamos la escritura de los datos de la tarjeta.
    bool escrituraOK = false;

    // Guardamos en el bloque 1, que representa el id del empleado.
    escrituraOK = RFID::escrituraRFID(
        BLOCK_ID,
        ID_EMPLEADO
    );

    if(escrituraOK) {
        LCD::mostrarTexto("OK", 17, 1);
    } else {
        LCD::mostrarTexto("ERR", 17, 1);
    }

    // Guardamos en el bloque 2, que representa los permisos
    // del empleado.
    escrituraOK = RFID::escrituraRFID(
        BLOCK_PERMISOS,
        PERMISO_EMPLEADO
    );

    if(escrituraOK) {
        LCD::mostrarTexto("OK", 17, 2);
    } else {
        LCD::mostrarTexto("ERR", 17, 2);
    }

    // Guardamos en el bloque 3, que representa el rol del empleado.
    escrituraOK = RFID::escrituraRFID(
        BLOCK_ROL,
        ROL_EMPLEADO
    );

    if(escrituraOK) {
        LCD::mostrarTexto("OK", 17, 3);
    } else {
        LCD::mostrarTexto("ERR", 17, 3);
    }

    // Si la lectura fallo.
    if(!escrituraOK) {
        // Esperamos a que ingrese nuevamente la tarjeta.
        ESTADO = ESTADOS::ERROR_ESCRITURA;
    }

    // Cambiamos al ESTADO de escritura finalizda.
    ESTADO = ESTADOS::ESCRITURA_FINALIZADA;

    return true;
};
