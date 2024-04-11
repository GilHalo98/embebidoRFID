/*
* Rutinas para el LCD.
**/

bool inicializarLCD(void) {
    /*
    * Rutina de inicializacion del display LCD.
    */

    // Inicializamos el lcd.
    DISPLAY_LCD.init();

    // Encendemos la luz del lcd.
    DISPLAY_LCD.backlight();

    // limpiamos el lcd.
    DISPLAY_LCD.clear();

    // Mostramos el mensaje de inicializando dispositivo.
    DISPLAY_LCD.setCursor(0, 0);
    DISPLAY_LCD.print("INICIALIZANDO");

    return true;
};

bool mostrarTexto(const char texto[], int x, int y, bool limpiar) {
    /*
    * Mostramos un texto en el lcd.
    */

    // Se limpia el lcd si asi se indica.
    if(limpiar) {
        DISPLAY_LCD.clear();
    }

    // Movemos el cursor a la posicion indicada.
    DISPLAY_LCD.setCursor(x, y);

    // Mostramos el texto.
    DISPLAY_LCD.print(texto);

    return true;
};