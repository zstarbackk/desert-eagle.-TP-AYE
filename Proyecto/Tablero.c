#include "Tablero.h"
#include "Bandido.h"
#include "Utils.h"

static void accionCambiarEvento(void* dato, void* ctx)
{
    tCasillero* cas = (tCasillero*)dato;
    tTipoEvento* evento = (tTipoEvento*)ctx;

    cas->tipoEvento = *evento;
}


void inicializarTablero(tTablero* tablero)
{
    crearListaDC(&tablero->casilleros);
    tablero->inicio = NULL;
    tablero->fin = NULL;
    tablero->cantidadCasilleros = 0;
    crearLista(&tablero->bandidos);
}

int crearCasilleros(tTablero* tablero, unsigned cantidadCasilleros)
{
    unsigned i;
    tCasillero aux;
    int ret;

    for(i = 0; i < cantidadCasilleros; i++)
    {
        aux.tipoEvento = DESPEJADO;
        aux.numeroCasillero = i;
        aux.tieneJugador = 0;
        aux.idBandido = 0;

        if(i == 0)
            aux.tipoEvento = INICIO;
        else if(i == cantidadCasilleros - 1)
            aux.tipoEvento = SALIDA;

        ret = insertarAlFinalDC(&(tablero->casilleros), &aux, sizeof(tCasillero));

        if(ret != EXITO)
            return ERROR_MEMORIA;
    }

    tablero->inicio = obtenerPrimeroDC(&(tablero->casilleros));
    tablero->fin = obtenerUltimoDC(&(tablero->casilleros));
    tablero->cantidadCasilleros = cantidadCasilleros;

    return EXITO;
}

tCursorDC obtenerCasilleroAleatorioLibre(const tTablero* tablero)
{
    tCursorDC actual;
    tCasillero casAux;
    int pos;

    do
    {
        actual = tablero->inicio;
        pos = rand() % tablero->cantidadCasilleros;

        actual = avanzarNDC(actual, pos);

        verActualDC(actual, &casAux, sizeof(tCasillero));

        if(casAux.tipoEvento == DESPEJADO &&
           casAux.idBandido == 0 &&
           casAux.tieneJugador == 0)
        {
            return actual;
        }

    } while(1); // config ya verifica que va a haber casilleros disponibles
}

int colocarEventos(tTablero* tablero, tTipoEvento evento, unsigned maximo)
{
    unsigned i;
    unsigned cantidadReal;
    tCursorDC pos;
    int ret;

    if(maximo == 0)
        return EXITO;

    cantidadReal = (maximo * PORCENTAJE_MINIMO_EVENTOS) / 100; //cantidad minima de eventos a colocar, no necesariamente lo que esta en la config

    if(cantidadReal == 0)
        cantidadReal = 1; //minimo 1

    cantidadReal += rand() % (maximo - cantidadReal + 1); //se elije aleatoriamente entre ese minimo y el maximo

    for(i = 0; i < cantidadReal; i++)
    {
        pos = obtenerCasilleroAleatorioLibre(tablero);

        ret = modificarActualDC(pos, accionCambiarEvento, &evento);

        if(ret != EXITO)
            return ret;
    }

    return EXITO;
}

int colocarBandidos(tTablero* tablero, unsigned maximo)
{
    unsigned i;
    unsigned cantidadReal;
    tCursorDC pos;
    tBandido banAux;
    unsigned idBandido;
    int ret;

    if(maximo == 0)
        return EXITO;

    cantidadReal = (maximo * PORCENTAJE_MINIMO_EVENTOS) / 100;

    if(cantidadReal == 0)
        cantidadReal = 1;

    cantidadReal += rand() % (maximo - cantidadReal + 1);

    for(i = 0; i < cantidadReal; i++)
    {
        pos = obtenerCasilleroAleatorioLibre(tablero);

        inicializarBandido(&banAux, i + 1, pos);

        ret = insertarAlFinal(&tablero->bandidos, &banAux, sizeof(tBandido));

        if(ret != EXITO)
            return ERROR_MEMORIA;

        idBandido = banAux.idBandido;

        ret = modificarActualDC(pos, accionCambiarIdBandido, &idBandido);

        if(ret != EXITO)
            return ret;
    }

    return EXITO;
}

