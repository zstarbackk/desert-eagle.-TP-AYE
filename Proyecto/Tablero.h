#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "../Bibliotecas/listaDobleCircular.h"
#include "../Bibliotecas/TdaListaDinamica.h"
#include "Config.h"

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
} tTipoEvento;

typedef struct
{
    tTipoEvento tipoEvento;
    int tieneJugador;
    unsigned numeroCasillero;
    unsigned idBandido;
} tCasillero;

typedef struct
{
    tListaDC casilleros;
    tCursorDC inicio;
    tCursorDC fin;
    unsigned cantidadCasilleros;
    tLista bandidos;
} tTablero;

void inicializarTablero(tTablero* tablero);
int generarTablero(tTablero* tablero, const tConfig* config);
int validarTablero(tTablero* tablero);
void vaciarTablero(tTablero* tablero);
int exportarTablero(const tTablero* tablero, char* nombreArchivo);
void mostrarTablero(const tTablero* tablero, FILE* salida);

// Primitivas de tablero útiles para otros módulos


#endif // TABLERO_H_INCLUDED

