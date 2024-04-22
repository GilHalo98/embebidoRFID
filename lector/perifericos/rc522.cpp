/*
* Rutinas para el RC522.
**/

bool RFID::inicializarRFID(void) {
    /*
    * Inicializamos el RC522.
    */

    Serial.println("Inicializando RC522");

    // Inicializamos el PCD.
    mfrc522.PCD_Init();

    // Verificamos que se pueda leer el registro de version del RC522.
    byte version = mfrc522.PCD_ReadRegister(MFRC522::VersionReg);

    // Si la version es invalida, retorna false.
    if((version == 0x00) || (version == 0xFF)) {
        return false;
    } else {
        // Mostramos la version del firmware.
        mfrc522.PCD_DumpVersionToSerial();
    }

    // Poblamos las llaves de lectura y escritura.
    for(byte i = 0; i < 6; i++) {
        keyA.keyByte[i] = 0xFF;
        keyB.keyByte[i] = 0xFF;
    }

    return true;
};

bool RFID::limpiarBufferRFID(void) {
    /*
    * Limpiamos el buffer del RC522
    * y reseteamos la bandera de acceso.
    **/

    // Limpiamos el buffer del rfid.
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

    // Reseteamos los datos del empelado.
    ACCESO_GARANTIZADO = false;
    ID_EMPLEADO = "";
    ACCESOS = 0;

    return true;
};

bool RFID::lecturaRFID(void) {
    /*
    * Realizamos la lectura de los datos del empleado en la tarjeta.
    **/

    // Calculamos el tamaño del buffer del id.
    byte size = sizeof(bufferID);

    // Realizamos la lectua del bloque.
    STATUS_RC522 = mfrc522.MIFARE_Read(
        BLOCK_ID,
        bufferID,
        &size
    );

    // Si la lectura no fue existosa.
    if(STATUS_RC522 != MFRC522::STATUS_OK) {
        // mandamos el ESTADO a error de lectura.
        return false;
    }

    // Calculamos el tamaño del buffer de los permisos.
    size = sizeof(bufferPermisos);

    // Realizamos la lectua del bloque.
    STATUS_RC522 = mfrc522.MIFARE_Read(
        BLOCK_PERMISOS,
        bufferPermisos,
        &size
    );

    // Si la lectura no fue existosa.
    if(STATUS_RC522 != MFRC522::STATUS_OK) {
        // mandamos el ESTADO a error de lectura.
        return false;
    }

    // Guardamos el id del empleado extraido.
    ID_EMPLEADO = String(bufferID[0], DEC);

    // Guardamos el permiso del empelado extraido.
    ACCESOS = bufferPermisos[0];

    return true;
};

bool RFID::hayTarjetaPresente(void) {
    /*
    * Verificamos que haya una tarjeta presente en el RC522.
    **/

    if(!mfrc522.PICC_IsNewCardPresent()) {
        return false;
    }

    if(!mfrc522.PICC_ReadCardSerial()) {
        return false;
    }

    return true;
};

bool RFID::autentificarTarjetaLectura(int numeroBlock) {
    /*
    * Autentificamos la tarjeta para la lectura.
    **/

    // Autenticamos la llave con la tarjeta.
    STATUS_RC522 = mfrc522.PCD_Authenticate(
        MFRC522::PICC_CMD_MF_AUTH_KEY_A,
        numeroBlock,
        &keyA,
        &(mfrc522.uid)
    );

    // Si se autentica exitosamente.
    if(STATUS_RC522 == MFRC522::STATUS_OK) {
        return true;

    }

    return false;
};
