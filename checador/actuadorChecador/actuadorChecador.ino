#include "./comun.hpp"
#include "./perifericos/perifericos.hpp"
#include "./coms/coms.hpp"
#include "./controladores/controladores.hpp"

void setup() {
    // Inicializamos el dispositivo.
    inicializacion();
};

void loop() {
    switch(estado) {
        case ESTADOS::ESPERAR_EVENTO: {
            // Este estado es manejado por el hilo de Wire.
            break;

        } case ESTADOS::CHEQUEO_OK: {
            chequeoOk();
            break;

        } case ESTADOS::CHEQUEO_FALLIDO: {
            chequeoFallido();
            break;

        } default: {
            break;
        }
    }

    // Delay del loop de 100ms.
    delay(100);
};
