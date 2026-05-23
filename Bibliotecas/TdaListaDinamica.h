#ifndef TDALISTADINAMICA_H_INCLUDED
#define TDALISTADINAMICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "../Proyecto/Errores.h"
#define MINIMO( X , Y ) ( ( X ) <= ( Y ) ? ( X ) : ( Y ) )

typedef struct sNodoL
{
    void* info;
    unsigned tamInfo;
    struct sNodoL* sig;
} tNodoL;

typedef tNodoL* tLista;

void crearLista(tLista* pl);
int listaLlena(const tLista* pl, unsigned tamInfo);
int listaVacia(const tLista* pl);
int insertarAlFinal(tLista* pl, const void* info, unsigned tamInfo);
void vaciarLista(tLista* pl);
void mapLista(tLista* pl, void (*accion)(const void*, unsigned));

int insertarOrdenadoAdelante(tLista* pl, const void* info, unsigned tamInfo,
                             int (*cmp)(const void*, const void*), int duplicados,
                             void (*accion)(void*, const void*));

int insertarOrdenadoAtras(tLista* pl, const void* info, unsigned tamInfo,
                          int (*cmp)(const void*, const void*), int duplicados,
                          void (*accion)(void*, const void*));

int eliminarNodoPrimerApEnListaOrdenada(tLista* pl, void* info, unsigned tamBuffer,
                                        int (*cmp)(const void*, const void*));

int eliminarNodoTodasApEnListaOrdenada(tLista* pl, void* info,
                                       int (*cmp)(const void*, const void*));

int eliminarNodoPrimerApEnListaDesordenada(tLista* pl, void* info, unsigned tamBuffer,
                                           int (*cmp)(const void*, const void*));

int eliminarNodoTodasApEnListaDesordenada(tLista* pl, void* info,
                                          int (*cmp)(const void*, const void*));

void seleccionSortLista(tLista* pl, int (*cmp)(const void*, const void*));

#endif // TDALISTADINAMICA_H_INCLUDED
