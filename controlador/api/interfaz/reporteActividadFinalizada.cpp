/*
 * Interfaz de endpoint de registro de reporte.
 * */

respuestaIoT INTERFAZ::registroReporteActividadFinalizada(void) {
    /*
    * Función de consulta de usuarios de la API.
    */

    // Instanciamos el cliente WiFi.
    WiFiClient cliente;

    // Instanciamos el tipo de cliente a http.
    HTTPClient registroHTTP;

    // Concatenamos el uri de la API.
    String uri = String("http://")
        + String(IP_API)
        + String(":")
        + String(PORT_API)
        + String(VERSION_API)
        + String(ENDPOINTS::registrarReporteActividadFinalizada);

    // Instanciamos el modelo de la respuesta del servidor.
    respuestaIoT respuesta;

    Serial.print("[HTTP] begin...\n");
    Serial.println(uri);

    if(registroHTTP.begin(cliente, uri)) {
        // Iniciamos la conexion para la consulta de datos.

        // Agregamos headers a la consulta.
        registroHTTP.addHeader("Content-Type", "API_KEY");
        registroHTTP.addHeader("Accept", "application/json");
        registroHTTP.addHeader(
            "Content-Type",
            "application/x-www-form-urlencoded"
        );
        registroHTTP.addHeader("authorization", ACCESS_TOKEN);

        // Generamos el cuerpo del post.
        String body = String("idEmpleadoVinculado=")
            + String(ID_EMPLEADO);

        Serial.print("[HTTP] POST...\n");

        // Iniciamos la consulta de tipo POST.
        int httpCode = registroHTTP.POST(body);

        // Verificamos que el codigo http sea valido.
        if(httpCode > 0) {
            // HTTP header has been send and Server
            // response header has been handled
            Serial.printf("[HTTP] POST... code: %d\n", httpCode);

            // Se evalua la validez del codigo retornado.
            if(
                httpCode == HTTP_CODE_OK
                || httpCode == HTTP_CODE_MOVED_PERMANENTLY
            ) {
                // Si el codigo es OK (200) entonces la peticion
                // se realizo con exito.

                // Recuperamos los datos de la
                // consulta en formato String.
                String respuestaString = registroHTTP.getString();

                // Instanciamos un buffer json.
                StaticJsonDocument<1024> bufferJson;

                // Deserealizamos la respuesta en formato string y la
                // pasamos al buffer json.
                deserializeJson(bufferJson, respuestaString);

                // Mostramos la respuesta por el monitor serial.
                // serializeJson(bufferJson, Serial);

                // Agregamos el codigo de respuesta del API al
                // modelo de la respuesta.
                respuesta.codigoRespuesta = bufferJson[
                    "codigoRespuesta"
                ].as<int>();
            }

        } else {
            // Si el codigo no es valido, la peticion
            // retorna un codigo http invalido.
            Serial.printf(
                "[HTTP] POST... failed, error: %s\n",
                registroHTTP.errorToString(httpCode).c_str()
            );
        }

        // Terminamos la consulta http.
        registroHTTP.end();

    } else {
        // Si no se conecta con el API, ocurrio un error de conexion
        // la respuesta se establece a nulo.
        // respuesta = NULL;
        Serial.println("Error, no se puede conectar a la API.");
        Serial.printf("[HTTP] Unable to connect\n");
    }

    return respuesta;
};
