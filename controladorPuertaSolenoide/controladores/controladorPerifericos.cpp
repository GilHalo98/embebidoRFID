// Abrimos la puerta.
bool CONTROLADOR_PERIFERICOS::abrirPuerta(void) {
    // Desactivamos el segundo relevador.
    digitalWrite(RELE_2, HIGH);

    if(EJECUTAR_SECUENCIA_COMPLETA) {
        // Cambiamos el estado por espera de evento.
        ESTADO = ESTADOS::ESPERAR_USO_PUERTA;

        // Actualizamos el tiempo.
        TEMPORIZADOR = millis();

    } else {
        // Cambiamos el estado por espera de evento.
        ESTADO = ESTADOS::ESPERA_EVENTO;

        // Cambiamos el estatus del dispositivo
        // a desocupado.
        ESTATUS_DISPOSITIVO = ESTATUS::LIBRE;
    }

    return true;
};

bool CONTROLADOR_PERIFERICOS::esperarUsoPuerta(void) {
    // Espera un tiempo para que la puerta sea usada.
    if(millis() - TEMPORIZADOR >= TIEMPO_ESPERA_USO_PUERTA) {
        // Cambiamos el estado al de cerrar la puerta.
        ESTADO = ESTADOS::CERRAR_PUERTA;
    }

    return true;
}

// cerramos la puerta.
bool CONTROLADOR_PERIFERICOS::cerrarPuerta(void) {
    // Activamos el segundo relevador.
    digitalWrite(RELE_2, LOW);

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