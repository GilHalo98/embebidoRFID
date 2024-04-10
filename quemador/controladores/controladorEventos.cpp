/*
* Controlador de eventos.
**/

bool esperarEvento(void) {
    // Buffer para convertir los datos en char array.
    char buffer[255];

    // Escuchamos por eventos en el bus Serial.
    switch(checarPorEvento()) {
        case EVENTOS::INICIAR_GUARDADO_DATOS: {
            /*
             * Evento de inicio de guardado de datos.
             * */

            mostrarTexto("Reciviendo datos...", 0, 0, true);

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

            // Esperamos por 2 segundos a que se reciva el dato.
            // delay(2000);

            // Recivimos y almacenamos el dato.
            ID_EMPLEADO = recivirDato();

            mostrarTexto("ID:", 0, 1);
            itoa(ID_EMPLEADO, buffer, 10);
            mostrarTexto(buffer, 6, 1);

            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);

            break;

        } case EVENTOS::PERMISOS_ENVIADO: {
            /*
             * Evento de guardado de permisos del empleado.
             * */

            // Esperamos por 2 segundos a que se reciva el dato.
            // delay(2000);

            // Recivimos y almacenamos el dato.
            PERMISO_EMPLEADO = recivirDato();

            mostrarTexto("PERMISOS:", 0, 2);
            itoa(PERMISO_EMPLEADO, buffer, 10);
            mostrarTexto(buffer, 10, 2);

            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);

            break;

        } case EVENTOS::ROL_ENVIADO: {
            /*
             * Evento de guardado de permisos del empleado.
             * */

            // Esperamos por 2 segundos a que se reciva el dato.
            // delay(2000);

            // Recivimos y almacenamos el dato.
            ROL_EMPLEADO = recivirDato();

            mostrarTexto("ROL:", 0, 3);
            itoa(ROL_EMPLEADO, buffer, 10);
            mostrarTexto(buffer, 5, 3);

            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);

            break;

        } case EVENTOS::TERMINAR_GUARDADO_DATOS: {
            /*
             * Evento de termino de guardado de datos del empleado.
             * */

            mostrarTexto("INGRESA LA TARJETA..", 0, 0);

            // Cambiamos de estado al de espera de ingreso de tarjeta.
            estado = ESTADOS::ESPERA_TARJETA;

            break;

        } default: {
            break;
        }
    }

    return true;
};
