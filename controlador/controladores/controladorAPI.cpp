/*
* Controlador del API.
**/

bool CONTROLADOR_API::verificarEstadoApi(void) {
    /*
     * Verifica la conexion con la API.
     * */

    // Consultamos el estado de la API.
    respuestaIoT respuesta = INTERFAZ::verificarConexionApi();

    Serial.print("[API] CODIGO DE RESPUESTA DE API: ");
    Serial.println(respuesta.codigoRespuesta);

    // Si el codigo de la respuesta es menor que 0, ocurrio
    // un problema con la API.
    if(respuesta.codigoRespuesta < 0) {
        // En caso de error de conexion, mandamos el estado
        // a error de conexon con api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;

        return false;
    }

    // Si no hay problema con la conexion de api, cambiamos el estado
    // al estado de inicializacion de conexion con el servidor socket.
    ESTADO = ESTADOS::INICIALIZAR_CONEXION_SOCKETS;

    return true;
};

bool CONTROLADOR_API::validarExistenciaEmpleado(void) {
    /*
    * Valida los datos del empleado en la tarjeta, que exista un
    * registro en la base de datos.
    **/

    // Consultamos si el registro existe en la base de datos.
    respuestaIoT respuesta = INTERFAZ::validarRegistroEmpleado();

    Serial.print("[API] CODIGO DE RESPUESTA DE API: ");
    Serial.println(respuesta.codigoRespuesta);

    // Si el codigo de la respuesta es menor que 0, ocurrio
    // un problema con el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el ESTADO para la validacion de permisos.
            ESTADO = ESTADOS::VALIDAR_INICIO_ACTIVIDAD;

        } else {
            // Si no existe, cambiamos el ESTADO a registro inexistente.
            ESTADO = ESTADOS::REPORTE_DATOS_NO_COINCIDEN_CON_REGISTRO;

            return false;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;

        return false;
    }

    return true;
};

bool CONTROLADOR_API::reporteErrorAutentificacionTarjeta(void) {
    /*
    * Genera un reporte de tarjeta no autentificada, esto quiere
    * decir que la tarjeta ingresada no pertenece a las
    * tarjetas de accesos de los empleados.
    **/
    respuestaIoT respuesta = INTERFAZ::registrarReporteErrorAutentificacionTarjeta();

    Serial.print("[API] CODIGO DE RESPUESTA DE API: ");
    Serial.println(respuesta.codigoRespuesta);

    // Si el codigo de la respuesta es menor que 0, ocurrio un
    // problema con el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el ESTADO para la espera de tarjeta.
            ESTADO = ESTADOS::ESPERA_TARJETA;

        } else {
            // Si no existe, cambiamos el ESTADO a registro de
            // empleado inexistente fallido.
            ESTADO = ESTADOS::REGISTRO_REPORTE_FALLIDO;

            return false;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;

        return false;
    }

    return true;
};

bool CONTROLADOR_API::reporteEmpleadoInexistente(void) {
    /*
    * Genera un reporte de datos de empleado leidos de la tarjeta
    * no coinciden con ningún registro en la base de datos.
    **/
    respuestaIoT respuesta = INTERFAZ::registrarReporteEmpleadoInexistente();

    Serial.print("[API] CODIGO DE RESPUESTA DE API: ");
    Serial.println(respuesta.codigoRespuesta);

    // Si el codigo de la respuesta es menor que 0, ocurrio
    // un problema con el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el ESTADO para la espera de tarjeta.
            ESTADO = ESTADOS::ESPERA_TARJETA;

        } else {
            // Si no existe, cambiamos el ESTADO a registro de
            // empleado inexistente fallido.
            ESTADO = ESTADOS::REGISTRO_REPORTE_FALLIDO;

            return false;
        }

    } else {
        // Si no se pudo comunicar con la API, se manda al
        // estao de error de api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;

        return false;
    }

    return true;
};

bool CONTROLADOR_API::reporteInicioActividad(void) {
    /*
    * Genera un reporte de actividad iniciada.
    **/

    // Realizamos el registro del reporte.
    respuestaIoT respuesta = INTERFAZ::registroReporteActividadIniciada();

    Serial.print("[API] CODIGO DE RESPUESTA DE API: ");
    Serial.println(respuesta.codigoRespuesta);

    // Si el codigo de la respuesta es menor que 0, ocurrio
    // un problema con el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el ESTADO de inicio de actividad.
            ESTADO = ESTADOS::EN_ACTIVIDAD;

        } else {
            Serial.print("[");
            Serial.print(respuesta.codigoRespuesta);
            Serial.println("]");

            // Si ocurrio un problema  con el registro del reporte
            // se cambia el ESTADO al ESTADO de fallo de registro.
            ESTADO = ESTADOS::REGISTRO_REPORTE_FALLIDO;

            return false;
        }

    } else {
        // Cambiamos el estado a error con conexion a api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;

        return false;
    }

    if(CREDENCIALES_VALIDAS) {
        // Si las credenciales fueron validadas, cambiamos al estado
        // de iniciar actividad.
        ESTADO = ESTADOS::INICIO_ACTIVIDAD;

    } else {
        // Si no es asi, entonces cambiamos al
        // estado de espera de tarjeta.
        ESTADO = ESTADOS::ESPERA_TARJETA;
    }

    return true;
};

bool CONTROLADOR_API::reporteActividadFinalizada(void) {
    /*
    * Genera un reporte de actividad finalizada.
    **/

    // Realizamos el registro del reporte.
    respuestaIoT respuesta = INTERFAZ::registroReporteActividadFinalizada();

    Serial.print("[API] CODIGO DE RESPUESTA DE API: ");
    Serial.println(respuesta.codigoRespuesta);

    // Si el codigo de la respuesta es menor que 0, ocurrio
    // un problema con el API.
    if(respuesta.codigoRespuesta >= 0) {
        // Si el codigo es 0, no hubo problema en la consulta.
        if(respuesta.codigoRespuesta == 0) {
            // Cambiamos el ESTADO para la espera de
            // ingreso de la tarjeta.
            ESTADO = ESTADOS::ESPERA_TARJETA;

        } else {
            Serial.print("[");
            Serial.print(respuesta.codigoRespuesta);
            Serial.println("]");

            // Si ocurrio un problema  con el registro del reporte
            // se cambia el ESTADO al ESTADO de fallo de registro.
            ESTADO = ESTADOS::REGISTRO_REPORTE_FALLIDO;

            return false;
        }

    } else {
        // Cambiamos el estado a error con conexion a api.
        ESTADO = ESTADOS::ERROR_CONEXION_API;

        return false;
    }

    return true;
};