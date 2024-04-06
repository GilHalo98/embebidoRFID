/*
* Controlaodres de accesos del dispositivo.
**/

bool validarAcceso(void) {
    /*
    * Valida los permisos de acceso del empleado y se le garantiza o niega el acceso.
    **/

    // Valida los permisos de acceso del empleado con el pedido por el dispositivo.
    if((bufferPermisos[0] & permisoPedido) > 0) {
        // Si el bitwise es mayor que 0, se garantiza el acceso.
        accesoGarantizado = true;

    } else {
        // De lo contrario se niega el acceso.
        accesoGarantizado = false;
    }

    // Cambiamos el estado al envio del evento por medio de I2C.
    estado = ESTADOS::ENVIAR_EVENTO_ACCESO;

    return true;
};