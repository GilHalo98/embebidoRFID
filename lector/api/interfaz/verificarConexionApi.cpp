/*
 * Interfaz de endpoint para verificar la conexion con la api.
 * */

respuestaIoT INTERFAZ::verificarConexionApi(void) {
    /*
     * Funcion de verificar conexion con api.
     * */

    // Instanciamos el cliente wifi.
    WiFiClient cliente;

    // Instanciamos el cliente http.
    HTTPClient consultaHTTP;

    // Concatenamos el uri de la API.
    String uri = String("http://")
        + String(IP_API)
        + String(":")
        + String(PORT_API)
        + String(VERSION_API)
        + String(ENDPOINTS::verificarApi);

    // Instanciamos el modelo de la respuesta del servidor.
    respuestaIoT respuesta;

    Serial.print("[HTTP] begin...\n");
    Serial.println(uri);

    if(consultaHTTP.begin(cliente, uri)) {
        // Iniciamos la conexion para la consulta
        // del estado del server API.
        // Agregamos headers a la consulta.
        consultaHTTP.addHeader("Content-Type", "API_KEY");
        consultaHTTP.addHeader("Accept", "application/json");
        consultaHTTP.addHeader("authorization", ACCESS_TOKEN);

        Serial.println("[HTTP] GET...\n");

        // Iniciamos la consulta de tipo GET.
        int httpCode = consultaHTTP.GET();

        // Verificamos que el codigo http sea valido.
        if(httpCode > 0) {
            // HTTP header has been send and Server
            // response header has been handled.
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // Se evalua la validez del codigo retornado.
            if(
                httpCode == HTTP_CODE_OK
                ||  httpCode == HTTP_CODE_MOVED_PERMANENTLY
            ) {
                // Si el codigo es OK (200) entonces la peticion
                // se realizo con exito.

                // Recuperamos los datos de
                // la consutla en formato string.
                String respuestaString = consultaHTTP.getString();

                // Instanciamos un buffer json.
                StaticJsonDocument<1024> bufferJson;

                //Deserealizamos la respuesta en formato string y
                //la pasamos al buffer.
                deserializeJson(bufferJson, respuestaString);

                // Mostramos la respuesta por el monitor serial.
                // serializeJson(bufferJson, Serial);

                // Agregamos el codigo de respuesta del
                // API al modelo de la respuesta.
                respuesta.codigoRespuesta = bufferJson[
                    "codigoRespuesta"
                ].as<int>();
            }
        } else {
            // Si el codigo no es valido, la peticio
            // retorna un codigo http invalido.
            Serial.printf(
                "[HTTP] GET... failed, error: %s\n",
                consultaHTTP.errorToString(httpCode).c_str()
            );
        }

        // Terminamos la consutla http.
        consultaHTTP.end();

    } else {
        // Si no se conecta con el API, ocurrio un error de conexion,
        // la respuesta se establece a nulo.
        Serial.println("Error, no se puede conectar a la API.");
        Serial.printf("[HTTP] Unable to connect\n");
    }

    return respuesta;
};
