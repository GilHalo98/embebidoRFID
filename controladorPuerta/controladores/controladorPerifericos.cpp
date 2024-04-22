// Abrimos la puerta.
bool CONTROLADOR_PERIFERICOS::abrirPuerta(void) {
    digitalWrite(RELE_1, LOW);

    // Cambiamos el estado por espera de evento.
    ESTADO = ESTADOS::ESPEAR_APERTURA;
    return true;
};

// Esperamos a que la puerta sea abierta.
bool CONTROLADOR_PERIFERICOS::esperarApertura(void) {
    delay(2000);

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
    digitalWrite(RELE_2, LOW);
    // Cambiamos el estado por espera de evento.
    ESTADO = ESTADOS::ESPEAR_CIERRE;
    return true;
};

// Esperamos a que la puerta sea cerrada.
bool CONTROLADOR_PERIFERICOS::esperarCierre(void) {
    delay(2000);

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
    if(millis() % 5000 == 0) {
        ESTADO = ESTADOS::CERRAR_PUERTA;
    }

    return true;
}