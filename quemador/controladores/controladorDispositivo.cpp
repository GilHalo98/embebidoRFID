/*
* Controlador de estados del dispositivo.
*/

bool pruebaDispositivo(void) {
    /*
    * Realiza una prueba al dispositivo y retorna el resultado por
    * serial.
    */

    // Retoramos el estado actual del dispositivo.
    // Serial.println(estado);

    // Cambiamos al estado de espera por evento.
    estado = ESTADOS::ESPERA_EVENTO;

    return true;
}

bool escrituraFinalizada(void) {
    /*
    * Termina la escritura a la tarjeta de manera exitosa.
    *
    */

    // Cambiamos el estado al estado de espera por evento.
    estado = ESTADOS::ESPERA_EVENTO;

    // Enviamos una bandera de operación terminda.
    Serial.println(FLAGS::OPERACION_TERMINADA);

    // Vaciamos el buffer serial.
    vaciarBuffer();

    mostrarTexto("ESCRITURA TERMINADA ", 0, 0, true);

    return true;
}