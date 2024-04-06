/*
* Rutinas para el RC522.
**/

bool inicializarRFID(void) {
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

bool limpiarBufferRFID(void) {
    /*
    * Limpiamos el buffer del RC522
    * y reseteamos la bandera de acceso.
    **/

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    accesoGarantizado = false;

    return true;
};

bool lecturaRFID(void) {
    /*
    * Realizamos la lectura de los datos del empleado en la tarjeta.
    **/

    // Calculamos el tamaño del buffer del id.
    byte size = sizeof(bufferID);

    // Realizamos la lectua del bloque.
    statusRC522 = mfrc522.MIFARE_Read(1, bufferID, &size);

    // Si la lectura no fue existosa.
    if(statusRC522 != MFRC522::STATUS_OK) {
        // mandamos el estado a error de lectura.
        return false;
    }

    // Calculamos el tamaño del buffer de los permisos.
    size = sizeof(bufferPermisos);

    // Realizamos la lectua del bloque.
    statusRC522 = mfrc522.MIFARE_Read(2, bufferPermisos, &size);

    // Si la lectura no fue existosa.
    if(statusRC522 != MFRC522::STATUS_OK) {
        // mandamos el estado a error de lectura.
        return false;
    }

    return true;
};

bool hayTarjetaPresente(void) {
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

bool autentificarTarjetaLectura(int numeroBlock) {
    /*
    * Autentificamos la tarjeta para la lectura.
    **/

    // Autenticamos la llave con la tarjeta.
    statusRC522 = mfrc522.PCD_Authenticate(
        MFRC522::PICC_CMD_MF_AUTH_KEY_A,
        numeroBlock,
        &keyA,
        &(mfrc522.uid)
    );

    // Si se autentica exitosamente.
    if(statusRC522 == MFRC522::STATUS_OK) {
        return true;

    }

    return false;
};