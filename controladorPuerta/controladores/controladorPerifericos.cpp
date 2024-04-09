// Abrimos la puerta.
bool abrirPuerta(void) {
    digitalWrite(RELE_1, LOW);

    // Cambiamos el estado por espera de evento.
    ESTADO = ESTADOS::ESPEAR_APERTURA;
    return true;
};

// Esperamos a que la puerta sea abierta.
bool esperarApertura(void) {
    if(millis() % 2000 == 0) {
        digitalWrite(RELE_1, HIGH);

        if(EJECUTAR_SECUENCIA_COMPLETA) {
            // Cambiamos el estado por espera de puerta abierta
            // para el pase del empleado.
            ESTADO = ESTADOS::ESPERA_PUERTA_ABIERTA;
        } else {
            // Cambiamos el estado por espera de evento.
            ESTADO = ESTADOS::ESPERA_EVENTO;

            // Cambiamos el estatus del dispositivo
            // a desocupado.
            ESTATUS_DISPOSITIVO = ESTATUS::DESOCUPADO;
        }
    }

    return true;
};

// cerramos la puerta.
bool cerrarPuerta(void) {
    digitalWrite(RELE_2, LOW);
    // Cambiamos el estado por espera de evento.
    ESTADO = ESTADOS::ESPEAR_CIERRE;
    return true;
};

// Esperamos a que la puerta sea cerrada.
bool esperarCierre(void) {
    if(millis() % 2000 == 0) {
        digitalWrite(RELE_2, HIGH);
        // Cambiamos el estado por espera de evento.
        ESTADO = ESTADOS::ESPERA_EVENTO;

        // Cambiamos el estatus del dispositivo
        // a desocupado.
        ESTATUS_DISPOSITIVO = ESTATUS::DESOCUPADO;
    }

    return true;
};