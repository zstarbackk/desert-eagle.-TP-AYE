#include "indiceJugador.h"

int cmpIndiceJugadorPorNickname(const void* a, const void* b)
{
    tIndiceJugador * jugadorX = (tIndiceJugador*)a;
    tIndiceJugador * jugadorY = (tIndiceJugador*)b;
    return strcmpi(jugadorX->nickname, jugadorY->nickname);
}
int cargarIndiceJugadores(tArbol* indice, const char* nombreArchivoIndice, const char * nombreArchivoUsuarios)
{
    FILE * archIdx;
    tIndiceJugador registroJugador;
    int ret;

    ret=abrirArchivo(&archIdx,nombreArchivoIndice,"rb");
    if(ret != EXITO)
    {
        printf("\nIndice no encontrado. Se regenera...\n\n");
        return regenerarIndiceJugadores(indice, nombreArchivoUsuarios);
    }

    while(fread(&registroJugador, sizeof(tIndiceJugador),1,archIdx)==1)
            insertarIndiceJugador(indice, registroJugador.nickname,registroJugador.posicionRegistro);

    fclose(archIdx);
    return EXITO;
}
int regenerarIndiceJugadores(tArbol* indice, const char * nombreArchivoUsuarios)
{
    tJugadorArchivo registroArchivo;
    FILE * pf;
    unsigned offsetReg;
    int ret;

    ret=abrirArchivo(&pf, nombreArchivoUsuarios,"rb");
    if(ret != EXITO)
        return ret;

    printf("\n\nRegenerando Indice jugadores...");
    offsetReg = 0;
    while(fread(&registroArchivo, sizeof(tJugadorArchivo), 1, pf) == 1)
    {
       insertarIndiceJugador(indice, registroArchivo.nickname, offsetReg);
       offsetReg += sizeof(tJugadorArchivo);
    }
    fclose(pf);
    printf("Indice regenerado exitosamente.\n\n");
    return EXITO;
}

int guardarIndiceJugadores(const tArbol* indice, const char* nombreArchivoIndice)
{
    FILE *archTemp;
    int ret;

    ret=abrirArchivo(&archTemp,"indice_temp.idx","wb");
    if (ret !=EXITO)
        return ret;

    cargarArchivoDesdeArbolBalanceado(indice, archTemp);
    fclose(archTemp);

    remove(nombreArchivoIndice);
    rename("indice_temp.idx", nombreArchivoIndice);

    return EXITO;
}
int buscarIndiceJugador(tArbol* indice, const char* nickname, tIndiceJugador* indiceEncontrado)
{
    tArbol * nodoAux;

    strcpy(indiceEncontrado->nickname, nickname);
    if((nodoAux =buscarNodo(indice,indiceEncontrado, cmpIndiceJugadorPorNickname))!=NULL)
    {
        printf("Usuario encontrado!");
        return EXITO;
    }
    return JUGADOR_INEXISTENTE;
}

int insertarIndiceJugador(tArbol* indice, const char* nickname, unsigned posicionRegistro)
{
    tIndiceJugador jug;
    strcpy(jug.nickname, nickname);
    jug.posicionRegistro = posicionRegistro;
    insertarEnArbolBRec(indice, &jug, sizeof(tIndiceJugador),cmpIndiceJugadorPorNickname);
    return EXITO;
}
