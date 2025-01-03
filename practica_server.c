/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "practica.h"
#include "test.h"

InfoAuto *
solicitarviaje_1(arg1, rqstp)
Posicion arg1;
struct svc_req *rqstp;
{

    static InfoAuto result;

    // Verificar si hay autos disponibles
    int disponibles = autosDisponibles();

    if (disponibles == 0)
    {
        return NULL;
    }

    // Buscamos el auto mas cercano al pasajero

    buscar_auto_cercano(arg1, &result);

    return (&result);
}

void *
terminarviaje_1(arg1, arg2, arg3, rqstp)
Posicion arg1;
float arg2;
char *arg3;
struct svc_req *rqstp;
{

    static char *result;

    // Buscamos el auto con las placas indicadas

    terminar_viaje(arg1, arg2, arg3);

    return ((void *)&result);
}

InfoServicio *
estadoservicio_1(rqstp)
struct svc_req *rqstp;
{

    static InfoServicio result;

    /*
     * insert server code here
     */

    return (&result);
}
