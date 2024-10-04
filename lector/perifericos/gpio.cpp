/*
* Inicializa los GPIOS del embebido.
**/

bool GPIO::inicializarGPIO(void) {
    /*
    * Inicializa los GPIO y los establece en un ESTADO.
    **/

    Serial.println("Inicializando GPIO");

    // Indicamos el uso de los pines como salidas digitales.
    pinMode(LED_OK, OUTPUT);
    pinMode(LED_ERROR, OUTPUT);

    // Indicamos el estado de las salidas digitales
    digitalWrite(LED_OK, LOW);
    digitalWrite(LED_ERROR, LOW);

    return true;
};

bool GPIO::toggleGPIO(int pin) {
    /*
    * Realiza un toggle sobre el GPIO dado.
    **/

    digitalWrite(pin, !digitalRead(pin));

    return true;
};

bool GPIO::identificarError(void) {
    /*
    * Actiiva el timer y el led de error.
    **/

    // Instanciamos el temporizador del led de error.
    TIMER_LED_ERROR = millis();

    // Encendemos el led de error.
    digitalWrite(LED_ERROR, HIGH);

    return true;
};

bool GPIO::identificarOK(void) {
    /*
    * Actiiva el timer y el led de ok.
    **/

    // Instanciamos el temporizador del led de ok.
    TIMER_LED_OK = millis();

    // Encendemos el led de ok.
    digitalWrite(LED_OK, HIGH);

    return true;
};