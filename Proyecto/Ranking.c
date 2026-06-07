#include "Ranking.h"
int cargarRanking(FILE *archivo, tLista *lista){
    tRanking rank;
    tPartida partida;

    rewind(archivo);
    while(fread(&partida,sizeof(partida),1,archivo)){
        rank.total = partida.puntaje;
        rank.idJugador = partida.idJugador;
        insertarOrdenado(lista, &rank, sizeof(tRanking),cmpIndiceJugadorPorId, sumarPuntos);
    }
    fclose(archivo);
}

int cmpRankingPorPuntos(const void* a, const void* b)
{
    const tRanking* jugA = (const tRanking*)a;
    const tRanking* jugB = (const tRanking*)b;

    if (jugA->total < jugB->total) return 1;
    if (jugA->total > jugB->total) return -1;

    if (jugA->idJugador > jugB->idJugador) return 1;
    if (jugA->idJugador < jugB->idJugador) return -1;

}

void generarListaTop(tLista* listaPorId, tLista* listaPorPuntos)
{
    tNodoL* aux = *listaPorId;

    while(aux != NULL)
    {
        insertarOrdenado(listaPorPuntos, aux->info, sizeof(tRanking), cmpRankingPorPuntos, NULL);

        aux = aux->sig;
    }
}
int listarTopJugadores(tLista * lista, int cant)
{
    tNodoL* aux = *lista;
    tRanking* rank;
    tJugadorArchivo jugArchivo;
    int contador = 0;
    long offset;


    FILE *archJugadores = fopen(ARCH_JUGADORES, "rb");
    if(archJugadores == NULL)
    {
        printf("Error: No se pudo abrir el archivo de jugadores.\n");
        return 0;
    }

    printf("\n--- TOP %d JUGADORES ---\n", cant);

    while(aux != NULL && contador < cant)
    {
        rank = (tRanking*)aux->info;


        offset = (rank->idJugador - 1) * sizeof(tJugadorArchivo);
        fseek(archJugadores, offset, SEEK_SET);

        if(fread(&jugArchivo, sizeof(tJugador), 1, archJugadores) == 1){
            printf("%d. Nickname: %-15s | Puntos: %u\n",
                       contador + 1,
                       jugArchivo.nickname,
                       rank->total);
        }

        aux = aux->sig;
        contador++;
    }

    printf("------------------------\n");

    fclose(archJugadores);

    return contador;
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
