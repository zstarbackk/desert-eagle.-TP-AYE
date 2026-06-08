#include "Ranking.h"
int cargarRanking(FILE *archivo, tLista *lista)
{
    tRanking rank;
    tPartida partida;
    int ret;

    rewind(archivo);

    while(fread(&partida, sizeof(tPartida), 1, archivo) == 1)
    {
        rank.total = partida.puntaje;
        rank.idJugador = partida.idJugador;
        rank.nickname[0] = '\0';

        ret = insertarOrdenado(lista,
                               &rank,
                               sizeof(tRanking),
                               cmpIndiceJugadorPorId,
                               sumarPuntos);

        if(ret != EXITO)
            return ret;
    }

    return EXITO;
}


int cmpRankingPorPuntos(const void* a, const void* b)
{
    const tRanking* jugA = (const tRanking*)a;
    const tRanking* jugB = (const tRanking*)b;

    if (jugA->total < jugB->total) return 1;
    if (jugA->total > jugB->total) return -1;

    if (jugA->idJugador > jugB->idJugador) return 1;
    if (jugA->idJugador < jugB->idJugador) return -1;

    return 0;

}

int generarListaTop(tLista* listaPorId, tLista* listaPorPuntos)
{
    tNodoL* aux = *listaPorId;
    int ret;

    while(aux != NULL)
    {
        ret = insertarOrdenado(listaPorPuntos,
                               aux->info,
                               sizeof(tRanking),
                               cmpRankingPorPuntos,
                               NULL);

        if(ret != EXITO)
            return ret;

        aux = aux->sig;
    }

    return EXITO;
}

int listarTopJugadores(tLista* lista, int cant)
{
    tNodoL* aux = *lista;
    tRanking* rank;
    tJugadorArchivo jugArchivo;
    int contador = 0;
    long offset;
    FILE* archJugadores;
    int ret;

    ret = abrirArchivo(&archJugadores, ARCH_JUGADORES, "rb");
    if(ret != EXITO)
        return ret;

    printf("\n--- TOP %d JUGADORES ---\n", cant);

    while(aux != NULL && contador < cant)
    {
        rank = (tRanking*)aux->info;

        offset = (long)(rank->idJugador - 1) * sizeof(tJugadorArchivo);

        if(fseek(archJugadores, offset, SEEK_SET) != 0)
        {
            fclose(archJugadores);
            return ERROR_ARCHIVO;
        }

        if(fread(&jugArchivo, sizeof(tJugadorArchivo), 1, archJugadores) != 1)
        {
            fclose(archJugadores);
            return ERROR_LECTURA;
        }

        printf("%d. Nickname: %-15s | Puntos: %u\n",
               contador + 1,
               jugArchivo.nickname,
               rank->total);

        aux = aux->sig;
        contador++;
    }

    printf("------------------------\n");

    fclose(archJugadores);
    return EXITO;
}


int cmpIndiceJugadorPorId(const void* a, const void* b)
{
    const tRanking* jugA = (const tRanking*)a;
    const tRanking* jugB = (const tRanking*)b;

    if (jugA->idJugador > jugB->idJugador)
        return 1;

    if (jugA->idJugador < jugB->idJugador)
        return -1;
    return 0;
}
void sumarPuntos(void *registro, const void* infoPartida){
    tRanking* regAct = (tRanking*)registro;
    const tRanking* info = (const tRanking*)infoPartida;
    regAct->total += info->total;
}
