/*
 * Controlador del EEPROM para guardar y cargar información permanente.
 * */

bool inicializarEEPROM(void) {
    // Inicializamos la memoria EEPROM.
    EEPROM.begin(DIMENCION_EEPROM);

    Serial.println("Memoria EEPROM inicializada");

    return true;
};

bool guardarConfiguracion(void) {
    // Instanciamos una estructura con la configuracion.
    CONFIGURACION_DISPOSITIVO configuracion;

    // Parseamos el string a un char array y lo
    // guardamos en la configuración.
    SSID.toCharArray(
        configuracion.ssid, SSID.length() + 1
    );

    // Parseamos el string a un char array y lo
    // guardamos en la configuración.
    PASSWORD.toCharArray(
        configuracion.password, PASSWORD.length() + 1
    );

    // Parseamos el string a un char array y lo
    // guardamos en la configuración.
    ACCESS_TOKEN.toCharArray(
        configuracion.accessToken, ACCESS_TOKEN.length() + 1
    );

    // Parseamos el string a un char array y lo
    // guardamos en la configuración.
    IP_API.toCharArray(
        configuracion.ipApi, IP_API.length() + 1
    );

    // Parseamos el string a un char array y lo
    // guardamos en la configuración.
    VERSION_API.toCharArray(
        configuracion.versionApi, VERSION_API.length() + 1
    );

    // Guardamos la accion opcional del dispositivo.
    configuracion.accionOpcional = ACCION_OPCIONAL;

    // Guardamos el bit del permiso pedido en la configuración.
    configuracion.permisoPedido = PERMISO_PEDIDO;

    // Guardamos el puerto del servidor api en la configuración.
    configuracion.portApi = PORT_API;

    // Ponemos la estructua en la memoria EEPROM, que en este
    // caso especifico es simulada por la memoria FLASH.
    EEPROM.put(0, configuracion);

    // Guardamos los cambios.
    EEPROM.commit();

    return true;
};

bool cargarConfiguracion(void) {
    // Instanciamos una estructura con la configuracion.
    CONFIGURACION_DISPOSITIVO configuracion;

    // Cargamos la configuración de la memoria EEPROM.
    EEPROM.get(0, configuracion);

    // Cargamos el bit del permiso de la configuración.
    PERMISO_PEDIDO = configuracion.permisoPedido;

    // Cargamos el bit del permiso de la configuración.
    PORT_API = configuracion.portApi;

    // Cargamos la SSID en el string.
    SSID = configuracion.ssid;

    // Cargamos el PASSWORD en el string.
    PASSWORD = configuracion.password;

    // Cargamos el ACCESS_TOKEN del dispositivo de la configuración.
    ACCESS_TOKEN = configuracion.accessToken;

    // Cargamos la ip del servidor api en la configuracion.
    IP_API = configuracion.ipApi;

    // Cargamos la version del servidor api en la configuracion.
    VERSION_API = configuracion.versionApi;

    // Cargamos la accion opcional del dispositivo.
    ACCION_OPCIONAL = configuracion.accionOpcional;

    return true;
};