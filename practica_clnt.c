/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "practica.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

InfoAuto *
solicitarviaje_1(arg1, clnt)
	Posicion arg1;
	CLIENT *clnt;
{
	static InfoAuto clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, solicitarViaje, xdr_Posicion, &arg1, xdr_InfoAuto, &clnt_res, TIMEOUT) != RPC_SUCCESS)
		return (NULL);
	return (&clnt_res);
}

void *
terminarviaje_1(arg1, arg2, arg3, clnt)
	Posicion arg1;
	float arg2;
	char *arg3;
	CLIENT *clnt;
{
	terminarviaje_1_argument arg;
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	arg.arg3 = arg3;
	if (clnt_call(clnt, terminarViaje, xdr_terminarviaje_1_argument, &arg, xdr_void, &clnt_res, TIMEOUT) != RPC_SUCCESS)
		return (NULL);
	return ((void *)&clnt_res);
}

InfoServicio *
estadoservicio_1(clnt)
	CLIENT *clnt;
{
	static InfoServicio clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, estadoServicio, xdr_void, NULL, xdr_InfoServicio, &clnt_res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	return (&clnt_res);
}
