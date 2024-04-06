/*
* Controlador de eventos.
**/

bool enviarEventoAcceso(void) {
    /*
    * Envia un evento por medio de sockets.
    **/

    // Se envia el evento de acceso por sockets.
    enviarPeticionAcceso();

    // Se cambia el ESTADO al de registro de reporte de acceso.
    ESTADO = ESTADOS::REPORTE_ACCESO;

    return true;
};


bool esperaConfirmacionSockets(void) {
    /*
    * Esperamos a la confirmacion de la conexion al socket server.
    */

    return true;
};