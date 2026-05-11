#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED
#define ADELANTE 'F'
#define ATRAS    'B'

typedef enum
{
    ACTOR_JUGADOR,
    ACTOR_BANDIDO
} tTipoActor;        // Asigna un valor diferente a cada opcion

typedef struct
{
    tTipoActor tipoActor;
    int idActor;
    char direccion;
    unsigned cantidad;
} tMovimiento;

#endif // MOVIMIENTO_H_INCLUDED
