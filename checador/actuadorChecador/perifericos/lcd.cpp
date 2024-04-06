/*
 * Controlador del periferico LCD.
 * */

bool inicializarLCD(void) {
    /*
     * Inicializa el periferico del LCD.
     * */

    // Inicializamos el LCD.
    lcd.begin(COLUMNAS_LCD, FILAS_LCD);

    return true;
};

bool mostrarDatos(String datos, int fila, int columna) {
    /*
    * Muestra un string en el display.
    * */

    // Limpiamos el LCD.
    lcd.clear();

    // Establecemos el cursor a la fila y columna dada.
    lcd.setCursor(fila, columna);

    // Mostramos el String dado.
    lcd.print(datos);

    return true;
};
