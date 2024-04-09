/*
* Controlador de eventos.
**/

bool esperarPorEvento(void) {
    return true;
};

bool esperarPase(void) {
    // Espera un tiempo para que la puerta sea cerrada.
    if(millis() % 5000 == 0) {
        ESTADO = ESTADOS::CERRAR_PUERTA;
    }

    return true;
}

bool esperaConfirmacionSockets(void) {
    /*
    * Esperamos a la confirmacion de la conexion al socket server.
    */

    return true;
};