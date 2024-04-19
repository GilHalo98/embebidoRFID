bool CONTROLADOR_ERROR::errorEscritura(void) {
    // Mostramo informacion por el LCD.
    LCD::mostrarTexto("Error en escritura", 0, 0, true);
    LCD::mostrarTexto("de tarjeta...", 0, 1);

    // Cambiamos el estado a halt.
    ESTADO = ESTADOS::ESPERA_EVENTO;

    return true;
};

bool CONTROLADOR_ERROR::errorPerifericos(void) {
    // Mostramo informacion por el LCD.
    LCD::mostrarTexto("Error con", 0, 0, true);
    LCD::mostrarTexto("perifericos...", 0, 1);

    // Cambiamos el estado a halt.
    ESTADO = ESTADOS::HALT;

    return true;
};

bool CONTROLADOR_ERROR::errorAutentificacion(void) {
    // Mostramo informacion por el LCD.
    LCD::mostrarTexto("Error de", 0, 0, true);
    LCD::mostrarTexto("autentificacion", 0, 1);
    LCD::mostrarTexto("de tarjeta...", 0, 2);

    // Cambiamos el estado a halt.
    ESTADO = ESTADOS::ESPERA_EVENTO;

    return true;
};

bool CONTROLADOR_ERROR::halt(void) {
    /*
    * Controlador de halt del dispositivo.
    */

    return true;
};