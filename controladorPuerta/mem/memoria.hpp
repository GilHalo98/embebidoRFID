/*
* Manejo de memoria EEPROM para almacenar y leer información
* de configuración del dispositivo.
*/

// Inicializamos la memoria EEPROM.
bool inicializarEEPROM(void);

// Guarda la configuración del dispositivo, red y api en la EEPROM.
bool guardarConfiguracion(void);

// Carga la configuracion del dispostivo, red y api de la EEPROM.
bool cargarConfiguracion(void);

#include "./eeprom.cpp"
