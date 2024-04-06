/*
 * Controlador de eventos del arduino nano.
 * */

bool chequeoOk(void) {
    /*
     * Controlador de chequeo OK.
     * */

    mostrarDatos(String("Chequeo OK"), 0, 0);

    // Cambiamos el estado a espera de evento.
    estado = ESTADOS::ESPERAR_EVENTO;

    return true;
};

bool chequeoFallido(void) {
    /*
     * Controlador de chequeo fallido.
     * */

    mostrarDatos(String("Chequeo Fallido"), 0, 0);

    // Cambiamos el estado a espera de evento.
    estado = ESTADOS::ESPERAR_EVENTO;

    return true;
};
