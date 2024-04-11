// Incluimos los modelos a usar en la interfaz.
#include "modelos/respuestaIoT.cpp"

namespace ENDPOINTS {
    /*
    * Namespace para las URI's de la API.
    */

    // Endpoint de validacion de empleados.
    const char* validarRegistroEmpleado = "IoT/validar/registro/empleado";

    // Endpoint de registro de reporte de chequeo.
    const char* registrarReporteChequeo = "IoT/registrar/reporte/chequeo";

    // Endpoint de registro de reporte de error de autentificacion de tarjeta.
    const char* registrarReporteErrorAutentificacionTarjeta = "IoT/registrar/reporte/errorAutentificacionTarjeta";

    // Endpoint de registro de reporte de empleado inexistente.
    const char* registrarReporteEmpleadoInexistente = "IoT/registrar/reporte/empleadoInexistente";

};

// Prototipo de funcion que consulta el registro de usuarios.
respuestaIoT validarRegistroEmpleado(void);

// Prototipo de funcion que registra un reporte de acceso.
respuestaIoT registrarReporteChequeo(void);

// Prototipo de funcion que registra un reporte de
// error de autentificacion de tarjeta.
respuestaIoT registrarReporteErrorAutentificacionTarjeta(void);

// Registra un reporte de empleado indexistente en el registro.
respuestaIoT registrarReporteEmpleadoInexistente(void);

// Importamos las funciones de la interfaz.
#include "interfaz/validarRegistroEmpleado.cpp"
#include "interfaz/registrarReporteChequeo.cpp"
#include "interfaz/reporteErrorAutentificacion.cpp"
#include "interfaz/reporteEmpleadoInexistente.cpp"