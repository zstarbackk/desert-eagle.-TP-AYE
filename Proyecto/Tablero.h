#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include <stdlib.h>
#include "../Bibliotecas/listaDobleCircular.h"
#include "../Bibliotecas/TdaListaDinamica.h"
#include "Config.h"
#include "Movimiento.h"
#define PORCENTAJE_MINIMO_EVENTOS 70
#define MAX_DADO 6

typedef enum
{
    DESPEJADO,
    INICIO,
    SALIDA,
    PREMIO,
    VIDA_EXTRA,
    OASIS,
    TORMENTA
} tTipoEvento;  //Asigna valores distintos a cada evento estático para no hacer muchos defines

typedef struct
{
    tTipoEvento tipoEvento;
    int tieneJugador;
    unsigned numeroCasillero;
    unsigned  idBandido;  //
} tCasillero;
typedef struct
{
    tListaDC casilleros;
    tPosicion inicio;
    tPosicion fin;
    unsigned cantidadCasilleros;
    tLista bandidos;
}tTablero;


int generarTablero(tTablero* tablero, const tConfig* config);
int validarTablero(tTablero* tablero);
void vaciarTablero(tTablero* tablero);
int exportarTablero(const tTablero* tablero, char* nombreArchivo);
void mostrarTablero(const tTablero* tablero, FILE* salida);
void probarGenerarTablero(void);


#endif // TABLERO_H_INCLUDED
