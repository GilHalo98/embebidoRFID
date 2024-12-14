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
    pinMode(RELE_2, OUTPUT);
    pinMode(RELE_3, OUTPUT);
    pinMode(RELE_4, OUTPUT);

    // Indicamos el estado de las salidas digitales
    digitalWrite(RELE_1, HIGH);
    digitalWrite(RELE_2, LOW);
    digitalWrite(RELE_3, HIGH);
    digitalWrite(RELE_4, HIGH);

    return true;
};

bool GPIO::toggleGPIO(int pin) {
    /*
    * Realiza un toggle sobre el GPIO dado.
    **/

    digitalWrite(pin, !digitalRead(pin));

    return true;
};

bool GPIO::mostrarEstatusTorreta(void) {
    /*
    * Mostramos el estatus del dispositivo por medio de la torreta.
    */
    if(ESTATUS_DISPOSITIVO == ESTATUS::BLOQUEADO) {
        digitalWrite(RELE_4, HIGH);
        digitalWrite(RELE_3, LOW);

    } else {
        digitalWrite(RELE_4, LOW);
        digitalWrite(RELE_3, HIGH);
    }

    return true;
};