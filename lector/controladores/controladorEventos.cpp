/*
* Controlador de eventos.
**/

bool enviarEventoAcceso(void) {
    /*
    * Envia un evento por medio de sockets.
    **/

    // Se envia el evento de acceso por sockets.
    switch(ACCION_OPCIONAL) {
        case ACCIONES_OPCIONALES::NINGUNA: {
            enviarPeticionAcceso();
            break;

        } case ACCIONES_OPCIONALES::BLOQUEAR_PUERTA_AL_CERRAR: {
            enviarPeticionAccesoBloqueo();
            break;

        } case ACCIONES_OPCIONALES::DESBLOQUEAR_PUERTA_AL_ABRIR: {
            enviarPeticionAccesoDesbloqueo();
            break;

        } default: {
            break;
        }
    }

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