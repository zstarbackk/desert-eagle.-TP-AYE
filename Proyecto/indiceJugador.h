#ifndef INDICEJUGADOR_H_INCLUDED
#define INDICEJUGADOR_H_INCLUDED
#include "../Bibliotecas/arbol.h"
#include <stdio.h>
typedef struct
{
    char nickname[TAM_NICKNAME];
    unsigned posicionRegistro;
} tIndiceJugador;

int cmpIndiceJugadorPorNickname(const void* a, const void* b);

int cargarIndiceJugadores(tArbol* indice, const char* nombreArchivoIndice, const char * nombreArchivoUsuarios);
int regenerarIndiceJugadores(tArbol* indice, const char * nombreArchivoUsuarios);
int guardarIndiceJugadores(const tArbol* indice, const char* nombreArchivoIndice);
int buscarIndiceJugador(tArbol* indice, const char* nickname, tIndiceJugador* indiceEncontrado);
int insertarIndiceJugador(tArbol* indice, const char* nickname, unsigned posicionRegistro);

#endif // INDICEJUGADOR_H_INCLUDED
