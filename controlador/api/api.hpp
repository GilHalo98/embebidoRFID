// Incluimos los modelos a usar en la interfaz.
#include "modelos/respuestaIoT.cpp"

namespace ENDPOINTS {
    /*
    * Namespace para las URI's de la API.
    */

    // Endpoint para probar conexion con API.
    const char* verificarApi = "IoT/verificar/api";

    // Endpoint de validacion de empleados.
    const char* validarRegistroEmpleado = "IoT/validar/registro/empleado";

    // Endpoint de registro de reporte de error de autentificacion de tarjeta.
    const char* registrarReporteErrorAutentificacionTarjeta = "IoT/registrar/reporte/errorAutentificacionTarjeta";

    // Endpoint de registro de reporte de empleado inexistente.
    const char* registrarReporteEmpleadoInexistente = "IoT/registrar/reporte/empleadoInexistente";

    // Endpoint de registro de reporte de actividad iniciada.
    const char* registrarReporteActividadIniciada = "IoT/registrar/reporte/actividad/iniciada";

    // Endpoint de registro de reporte de actividad finalizada.
    const char* registrarReporteActividadFinalizada = "IoT/registrar/reporte/actividad/finalizada";
};

namespace INTERFAZ {
    // Prototipo de funcion que verifica la conexion con el API.
    respuestaIoT verificarConexionApi(void);

    // Prototipo de funcion que consulta el registro de usuarios.
    respuestaIoT validarRegistroEmpleado(void);

    // Prototipo de funcion que registra un reporte de
    // error de autentificacion de tarjeta.
    respuestaIoT registrarReporteErrorAutentificacionTarjeta(void);

    // Registra un reporte de empleado indexistente en el registro.
    respuestaIoT registrarReporteEmpleadoInexistente(void);

    // Registro de un reporte de actividad terminada.
    respuestaIoT registroReporteActividadFinalizada(void);

    // Registro de un reporte de actividad iniciada.
    respuestaIoT registroReporteActividadIniciada(void);
};

// Importamos las funciones de la interfaz.
#include "interfaz/reporteErrorAutentificacion.cpp"
#include "interfaz/reporteEmpleadoInexistente.cpp"
#include "interfaz/reporteActividadFinalizada.cpp"
#include "interfaz/validarRegistroEmpleado.cpp"
#include "interfaz/reporteInicioActividad.cpp"
#include "interfaz/verificarConexionApi.cpp"
