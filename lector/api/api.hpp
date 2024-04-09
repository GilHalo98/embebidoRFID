// Incluimos los modelos a usar en la interfaz.
#include "modelos/respuestaIoT.cpp"

namespace ENDPOINTS {
    /*
    * Namespace para las URI's de la API.
    */

    // Endpoint de validacion de empleados.
    const char* validarRegistroEmpleado = "IoT/validar/empleado";

    // Endpoint de registro de reportes.
    const char* registrarReporteAcceso = "IoT/registrar/reporte/acceso";

    // Endpoint de registro de reporte de error de autentificacion de tarjeta.
    const char* registrarReporteErrorAutentificacionTarjeta = "IoT/registrar/reporte/errorAutentificacionTarjeta";

    // Endpoint de registro de reporte de empleado inexistente.
    const char* registrarReporteEmpleadoInexistente = "IoT/registrar/reporte/empleadoInexistente";

};

// Prototipo de funcion que consulta el registro de usuarios.
respuestaIoT validarRegistroEmpleado(void);

// Prototipo de funcion que registra un reporte de acceso.
respuestaIoT registrarReporteAcceso(TIPOS_REPORTES, String);

// Prototipo de funcion que registra un reporte de error de autentificacion de tarjeta.
respuestaIoT registrarReporteErrorAutentificacionTarjeta(void);

// Registra un reporte de empleado indexistente en el registro.
respuestaIoT registrarReporteEmpleadoInexistente(void);

// Importamos las funciones de la interfaz.
#include "interfaz/validarRegistroEmpleado.cpp"
#include "interfaz/registrarReporteAcceso.cpp"
#include "interfaz/reporteErrorAutentificacion.cpp"
#include "interfaz/reporteEmpleadoInexistente.cpp"