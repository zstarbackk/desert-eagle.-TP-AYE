#include "Tablero.h"
#include "Bandido.h"


void inicializarTablero(tTablero* tablero)
{
    crearListaDC(&tablero->casilleros);
    tablero->inicio=NULL;
    tablero->fin=NULL;
    tablero->cantidadCasilleros=0;
    crearLista(&tablero->bandidos);
}
int crearCasilleros(tTablero* tablero, unsigned cantidadCasilleros)
{
    int i;
    tCasillero aux;

    for(i=0; i<cantidadCasilleros; i++)
    {
        aux.tipoEvento=DESPEJADO;
        aux.numeroCasillero=i;
        aux.tieneJugador=0;
        aux.idBandido=0;
        if(i==0)
        {
            aux.tipoEvento=INICIO;
        }else if(i==cantidadCasilleros-1)
            aux.tipoEvento=SALIDA;

        if(insertarAlFinalDC(&(tablero->casilleros),&aux,sizeof(tCasillero))!=EXITO)
            return ERROR_MEMORIA;

        //com la lista queda apuntando al ultimo nodo
        if(i==0)
        {
            tablero->inicio=tablero->casilleros;
        }else if(i==cantidadCasilleros-1)
            tablero->fin=tablero->casilleros;
    }
    tablero->cantidadCasilleros=cantidadCasilleros;
    return EXITO;
}
tPosicion obtenerCasilleroAleatorioLibre(const tTablero* tablero)
{
    tPosicion actual;
    tCasillero* casAux;
    int pos;
    do
    {
         actual=tablero->inicio;
         pos=rand() % tablero->cantidadCasilleros;
         while(pos--)
            actual=actual->sig;
        casAux=(tCasillero*)actual->info;
        if(casAux->tipoEvento==DESPEJADO && !casAux->idBandido && !casAux->tieneJugador)
            return actual;
    }while(1);

}
int colocarEventos(tTablero* tablero, tTipoEvento evento, unsigned maximo)
{
    int i,cantidadReal;
    tPosicion pos;
    tCasillero * cas;
    if(maximo==0)
        return EXITO;
    cantidadReal=(maximo * PORCENTAJE_MINIMO_EVENTOS)/100; //calculo un porcentaje del maximo, a mas porcentaje mas complicado podria ser

    if(cantidadReal==0)
        cantidadReal=1;
    cantidadReal+=rand()%(maximo-cantidadReal+1); //elijo aleatoriamente entre ese minimo y el maximo


    for(i=0;i<cantidadReal;i++)
    {
        pos=obtenerCasilleroAleatorioLibre(tablero);
        cas=(tCasillero*)pos->info;
        cas->tipoEvento=evento;
    }
    return EXITO;
}
int colocarBandidos(tTablero* tablero, unsigned maximo)
{
    int i, cantidadReal;
    tPosicion pos;
    tCasillero* cas;
    tBandido banAux;

    if(maximo == 0)
        return EXITO;

    cantidadReal = (maximo * PORCENTAJE_MINIMO_EVENTOS) / 100;

    if(cantidadReal == 0)
        cantidadReal = 1;

    cantidadReal += rand() % (maximo - cantidadReal + 1);

    for(i = 0; i < cantidadReal; i++)
    {
        pos = obtenerCasilleroAleatorioLibre(tablero);
        cas = (tCasillero*)pos->info;

        inicializarBandido(&banAux, i+1,pos);
        if(insertarAlFinal(&tablero->bandidos, &banAux, sizeof(tBandido))!=EXITO)
            return ERROR_MEMORIA;
        cas->idBandido=banAux.idBandido;
    }

    return EXITO;
}

int generarTablero(tTablero* tablero, const tConfig* config)
{
    int ret;
    inicializarTablero(tablero);

    ret=crearCasilleros(tablero,config->cantidad_posiciones);
    if(ret!=EXITO)
        return ret;

    ret=colocarEventos(tablero,PREMIO,config->maximo_premios);
    if(ret!=EXITO)
        return ret;

    ret=colocarEventos(tablero,VIDA_EXTRA,config->maximo_vidas_extra);
    if(ret!=EXITO)
        return ret;

    ret=colocarEventos(tablero,OASIS,config->maximo_oasis);
    if(ret!=EXITO)
        return ret;

    ret=colocarEventos(tablero,TORMENTA,config->maximo_tormentas);
    if(ret!=EXITO)
        return ret;
    ret=colocarBandidos(tablero,config->maximo_bandidos);
    if(ret!=EXITO)
        return ret;

    return EXITO;

}
void vaciarTablero(tTablero* tablero)
{
    vaciarListaDC(&tablero->casilleros);
    vaciarLista(&tablero->bandidos);
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
    tPosicion actual;
    tCasillero* cas;
    unsigned i;
    actual = tablero->inicio;
    for(i = 0; i < tablero->cantidadCasilleros; i++)
    {
        cas = (tCasillero*)actual->info;
        fprintf(salida, "%02u:", cas->numeroCasillero + 1);
        if(cas->tieneJugador && cas->idBandido)
            fprintf(salida, "[%c B J]", obtenerCharEvento(cas->tipoEvento));
        else if(cas->tieneJugador)
        {
            if(cas->tipoEvento == DESPEJADO)
                fprintf(salida, "[J]");
            else
                fprintf(salida, "[%c J]", obtenerCharEvento(cas->tipoEvento));
        }
        else if(cas->idBandido)
        {
            if(cas->tipoEvento == DESPEJADO)
                fprintf(salida, "[B]");
            else
                fprintf(salida, "[%c B]", obtenerCharEvento(cas->tipoEvento));
        }
        else
            fprintf(salida, "[%c]", obtenerCharEvento(cas->tipoEvento));

        fprintf(salida, "\n");
        actual = actual->sig;
    }
}

int exportarTablero(const tTablero* tablero, char* nombreArchivo)
{
    FILE* archivo;
    if(abrirArchivo(&archivo,nombreArchivo, "wt")!=EXITO)
        return ERROR_ARCHIVO;
    mostrarTablero(tablero, archivo);
    fclose(archivo);
    return EXITO;
}

void probarGenerarTablero(void)
{
    tConfig config;
    tTablero tablero;

    if(cargarConfiguracion("Archivos/config.txt", &config) != EXITO)
    {
        printf("Error cargando configuracion\n");
        return;
    }

    if(generarTablero(&tablero, &config) != EXITO)
    {
        printf("Error generando tablero\n");
        return;
    }

    mostrarTablero(&tablero, stdout);

    vaciarTablero(&tablero);
}
int validarTablero(tTablero* tablero)
{
    int i;
    int casillaJugable = 0;
    tPosicion actual = tablero->inicio->sig;
    tCasillero* cas;

    for(i = 0; i < MAX_DADO && i <tablero->cantidadCasilleros - 1; i++)
    {
        cas = (tCasillero*)actual->info;

        if(cas->idBandido == 0)
        {
            casillaJugable = 1;
            break;
        }

        actual = actual->sig;
    }

    return casillaJugable ? EXITO : TABLERO_NO_JUGABLE;
}





