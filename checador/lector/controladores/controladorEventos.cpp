/*
* Controlador de eventos.
**/

bool enviarEventoAcceso(void) {
    /*
    * Envia un evento por medio del bus I2C.
    **/

    // Inicializamos el evento a enviar.
    EVENTOS evento = EVENTOS::NEGAR_ACCESO;

    // Si el acceso fue garantizado, se cambia
    // el evento.
    if(accesoGarantizado) {
        evento = EVENTOS::GARANTIZAR_ACCESO;
    }

    // Se envia el evento por el bus de I2C.
    enviarEvento(DIRECCIONES_PERIFERICOS::ACTUADOR, evento);

    // Se cambia el estado al de registro de reporte de acceso.
    estado = ESTADOS::REPORTE_ACCESO;

    return true;
};
