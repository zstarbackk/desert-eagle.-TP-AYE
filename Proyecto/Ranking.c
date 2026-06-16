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
        strcpy(rank.nickname,partida.nickname);

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

int listarTopJugadores(const tLista* lista, int cant)
{
    tRanking rank;
    int contador = 0;

    printf("\n--- TOP %d JUGADORES ---\n", cant);

    while(contador < cant && buscarEnListaPorPosicion(lista, contador, &rank, sizeof(tRanking)) == EXITO)
    {
        printf("%d. Nickname: %-15s | Puntos: %u\n",
               contador + 1,
               rank.nickname,
               rank.total);
        contador++;
    }

    printf("------------------------\n");

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

void sumarPuntos(void *registro, const void* infoPartida)
{
    tRanking* regAct = (tRanking*)registro;
    const tRanking* info = (const tRanking*)infoPartida;
    regAct->total += info->total;
}
