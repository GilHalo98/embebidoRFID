/*
* Controlador del API.
**/

bool validarExistenciaEmpleado(void) {
    /*
    * Valida los datos del empleado en la tarjeta, que exista un
    * registro en la base de datos.
    **/

    // Consultamos si el registro existe en la base de datos.
    respuestaIoT validacion = validarRegistroEmpleado();

    // Si el codigo de la respuesta es menor que 0, ocurrio un problema con
    // el API.
    if(validacion.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(validacion.codigoRespuesta == 0) {
            // Cambiamos el ESTADO para la validacion de permisos.
            ESTADO = ESTADOS::VALIDAR_ACCESO_EMPLEADO;

        } else {
            // Si no existe, cambiamos el ESTADO a registro inexistente.
            ESTADO = ESTADOS::REPORTE_DATOS_NO_COINCIDEN_CON_REGISTRO;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;
    }

    return true;
};

bool reporteAcceso(void) {
    /*
    * Genera un reporte de acceso del
    * area en cuestion.
    **/

    // Realizamos el registro del reporte.
    respuestaIoT respuesta = registrarReporteAcceso();

    // Si el codigo de la respuesta es menor que 0, ocurrio un problema con
    // el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el ESTADO para la espera de ingreso de la tarjeta.
            ESTADO = ESTADOS::ESPERA_TARJETA;

        } else {
            Serial.print("[");
            Serial.print(respuesta.codigoRespuesta);
            Serial.println("]");
            // Si ocurrio un problema  con el registro del reporte
            // se cambia el ESTADO al ESTADO de fallo de registro.
            ESTADO = ESTADOS::REGISTRO_REPORTE_FALLIDO;
        }
    } else {
        // Si no se pudo comunicar con la API, se manda al
        // ESTADO de error de API.
        ESTADO = ESTADOS::ERROR_CONEXION_API;
    }

    return true;
};

bool reporteErrorAutentificacionTarjeta(void) {
    /*
    * Genera un reporte de tarjeta no autentificada, esto quiere
    * decir que la tarjeta ingresada no pertenece a las tarjetas de accesos
    * de los empleados.
    **/
    respuestaIoT respuesta = registrarReporteErrorAutentificacionTarjeta();

    // Si el codigo de la respuesta es menor que 0, ocurrio un problema con
    // el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el ESTADO para la espera de tarjeta.
            ESTADO = ESTADOS::ESPERA_TARJETA;

        } else {
            // Si no existe, cambiamos el ESTADO a registro de empleado inexistente fallido.
            ESTADO = ESTADOS::REGISTRO_REPORTE_FALLIDO;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;
    }

    return true;
};

bool reporteEmpleadoInexistente(void) {
    /*
    * Genera un reporte de datos de empleado leidos de la tarjeta
    * no coinciden con ningún registro en la base de datos.
    **/
    respuestaIoT respuesta = registrarReporteEmpleadoInexistente();

    // Si el codigo de la respuesta es menor que 0, ocurrio un problema con
    // el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el ESTADO para la espera de tarjeta.
            ESTADO = ESTADOS::ESPERA_TARJETA;

        } else {
            // Si no existe, cambiamos el ESTADO a registro de empleado inexistente fallido.
            ESTADO = ESTADOS::REGISTRO_REPORTE_FALLIDO;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;
    }

    return true;
};