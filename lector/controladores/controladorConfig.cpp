/*
* Controladores para la configuracion del dispositivo.
**/

bool CONTROLADOR_CONFIGURACION::configurarVariables(void) {
    /*
    * Controlador para configuar las variables del dispositivo.
    **/
    switch(COMS_SERIAL::checarPorEvento()) {
        case EVENTOS::CAMBIAR_PERMISO_PEDIDO: {
            Serial.print("Ingresa el bit de permiso: ");
            if(Serial.available() > 0) {
                PERMISO_PEDIDO = Serial.parseInt();

                Serial.println(PERMISO_PEDIDO);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::CAMBIAR_SSID: {
            // Este se unira con el de cambiar password y se creara
            // un ESTADO unico para la configuracion de los datos.
            Serial.print("Ingresa el SSID: ");
            if(Serial.available() > 0) {
                SSID = Serial.readString();

                SSID.replace("\r", "");

                Serial.println(SSID);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::CAMBIAR_PASSWORD: {
            Serial.print("Ingresa el PASSWORD: ");
            if(Serial.available() > 0) {
                PASSWORD = Serial.readString();
                PASSWORD.replace("\r", "");

                Serial.println(PASSWORD);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::CAMBIAR_PUERTO_API: {
            Serial.print("Ingresa el PUERTO del servidor API: ");
            if(Serial.available() > 0) {
                PORT_API = Serial.parseInt();

                Serial.println(PORT_API);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::CAMBIAR_IP_API: {
            Serial.print("Ingresa el IP del servidor API: ");
            if(Serial.available() > 0) {
                IP_API = Serial.readString();
                IP_API.replace("\r", "");

                Serial.println(IP_API);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::CAMBIAR_VERSION_API: {
            Serial.print("Ingresa el URL de la version API: ");
            if(Serial.available() > 0) {
                VERSION_API = Serial.readString();
                VERSION_API.replace("\r", "");

                Serial.println(VERSION_API);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::CAMBIAR_ACCESS_TOKEN: {
            Serial.print("Ingresa el ACCESS TOKEN del dispositivo: ");
            if(Serial.available() > 0) {
                ACCESS_TOKEN = Serial.readString();
                ACCESS_TOKEN.replace("\r", "");

                Serial.println(ACCESS_TOKEN);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::CAMBIAR_ACCION_OPCIONAL: {
            Serial.print("Ingresa la ACCION OPCIONAL: ");
            if(Serial.available() > 0) {
                ACCION_OPCIONAL = Serial.parseInt();

                Serial.println(ACCION_OPCIONAL);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::CAMBIAR_REGISTRAR_REPORTE_SALIDA: {
            Serial.print("Ingresa si REGISTRAR REPORTE SALIDA: ");
            if(Serial.available() > 0) {
                REGISTRAR_REPORTE_SALIDA = Serial.parseInt();

                Serial.println(REGISTRAR_REPORTE_SALIDA);
            } else {
                Serial.println("No hay informacion recivida");
            }
            Serial.println("\r\n");
            Serial.println(FLAGS::ESCRITURA_TERMINADA);
            break;

        } case EVENTOS::FINALIZAR_CONFIGURACION: {
            Serial.println("Guardando configuracion...");

            // Al finalizar la modificacion de la configuracion, esta se
            // guarda en la EEPROM.
            EEPROM_MEM::guardarConfiguracion();

            Serial.println("Configuracion guardada");

            // Mandamos el flag de termino de operacion.
            Serial.println("\r\n");
            Serial.println(FLAGS::OPERACION_TERMINADA);

            // Cambiamos el estado a carga de datos desde la eeprom para
            // confirmar que la operacion fue exitosa.
            ESTADO = ESTADOS::CARGAR_CONFIGURACION_EEPROM;
            break;

        } default: {
           break;
        }
    }

    return true;
}