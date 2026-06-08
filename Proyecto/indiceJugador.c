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
        return regenerarIndiceJugadores(indice, nombreArchivoUsuarios);
    }

    while(fread(&registroJugador, sizeof(tIndiceJugador), 1, archIdx) == 1)
    {
        ret = insertarIndiceJugador(indice, registroJugador.nickname, registroJugador.posicionRegistro);

        if(ret != EXITO)
        {
            fclose(archIdx);
            return ret;
        }
    }

    fclose(archIdx);
    return EXITO;
}

//int regenerarIndiceJugadores(tArbol* indice, const char * nombreArchivoUsuarios)
//{
//    tJugadorArchivo registroArchivo;
//    FILE * pf;
//    unsigned offsetReg;
//    size_t tamRegistro;
//    int ret;
//
//    ret=abrirArchivo(&pf, nombreArchivoUsuarios,"rb");
//    if(ret != EXITO)
//        return ret;
//
//    tamRegistro=sizeof(tJugadorArchivo);
//
//    printf("\n\nRegenerando Indice jugadores...");
//    offsetReg = 0;
//    while(fread(&registroArchivo, sizeof(tJugadorArchivo), 1, pf) == 1)
//    {
//       ret= insertarIndiceJugador(indice, registroArchivo.nickname, offsetReg);
//       if(ret != EXITO)
//            {
//               fclose(pf);
//               return ret;
//            }
//       offsetReg += tamRegistro;
//    }
//    fclose(pf);
//    printf("Indice regenerado exitosamente.\n\n");
//    return EXITO;
//}

int regenerarIndiceJugadores(tArbol* indice, const char* nombreArchivoUsuarios)
{
    tJugadorArchivo registroArchivo;
    FILE* pf;
    unsigned posicionRegistro = 0;
    int ret;

    ret = abrirArchivo(&pf, nombreArchivoUsuarios, "rb");

    if(ret != EXITO)
        return ret;

    printf("\nRegenerando indice de jugadores...\n");

    while(fread(&registroArchivo, sizeof(tJugadorArchivo), 1, pf) == 1)
    {
        ret = insertarIndiceJugador(indice, registroArchivo.nickname, posicionRegistro);

        if(ret != EXITO)
        {
            fclose(pf);
            return ret;
        }

        posicionRegistro++;
    }

    fclose(pf);

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

int insertarIndiceJugador(tArbol* indice, const char* nickname, unsigned posicionRegistro)
{
    tIndiceJugador jug;

    strcpy(jug.nickname, nickname);
    jug.posicionRegistro = posicionRegistro;

    if(!insertarEnArbolBRec(indice, &jug, sizeof(tIndiceJugador), cmpIndiceJugadorPorNickname))
        return ERROR_MEMORIA;

    return EXITO;
}

