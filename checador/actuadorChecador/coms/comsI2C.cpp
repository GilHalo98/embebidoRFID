/*
* Funcion de comunicacion I2C.
* */

bool inicializarI2C(void) {
    /*
    * Inicializa el bus de comunicacion I2C.
    * */

    // Inicializa el esclavo con la dirección dada.
    Wire.begin(direccion);

    // Asignamos la funcion para escuchar por eventos.
    Wire.onReceive(escucharEventos);

    return true;
};

bool escucharEventos(int totalDatos) {
    /*
    * Espera por un evento transmitido por medio de I2C.
    **/

    // El primer byte es el evento pasado por el master.
    int evento = Wire.read();

    Serial.println(evento);

    // Procesamos el evento.
    switch(evento) {
        case EVENTOS::OK_CHEQUEO: {
            // Si el evento es de acceso garantizado, se cambia
            // al estado del mismo.
            estado = ESTADOS::CHEQUEO_OK;
            break;

        } case EVENTOS::NO_OK_CHEQUEO: {
            // Si el evento es de acceso negado, se cambia al mismo.
            estado = ESTADOS::CHEQUEO_FALLIDO;
            break;

        } default: {
            break;
        }
    }

    return true;
};
