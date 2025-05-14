// Mandamos a home la puerta.
bool CONTROLADOR_PERIFERICOS::enviarPuertaHome(void) {
    /*
    * Enviamos la pueta a posicion Home.
    */

    // Esperamos a que cierre la puerta.
    if(!GPIO::puertaEstaCerrada()) {
        // Si la puerta no esta cerrada, entonces cerramos la puerta.
        digitalWrite(RELE_2, LOW);

        return false;
    }

    // Desactivamos el rele del motor.
    digitalWrite(RELE_2, HIGH);

    // Cambiamos de estado a esperar por evento.
    ESTADO = ESTADOS::ESPERA_EVENTO;

    // Cambiamos el status del dispositivo.
    ESTATUS_DISPOSITIVO = ESTATUS::LIBRE;

    return true;
};

// Abrimos la puerta.
bool CONTROLADOR_PERIFERICOS::abrirPuerta(void) {
    // Activamos el rele del motor.
    digitalWrite(RELE_1, LOW);

    // Cambiamos el estado por espera de evento.
    ESTADO = ESTADOS::ESPEAR_APERTURA;
    return true;
};

// Esperamos a que la puerta sea abierta.
bool CONTROLADOR_PERIFERICOS::esperarApertura(void) {
    // Esperamos a que la puerta abra.
    if(!GPIO::puertaEstaAbierta()) {
        return false;
    }

    // Desactivamos el rele del motor.
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
        ESTATUS_DISPOSITIVO = ESTATUS::LIBRE;
    }

    return true;
};

// cerramos la puerta.
bool CONTROLADOR_PERIFERICOS::cerrarPuerta(void) {
    // Activamos el rele del motor.
    digitalWrite(RELE_2, LOW);

    // Cambiamos el estado por espera de evento.
    ESTADO = ESTADOS::ESPEAR_CIERRE;
    return true;
};

// Esperamos a que la puerta sea cerrada.
bool CONTROLADOR_PERIFERICOS::esperarCierre(void) {
    // Esperamos a que se detecte la puerta cerrada.
    if(!GPIO::puertaEstaCerrada()) {
        return false;
    }

    // Desactivamos el rele del motor.
    digitalWrite(RELE_2, HIGH);

    // Cambiamos el estado por espera de evento.
    ESTADO = ESTADOS::ESPERA_EVENTO;

    // Cambiamos el estatus del dispositivo
    // a desocupado.
    ESTATUS_DISPOSITIVO = ESTATUS::LIBRE;

    // Si se bloquea la puerta, se cambia el estatus del dispositivo.
    if(BLOQUEAR_PUERTA) {
        ESTATUS_DISPOSITIVO = ESTATUS::BLOQUEADO;
    }

    // Si se desbloquea la puerta, se cambia el estatus del dispositivo.
    if(DESBLOQUEAR_PUERTA) {
        ESTATUS_DISPOSITIVO = ESTATUS::LIBRE;
    }

    // Reseteamos las variables de bloquear
    // y desbloquear puerta a falso.
    BLOQUEAR_PUERTA = false;
    DESBLOQUEAR_PUERTA = false;

    return true;
};

bool CONTROLADOR_PERIFERICOS::esperarPase(void) {
    // Espera un tiempo para que la puerta sea cerrada.
    delay(TIEMPO_PUERTA_ABIERTA);

    // Cambiamos de estado a cerrar puerta.
    ESTADO = ESTADOS::CERRAR_PUERTA;

    return true;
};