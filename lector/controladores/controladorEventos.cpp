/*
* Controlador de eventos.
**/

bool CONTROLADOR_SOCKETS::enviarEventoAcceso(void) {
    /*
    * Envia un evento por medio de sockets.
    **/

    Serial.print("Accion opcional: ");
    Serial.println(ACCION_OPCIONAL);

    // Se envia el evento de acceso por sockets.
    switch(ACCION_OPCIONAL) {
        case ACCIONES_OPCIONALES::NINGUNA: {
            COMS_SOCKETS::enviarPeticionAcceso();
            break;

        } case ACCIONES_OPCIONALES::BLOQUEAR_PUERTA_AL_CERRAR: {
            COMS_SOCKETS::enviarPeticionAccesoBloqueo();
            break;

        } case ACCIONES_OPCIONALES::DESBLOQUEAR_PUERTA_AL_ABRIR: {
            COMS_SOCKETS::enviarPeticionAccesoDesbloqueo();
            break;

        } default: {
            break;
        }
    }

    // Se cambia el ESTADO al de registro de reporte de acceso.
    ESTADO = ESTADOS::REPORTE_ACCESO;

    return true;
};


bool CONTROLADOR_SOCKETS::esperaConfirmacionSockets(void) {
    /*
    * Esperamos a la confirmacion de la conexion al socket server.
    */

    return true;
};