/*
* Funcion de comunicacion I2C.
* */

bool inicializarI2C(void) {
    /*
    * Inicializa el bus de comunicacion I2C.
    * */

    // Inicializa el esclavo con la dirección dada.
    Wire.begin();

    Serial.println("I2C Inicializado");

    return true;
};

bool enviarEvento(
    DIRECCIONES_PERIFERICOS direccion,
    EVENTOS eventoAEnviar
) {
    /*
    * Envia un evento y sus respectivos datos por medio del bus I2C.
    * */
    Serial.print("Enviando evento ");
    Serial.print(eventoAEnviar);
    Serial.print(" a ");
    Serial.println(direccion);
    Wire.beginTransmission(direccion);
    Wire.write(eventoAEnviar);
    Wire.endTransmission();
    return true;
};
