/*
* Inicializa los GPIOS del embebido.
**/

bool inicializarGPIO(void) {
    /*
    * Inicializa los GPIO y los establece en un estado.
    **/

    Serial.println("Inicializando GPIO");

    return true;
};

bool toggleGPIO(int pin) {
    /*
    * Realiza un toggle sobre el GPIO dado.
    **/

    digitalWrite(pin, !digitalRead(pin));

    return true;
};