int generarTablero(tTablero* tablero, const tConfig* config)
{
    int ret;

    inicializarTablero(tablero);

    ret = crearCasilleros(tablero, config->cantidad_posiciones);
    if(ret != EXITO)
        return ret;

    ret = colocarEventos(tablero, PREMIO, config->maximo_premios);
    if(ret != EXITO)
        return ret;

    ret = colocarEventos(tablero, VIDA_EXTRA, config->maximo_vidas_extra);
    if(ret != EXITO)
        return ret;

    ret = colocarEventos(tablero, OASIS, config->maximo_oasis);
    if(ret != EXITO)
        return ret;

    ret = colocarEventos(tablero, TORMENTA, config->maximo_tormentas);
    if(ret != EXITO)
        return ret;

    ret = colocarBandidos(tablero, config->maximo_bandidos);
    if(ret != EXITO)
        return ret;

    return EXITO;
}

void vaciarTablero(tTablero* tablero)
{
    vaciarListaDC(&tablero->casilleros);
    vaciarLista(&tablero->bandidos);

    tablero->inicio = NULL;
    tablero->fin = NULL;
    tablero->cantidadCasilleros = 0;
}

char obtenerCharEvento(tTipoEvento evento)
{
    switch(evento)
    {
        case INICIO:     return 'I';
        case SALIDA:     return 'S';
        case PREMIO:     return 'P';
        case VIDA_EXTRA: return 'V';
        case OASIS:      return 'O';
        case TORMENTA:   return 'T';
        default:         return '.';
    }
}

void mostrarTablero(const tTablero* tablero, FILE* salida)
{
    tCursorDC actual;
    tCasillero cas;
    unsigned i;

    actual = tablero->inicio;

    for(i = 0; i < tablero->cantidadCasilleros; i++)
    {
        verActualDC(actual, &cas, sizeof(tCasillero));

        fprintf(salida, "%02u:", cas.numeroCasillero + 1);

        if(cas.tieneJugador && cas.idBandido)
            fprintf(salida, "[%c B J]", obtenerCharEvento(cas.tipoEvento));
        else if(cas.tieneJugador)
        {
            if(cas.tipoEvento == DESPEJADO)
                fprintf(salida, "[J]");
            else
                fprintf(salida, "[%c J]", obtenerCharEvento(cas.tipoEvento));
        }
        else if(cas.idBandido)
        {
            if(cas.tipoEvento == DESPEJADO)
                fprintf(salida, "[B]");
            else
                fprintf(salida, "[%c B]", obtenerCharEvento(cas.tipoEvento));
        }
        else
            fprintf(salida, "[%c]", obtenerCharEvento(cas.tipoEvento));

        fprintf(salida, "\n");

        actual = siguienteDC(actual);
    }
}

int exportarTablero(const tTablero* tablero, char* nombreArchivo)
{
    FILE* archivo;

    if(abrirArchivo(&archivo, nombreArchivo, "wt") != EXITO)
        return ERROR_ARCHIVO;

    mostrarTablero(tablero, archivo);

    fclose(archivo);
    return EXITO;
}

int validarTablero(tTablero* tablero)
{
    unsigned i;
    int casillaJugable = 0;
    tCursorDC actual;
    tCasillero cas;

    actual = siguienteDC(tablero->inicio);

    for(i = 0; i < MAX_DADO && i < tablero->cantidadCasilleros - 1; i++)
    {
        verActualDC(actual, &cas, sizeof(tCasillero));

        if(cas.idBandido == 0)
        {
            casillaJugable = 1;
            break;
        }

        actual = siguienteDC(actual);
    }

    return casillaJugable ? EXITO : TABLERO_NO_JUGABLE;
}

