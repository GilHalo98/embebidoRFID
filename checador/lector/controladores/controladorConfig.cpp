/*
* Controladores para la configuracion del dispositivo.
**/

bool configurarVariables(void) {
    /*
    * Controlador para configuar las variables del dispositivo.
    **/

    switch(checarPorEvento()) {
        case EVENTOS::FINALIZAR_CONFIGURACION: {
            estado = ESTADOS::CONEXION_RED;
            break;

        } default: {
           break;
        }
    }

    return true;
}
