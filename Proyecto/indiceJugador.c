#include "indiceJugador.h"
int cmpIndiceJugadorPorNickname(const void* a, const void* b){
    tIndiceJugador * jugadorX = (tIndiceJugador*)a;
    tIndiceJugador * jugadorY = (tIndiceJugador*)b;
    return strcmp(jugadorX->nickname, jugadorY->nickname);
}
int cargarIndiceJugadores(tArbol* indice, const char* nombreArchivoIndice, const char * nombreArchivoUsuarios){
    FILE * archIdx = fopen(nombreArchivoIndice, "rb");
    if(archIdx!=NULL){
        tIndiceJugador registroJugador;
        while(fread(&registroJugador, sizeof(tIndiceJugador),1,archIdx)==1){
            insertarIndiceJugador(indice, registroJugador.nickname,registroJugador.posicionRegistro);
        }
        fclose(archIdx);
        return EXITO;
    }
    else{
        printf("\nIndice no encontrado. Se regenera...\n\n");
        return regenerarIndiceJugadores(indice, nombreArchivoUsuarios);
    }
}
int regenerarIndiceJugadores(tArbol* indice, const char * nombreArchivoUsuarios){
    tJugadorArchivo registroArchivo;
    FILE * pf;
    unsigned offsetReg;
    pf = fopen(nombreArchivoUsuarios, "rb");
    if(pf == NULL)
        return EXITO;
    printf("\n\nRegenerando Indice jugadores...");
    offsetReg = ftell(pf);
    while(fread(&registroArchivo, sizeof(tJugadorArchivo),1,pf)==1){
        insertarIndiceJugador(indice, registroArchivo.nickname,offsetReg);
        offsetReg =ftell(pf);
    }
    fclose(pf);
    printf("Indice regenerado exitosamente.\n\n");
    return EXITO;
}

int guardarIndiceJugadores(const tArbol* indice, const char* nombreArchivoIndice) {
    FILE *archTemp = fopen("indice_temp.idx", "wb");
    if (!archTemp) return ERROR_APERTURA;

    cargarArchivoDesdeArbol(indice, archTemp);
    fclose(archTemp);

    remove(nombreArchivoIndice);
    rename("indice_temp.idx", nombreArchivoIndice);

    return EXITO;
}
int buscarIndiceJugador(tArbol* indice, const char* nickname, tIndiceJugador* indiceEncontrado){
    tIndiceJugador temp;
    strcpy(temp.nickname, nickname);
    return verNodo(buscarNodo(indice,&temp,cmpIndiceJugadorPorNickname),indiceEncontrado,sizeof(tIndiceJugador));
}
int insertarIndiceJugador(tArbol* indice, const char* nickname, unsigned posicionRegistro){
    tIndiceJugador jug;
    strcpy(jug.nickname, nickname);
    jug.posicionRegistro = posicionRegistro;
    insertarEnArbolBRec(indice, &jug, sizeof(tIndiceJugador),cmpIndiceJugadorPorNickname);
    return 1;
}
