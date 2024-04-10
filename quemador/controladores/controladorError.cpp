bool errorEscritura(void) {
    mostrarTexto("Error en escritura", 0, 0, true);
    mostrarTexto("de tarjeta...", 0, 1);

    return true;
};

bool errorPerifericos(void) {
    mostrarTexto("Error con", 0, 0, true);
    mostrarTexto("perifericos...", 0, 1);

    return true;
};

bool errorAutentificacion(void) {
    mostrarTexto("Error de", 0, 0, true);
    mostrarTexto("autentificacion", 0, 1);
    mostrarTexto("de tarjeta...", 0, 2);

    return true;
};