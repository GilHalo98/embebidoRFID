/*
* Rutinas de comunicacion por medio de WiFi.
**/

bool COMS_WIFI::inicializarWiFi(void) {
    /*
    * Rutina que conecta el cliente a la red wifi.
    * retorna FALSE si la coneccion no se pudo establecer
    * si la conexion fue establecida retorna TRUE.
    * */

    // Intentos de conexion realizados.
    int intentosRealizados = 0;

    // Encendemos el led del node indicando que se esta
    // conectando al wifi.
    digitalWrite(ESP_LED, LOW);

    // Iniciamos la conexion a la red.
    WiFi.begin(
        SSID,
        PASSWORD
    );

    Serial.print("Iniciando conexion a red WiFi con SSID: ");
    Serial.println(SSID);
    Serial.print("Conectando ");

    // Esperamos a que la conexion sea exitosa.
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print("-");

        // Realizamos el toggle del led del node.
        digitalWrite(ESP_LED, !digitalRead(ESP_LED));

        // Aumentamos la cantidad de intentos de conexion realizados.
        intentosRealizados++;

        // Si la cantidad de intentos maximos se excedio.
        if(intentosRealizados >= INTENTOS_MAXIMOS) {
            // Encendemos el led del node y apagamos el del
            // esp indicando que la conexion no se pudo realizar.
            digitalWrite(ESP_LED, HIGH);
            Serial.println("\n");

            // Retornamos el ESTADO de la conexion.
            return false;
        }

        // Esperamos por respuesta de la peticion de conexion.
        delay(TIEMPO_ESPERA_CONEXION);
    }

    Serial.println("\nConexion establecida");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Dejamos encendido el led del ESP indicando una conexion exitosa.
    digitalWrite(ESP_LED, LOW);

    // Retorna el ESTADO de la conexion.
    return true;
};
