/*
* Inicializa los GPIOS del embebido.
**/

bool GPIO::inicializarGPIO(void) {
    /*
    * Inicializa los GPIO y los establece en un ESTADO.
    **/

    Serial.println("Inicializando GPIO");

    // Indicamos el uso de los pines como salidas digitales.
    pinMode(RELE_1, OUTPUT);

    // Indicamos el estado de las salidas digitales
    digitalWrite(RELE_1, HIGH);

    return true;
};

bool GPIO::toggleGPIO(int pin) {
    /*
    * Realiza un toggle sobre el GPIO dado.
    **/

    digitalWrite(pin, !digitalRead(pin));

    return true;
};