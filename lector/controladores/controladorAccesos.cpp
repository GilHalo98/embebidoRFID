/*
* Controlaodres de accesos del dispositivo.
**/

bool validarAcceso(void) {
    /*
    * Valida los permisos de acceso del empleado y se le garantiza o niega el acceso.
    **/

    // Valida los permisos de acceso del empleado con el pedido por el dispositivo.
    if((ACCESOS & PERMISO_PEDIDO) > 0) {
        // Si el bitwise es mayor que 0, se garantiza el acceso.
        ACCESO_GARANTIZADO = true;

    } else {
        // De lo contrario se niega el acceso.
        ACCESO_GARANTIZADO = false;
    }

    // Cambiamos el ESTADO al envio del evento por medio de I2C.
    ESTADO = ESTADOS::ENVIAR_EVENTO_ACCESO;

    return true;
};