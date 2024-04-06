/*
* Controlador de eventos.
**/

bool esperarEvento(void) {

    // Escuchamos por eventos en el bus Serial.
    switch(checarPorEvento()) {
        case EVENTOS::INICIAR_GUARDADO_DATOS: {
            /*
             * Evento de inicio de guardado de datos.
             * */

            // Receteamos los datos del empleado a guardar.
            ID_EMPLEADO = 0;
            PERMISO_EMPLEADO = 0;

            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);

            break;

        } case EVENTOS::ID_ENVIADO: {
            /*
             * Evento de guardado del ID del empleado.
             * */

            Serial.print("Ingrese id del empleado: ");

            // Esperamos por 2 segundos a que se reciva el dato.
            // delay(2000);

            // Recivimos y almacenamos el dato.
            ID_EMPLEADO = recivirDato();
            Serial.println(ID_EMPLEADO);

            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);

            break;

        } case EVENTOS::PERMISOS_ENVIADO: {
            /*
             * Evento de guardado de permisos del empleado.
             * */

            Serial.print("Ingrese permisos del empleado: ");

            // Esperamos por 2 segundos a que se reciva el dato.
            // delay(2000);

            // Recivimos y almacenamos el dato.
            PERMISO_EMPLEADO = recivirDato();
            Serial.println(PERMISO_EMPLEADO);

            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);

            break;

        } case EVENTOS::TERMINAR_GUARDADO_DATOS: {
            /*
             * Evento de termino de guardado de datos del empleado.
             * */

            // Cambiamos de estado al de espera de ingreso de tarjeta.
            estado = ESTADOS::ESPERA_TARJETA;

            break;

        } default: {
            break;
        }
    }

    return true;
};
