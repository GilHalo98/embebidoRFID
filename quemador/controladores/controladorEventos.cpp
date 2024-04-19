/*
* Controlador de eventos.
**/

bool CONTROLADOR_EVENTOS::esperarEvento(void) {
    // Buffer para convertir los datos en char array.
    char buffer[255];

    // Escuchamos por eventos en el bus Serial.
    switch(COMS_SERIAL::checarPorEvento()) {
        case EVENTOS::INICIAR_GUARDADO_DATOS: {
            /*
             * Evento de inicio de guardado de datos.
             * */

            LCD::mostrarTexto("Reciviendo datos...", 0, 0, true);

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
            ID_EMPLEADO = COMS_SERIAL::recivirDato();

            LCD::mostrarTexto("ID:", 0, 1);
            itoa(ID_EMPLEADO, buffer, 10);
            LCD::mostrarTexto(buffer, 6, 1);

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
            PERMISO_EMPLEADO = COMS_SERIAL::recivirDato();

            LCD::mostrarTexto("PERMISOS:", 0, 2);
            itoa(PERMISO_EMPLEADO, buffer, 10);
            LCD::mostrarTexto(buffer, 10, 2);

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
            ROL_EMPLEADO = COMS_SERIAL::recivirDato();

            LCD::mostrarTexto("ROL:", 0, 3);
            itoa(ROL_EMPLEADO, buffer, 10);
            LCD::mostrarTexto(buffer, 5, 3);

            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);

            break;

        } case EVENTOS::TERMINAR_GUARDADO_DATOS: {
            /*
             * Evento de termino de guardado de datos del empleado.
             * */

            LCD::mostrarTexto(">INGRESA LA TARJETA<", 0, 0);

            // Cambiamos de ESTADO al de espera de ingreso de tarjeta.
            ESTADO = ESTADOS::ESPERA_TARJETA;

            break;

        } default: {
            break;
        }
    }

    return true;
};

bool CONTROLADOR_EVENTOS::escrituraFinalizada(void) {
    /*
    * Termina la escritura a la tarjeta de manera exitosa.
    *
    */

    // Cambiamos el ESTADO al ESTADO de espera por evento.
    ESTADO = ESTADOS::ESPERA_EVENTO;

    // Enviamos una bandera de operación terminda.
    Serial.println(FLAGS::OPERACION_TERMINADA);

    // Vaciamos el buffer serial.
    COMS_SERIAL::vaciarBuffer();

    LCD::mostrarTexto("ESCRITURA TERMINADA ", 0, 0, true);

    return true;
}