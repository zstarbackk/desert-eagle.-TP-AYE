#include "indiceJugador.h"

int cmpIndiceJugadorPorNickname(const void* a, const void* b)
{
    const tIndiceJugador * jugadorX = (const tIndiceJugador*)a;
    const tIndiceJugador * jugadorY = (const tIndiceJugador*)b;
    return strcasecmp(jugadorX->nickname, jugadorY->nickname);
}
int cargarIndiceJugadores(tArbol* indice, const char* nombreArchivoIndice, const char* nombreArchivoUsuarios)
{
    FILE* archIdx;
    tIndiceJugador registroJugador;
    int ret;

    ret = abrirArchivo(&archIdx, nombreArchivoIndice, "rb");

    if(ret != EXITO)
    {
        printf("\nIndice no encontrado. Se regenera...\n\n");
        return regenerarIndiceJugadores(indice, nombreArchivoUsuarios, nombreArchivoIndice);
    }
    cargarArbolDesdeArchivoOrdenado(indice,archIdx,sizeof(tIndiceJugador));
    fclose(archIdx);
    return EXITO;
}

unsigned leerJugadorIndice(void* info, FILE* pf, unsigned* tam) {
    tJugadorArchivo jugador;
    tIndiceJugador* indice = (tIndiceJugador*)info;

    long pos = ftell(pf);

    if(fread(&jugador, sizeof(tJugadorArchivo), 1, pf) == 1) {

        strcpy(indice->nickname, jugador.nickname);

        indice->posicionRegistro = pos / sizeof(tJugadorArchivo);

        return *tam;
    }

    return 0; // Fin de archivo o error
}
int regenerarIndiceJugadores(tArbol* indice, const char* nombreArchivoUsuarios, const char * nombreArchivoIndice) {
    FILE* archIdx;
    int ret;

    printf("\nRegenerando indice de jugadores...\n");

    if (!crearArchivoIndice(nombreArchivoUsuarios, nombreArchivoIndice, sizeof(tIndiceJugador), leerJugadorIndice, cmpIndiceJugadorPorNickname)) {
        return 0;
    }


    ret = abrirArchivo(&archIdx, nombreArchivoIndice, "rb");
    if(ret != EXITO) {
        return ret;
    }


    vaciarArbol(indice);
    if (!cargarArbolDesdeArchivoOrdenado(indice, archIdx, sizeof(tIndiceJugador))) {
        fclose(archIdx);
        return 0;
    }
    fclose(archIdx);

    printf("Indice regenerado exitosamente.\n\n");
    return EXITO;
}

int guardarIndiceJugadores(const tArbol* indice, const char* nombreArchivoIndice)
{
    FILE *archTemp;
    int ret;

    ret=abrirArchivo(&archTemp,ARCH_TEMPORAL,"wb");
    if (ret !=EXITO)
        return ret;

    cargarArchivoDesdeArbolBalanceado(indice, archTemp);
    fclose(archTemp);

    remove(nombreArchivoIndice);
    rename(ARCH_TEMPORAL, nombreArchivoIndice);

    return EXITO;
}
//int buscarIndiceJugador(tArbol* indice, const char* nickname, tIndiceJugador* indiceEncontrado)
//{
//    tArbol * nodoAux;
//
//    strcpy(indiceEncontrado->nickname, nickname);
//    if((nodoAux =buscarNodo(indice,indiceEncontrado, cmpIndiceJugadorPorNickname))!=NULL)
//    {
//        printf("Usuario encontrado!");
//        return EXITO;
//    }
//    return JUGADOR_INEXISTENTE;
//}
int buscarIndiceJugador(tArbol* indice, const char* nickname, tIndiceJugador* indiceEncontrado)
{
    tIndiceJugador clave;

    strcpy(clave.nickname, nickname);

    if(buscarNodo2(indice,
                   indiceEncontrado,
                   &clave,
                   sizeof(tIndiceJugador),
                   cmpIndiceJugadorPorNickname))
    {
        return EXITO;
    }

    return JUGADOR_INEXISTENTE;
}

int insertarIndiceJugador(tArbol* indice, const char* nickname, unsigned posicionRegistro){
    tIndiceJugador jug;

    strcpy(jug.nickname, nickname);
    jug.posicionRegistro = posicionRegistro;

    if(!insertarEnArbolBRec(indice, &jug, sizeof(tIndiceJugador), cmpIndiceJugadorPorNickname))
        return ERROR_MEMORIA;

    return EXITO;
}

