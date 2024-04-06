/*
* Rutinas de comunicacion por medio de WiFi.
**/

bool inicializaWiFi(void) {
    /*
    * Rutina que conecta el cliente a la red wifi.
    * retorna FALSE si la coneccion no se pudo establecer
    * si la conexion fue establecida retorna TRUE.
    * */

    // Intentos de conexion realizados.
    int intentosRealizados = 0;

    // Encendemos el led del node indicando que se esta
    // conectando al wifi.
    digitalWrite(NODE_LED, LOW);

    // Iniciamos la conexion a la red.
    WiFi.begin(NETWORKING::ssid, NETWORKING::password);

    Serial.print("Iniciando conexion a red WiFi con SSID: ");
    Serial.println(NETWORKING::ssid);
    Serial.print("Conectando ");

    // Esperamos a que la conexion sea exitosa.
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print("-");

        // Realizamos el toggle del led del node.
        digitalWrite(NODE_LED, !digitalRead(NODE_LED));

        // Aumentamos la cantidad de intentos de conexion realizados.
        intentosRealizados++;

        // Si la cantidad de intentos maximos se excedio.
        if(intentosRealizados >= NETWORKING::intentosMaximos) {
            // Encendemos el led del node y apagamos el del esp indicando
            // que la conexion no se pudo realizar.
            digitalWrite(NODE_LED, HIGH);
            digitalWrite(ESP_LED, LOW);

            // Retornamos el estado de la conexion.
            return false;
        }

        // Esperamos por respuesta de la peticion de conexion.
        delay(NETWORKING::tiempoEsperaPorIntento);
    }

    Serial.println("\nConexion establecida");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Apagamos el led del node y encendemos el del esp indicando
    // que la conexion fue exitosa.
    digitalWrite(NODE_LED, LOW);
    digitalWrite(ESP_LED, HIGH);

    // Retorna el estado de la conexion.
    return true;
};