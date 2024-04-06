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
            // Cambiamos el estado para la validacion de permisos.
            estado = ESTADOS::VALIDAR_ACCESO_EMPLEADO;

        } else {
            // Si no existe, cambiamos el estado a registro inexistente.
            estado = ESTADOS::REPORTE_DATOS_NO_COINCIDEN_CON_REGISTRO;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        estado = ESTADOS::ERROR_CONEXION_API;
    }

    return true;
};

bool registrarReporteAcceso(void) {
    /*
    * Genera un reporte de acceso del
    * area en cuestion.
    **/

    // Inicializamos el tipo de reporte a registrar como de acceso negado.
    TIPOS_REPORTES tipoReporte = TIPOS_REPORTES::EMPLEADO_ACCESO_NEGADO;

    // Inicializamos el contenido del reporte.
    String contenidoReporte = String("Peticion de acceso a zona");

    // Si se garantizo el acceso.
    if(accesoGarantizado) {
        // Cambiamos el tipo de reporte a registrar como de acceso garantizado.
        tipoReporte = TIPOS_REPORTES::EMPLEADO_ACCESO_GARANTIZADO;
    }

    // Realizamos el registro del reporte.
    respuestaIoT respuesta = registrarReporteAcceso(
        tipoReporte,
        contenidoReporte
    );

    // Si el codigo de la respuesta es menor que 0, ocuffio un problema con
    // el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el estado para la espera de ingreso de la tarjeta.
            estado = ESTADOS::ESPERA_TARJETA;
        } else {
            // Si ocurrio un problema  con el registro del reporte
            // se cambia el estado al estado de fallo de registro.
            estado = ESTADOS::REGISTRO_REPORTE_FALLIDO;
        }
    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estado de error de API.
        estado = ESTADOS::ERROR_CONEXION_API;
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
            // Cambiamos el estado para la espera de tarjeta.
            estado = ESTADOS::ESPERA_TARJETA;

        } else {
            // Si no existe, cambiamos el estado a registro de empleado inexistente fallido.
            estado = ESTADOS::REGISTRO_REPORTE_FALLIDO;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        estado = ESTADOS::ERROR_CONEXION_API;
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
            // Cambiamos el estado para la espera de tarjeta.
            estado = ESTADOS::ESPERA_TARJETA;

        } else {
            // Si no existe, cambiamos el estado a registro de empleado inexistente fallido.
            estado = ESTADOS::REGISTRO_REPORTE_FALLIDO;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        estado = ESTADOS::ERROR_CONEXION_API;
    }

    return true;
};

bool reporteFalloPerifericos(void) {
    /*
    * Genera un reporte de fallos en la inicializacion de los perifericos
    * del lector.
    **/
    respuestaIoT respuesta = registrarReporteErrorPerifericos();

    // Si el codigo de la respuesta es menor que 0, ocurrio un problema con
    // el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el estado por el de error de perifericos
            estado = ESTADOS::ERROR_PERIFERICOS;

        } else {
            // Si no existe, cambiamos el estado a registro de empleado inexistente fallido.
            estado = ESTADOS::REGISTRO_REPORTE_FALLIDO;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        estado = ESTADOS::ERROR_CONEXION_API;
    }

    return true;
};
