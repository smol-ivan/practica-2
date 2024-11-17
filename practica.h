/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PRACTICA_H_RPCGEN
#define _PRACTICA_H_RPCGEN

#define RPCGEN_VERSION	199506

#include <rpc/rpc.h>


struct Posicion {
	int x;
	int y;
};
typedef struct Posicion Posicion;
#ifdef __cplusplus
extern "C" bool_t xdr_Posicion(XDR *, Posicion*);
#elif __STDC__
extern  bool_t xdr_Posicion(XDR *, Posicion*);
#else /* Old Style C */
bool_t xdr_Posicion();
#endif /* Old Style C */


struct InfoAuto {
	Posicion posicion_auto;
	char *tipo;
	float tarifa;
	char *placa;
};
typedef struct InfoAuto InfoAuto;
#ifdef __cplusplus
extern "C" bool_t xdr_InfoAuto(XDR *, InfoAuto*);
#elif __STDC__
extern  bool_t xdr_InfoAuto(XDR *, InfoAuto*);
#else /* Old Style C */
bool_t xdr_InfoAuto();
#endif /* Old Style C */


struct InfoServicio {
	int viajes_realizados;
	int autos_libres;
	float ganancia;
};
typedef struct InfoServicio InfoServicio;
#ifdef __cplusplus
extern "C" bool_t xdr_InfoServicio(XDR *, InfoServicio*);
#elif __STDC__
extern  bool_t xdr_InfoServicio(XDR *, InfoServicio*);
#else /* Old Style C */
bool_t xdr_InfoServicio();
#endif /* Old Style C */


struct terminarviaje_1_argument {
	Posicion arg1;
	float arg2;
	char *arg3;
};
typedef struct terminarviaje_1_argument terminarviaje_1_argument;
#ifdef __cplusplus
extern "C" bool_t xdr_terminarviaje_1_argument(XDR *, terminarviaje_1_argument);
#elif __STDC__
extern  bool_t xdr_terminarviaje_1_argument(XDR *, terminarviaje_1_argument);
#else /* Old Style C */
bool_t xdr_terminarviaje_1_argument();
#endif /* Old Style C */


#define DISPLAY_PRG ((rpc_uint)0x20000199)
#define DISPLAY_VER ((rpc_uint)1)

#ifdef __cplusplus
#define solicitarViaje ((rpc_uint)1)
extern "C" InfoAuto * solicitarviaje_1(Posicion , CLIENT *);
extern "C" InfoAuto * solicitarviaje_1_svc(Posicion , struct svc_req *);
#define terminarViaje ((rpc_uint)2)
extern "C" void * terminarviaje_1(Posicion , float , char *, CLIENT *);
extern "C" void * terminarviaje_1_svc(Posicion , float , char *, struct svc_req *);
#define estadoServicio ((rpc_uint)3)
extern "C" InfoServicio * estadoservicio_1(CLIENT *);
extern "C" InfoServicio * estadoservicio_1_svc(struct svc_req *);

#elif __STDC__
#define solicitarViaje ((rpc_uint)1)
extern  InfoAuto * solicitarviaje_1(Posicion , CLIENT *);
extern  InfoAuto * solicitarviaje_1_svc(Posicion , struct svc_req *);
#define terminarViaje ((rpc_uint)2)
extern  void * terminarviaje_1(Posicion , float , char *, CLIENT *);
extern  void * terminarviaje_1_svc(Posicion , float , char *, struct svc_req *);
#define estadoServicio ((rpc_uint)3)
extern  InfoServicio * estadoservicio_1(CLIENT *);
extern  InfoServicio * estadoservicio_1_svc(struct svc_req *);

#else /* Old Style C */
#define solicitarViaje ((rpc_uint)1)
extern  InfoAuto * solicitarviaje_1();
extern  InfoAuto * solicitarviaje_1_svc();
#define terminarViaje ((rpc_uint)2)
extern  void * terminarviaje_1();
extern  void * terminarviaje_1_svc();
#define estadoServicio ((rpc_uint)3)
extern  InfoServicio * estadoservicio_1();
extern  InfoServicio * estadoservicio_1_svc();
#endif /* Old Style C */

#endif /* !_PRACTICA_H_RPCGEN */
