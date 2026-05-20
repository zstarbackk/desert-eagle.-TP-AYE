#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED

typedef enum
{
    ADELANTE='F',
    ATRAS='B'
} tDireccion;
typedef enum
{
    ACTOR_JUGADOR,
    ACTOR_BANDIDO
} tTipoActor;        // Asigna un valor diferente a cada opcion

typedef struct
{
    tTipoActor tipoActor;
    int idActor;
    tDireccion direccion;
    unsigned cantidad;
} tMovimiento;

#endif // MOVIMIENTO_H_INCLUDED
