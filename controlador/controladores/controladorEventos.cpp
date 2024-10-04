/*
* Controlador de eventos.
**/
bool CONTROLADOR_SOCKETS::esperaConfirmacionSockets(void) {
    /*
    * Esperamos a la confirmacion de la conexion al socket server.
    */

    if(ESTATUS_DISPOSITIVO == ESTATUS::CONECTADO) {
        // Si se reintento la conexion, se pasa al estado
        // de inicializacion de perifericos.
        ESTADO = ESTADOS::INICIALIZAR_PERIFERICOS;

        return true;
    }

    return false;
};

bool CONTROLADOR_SOCKETS::dispositivoBloqueado(void) {
    /*
    * Bloqueamos el uso de la maquina.
    */
    return true;
};