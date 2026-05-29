#include "Juego.h"
#include "Bandido.h"
#include "Utils.h"

int ingresarJugador(tJugador *jugador)
{
    char nickname[TAM_NICKNAME];
    FILE *archivo;

    printf("Ingrese su nickname: ");
    fgets(nickname, TAM_NICKNAME , stdin);
    nickname[strcspn(nickname, "\n")] = '\0';  // elimina el \n que deja fgets


    if (abrirArchivo(&archivo,ARCH_JUGADORES, "a+b") != EXITO)
        return ERROR_APERTURA;

    if (buscarJugador(archivo, nickname, jugador) == JUGADOR_INEXISTENTE)
    {
        printf("Jugador nuevo, dando de alta...\n");
        darDeAltaJugador(archivo, nickname, jugador);
    }
    else
    {
        printf("Bienvenido de vuelta, %s!\n", jugador->nickname);
    }
    fclose(archivo);

    return EXITO;
}


void mostrarMenu(tJugador *jugador, tTablero *tablero, tConfig *config)
{
    tResultadoPartida resultado;
    int opcion;

    do {
        printf("\n=== CARAVANA DEL DESIERTO ===\n");
        printf("1. Jugar nueva partida\n");
        printf("2. Ver ranking\n");
        printf("3. Ayuda\n");
        printf("4. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                resultado = jugarPartida(jugador, tablero, config);
                finalizarPartida(jugador, resultado);
                break;
          /*  case 2:
                mostrarRanking();
                break;
            case 3:
                mostrarAyuda();
                break;  */
            case 4:
                printf("Hasta luego, %s!\n", jugador->nickname);
                break;
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 4);

}

tResultadoPartida inicializarPartida(tJugador* jugador,tTablero* tablero, tConfig *config)
{
    int ret;

    ret=cargarConfiguracion(ARCH_CONFIGURACION,config);
    if(ret != EXITO)
        return PARTIDA_ERROR;

    do
    {
        printf("Generando tablero...\n");
        ret=generarTablero(tablero,config);

        if(ret != EXITO)
           return PARTIDA_ERROR;

        printf("Validando tablero...\n");

    }while(validarTablero(tablero)!=EXITO);


    printf("Tablero valido\n");

    ret = exportarTablero(tablero, ARCH_CARAVANA);
    if(ret != EXITO)
        return PARTIDA_ERROR;

    inicializarEstadoJugador(jugador,config->vidas_inicio,tablero->inicio);


    return PARTIDA_EN_CURSO;
}

int puedeRetroceder(const tJugador* jugador, unsigned pasos)
{
    tPosicion act = jugador->posicionActual;

    while(pasos--)
    {
        if(((tCasillero*)act->info)->tipoEvento == INICIO)
            return NO_RETROCEDE;

        act = act->ant;
    }

    return EXITO;
}

int validarMovimiento(const tJugador* jugador, unsigned pasos, tDireccion direccion)
{
    if(direccion == ATRAS)
        return puedeRetroceder(jugador, pasos);

    return EXITO;
}

tDireccion pedirDireccion(const tJugador* jugador, unsigned dado)
{
    char dir;

    if(validarMovimiento(jugador, dado, ATRAS) != EXITO)
    {
        printf("Solo puede avanzar, no hay casilleros disponibles para retroceder\n");
        return ADELANTE;
    }

    do
    {
        printf("Puede elegir entre avanzar o retroceder\n");
        printf("Presione 'F' para avanzar o 'B' para retroceder\n");

        scanf(" %c", &dir);

        dir = toupper(dir);

        if(dir != 'F' && dir != 'B')
            printf("Direccion invalida\n");

    }while(dir != 'F' && dir != 'B');

    return dir == 'B' ? ATRAS : ADELANTE;
}

int prepararTurno(tJugador* jugador,tTablero* tablero, tCola *colaMovimientos)
{
    int ret;
    unsigned dado;
    char tecla;
    tMovimiento mov;
    tBandido *bandido;
    tLista *pl=&tablero->bandidos;
    tDireccion direccion;

    if(jugador->pierdeTurno)
    {
        jugador->pierdeTurno=0;
        printf("Como ha perdido un turno, es el turno de los bandidos, tenga cuidado!!\n\n");
    }
    else
    {

        do
        {
           printf("Presione ENTER para tirar el dado\n");
           fflush(stdin);
           scanf("%c", &tecla);
           if(tecla != '\n')
            printf("Tecla invalida\n");
        }while(tecla != '\n');

        dado=tirarDado();

        system("cls");

        printf("El dado giro en el aire y cayo, el numero es: %u\n", dado);

        direccion = pedirDireccion(jugador, dado);

        if(direccion == ATRAS)
           printf("Retrocede %u casilleros, suerte!!\n\n", dado);
        else
           printf("Avanza %u casilleros, suerte!!\n\n", dado);

        ret=generarMovimientoJugador(jugador,tablero,dado,&mov,direccion);
        if(ret!=EXITO)
            return ret;
        ret=encolar(colaMovimientos,&mov,sizeof(tMovimiento));
        if(ret!=EXITO)
            return ret;

    }


    while(*pl)
    {
        bandido=(tBandido*)(*pl)->info;
        if(bandido->activo)
        {
            mov=generarMovimientoBandido(bandido,jugador,tablero);
            ret=encolar(colaMovimientos,&mov,sizeof(tMovimiento));
            if(ret!=EXITO)
                return ret;
        }
        pl=&(*pl)->sig;
    }

    return EXITO;

}


void aplicarEvento(tJugador* jugador, tCasillero* cas, tTablero* tablero)
{
    switch(cas->tipoEvento)
    {
        case PREMIO:
            printf("Enhorabuena, se ha topado con un premio, su puntaje se ha incrementado con exito!!\n\n");
            jugador->puntaje++;
            cas->tipoEvento = DESPEJADO;
            break;
        case VIDA_EXTRA:
            printf("Parece que es su dia de suerte, ha conseguido una vida extra, aprovechelaa \n\n");
            jugador->vidas++;
            cas->tipoEvento = DESPEJADO;
            break;
        case OASIS:
            printf("Al parecer un desierto no es solo arena, felicidades ha encontrado un oasis, mala suerte para los bandidos\n\n");
            jugador->protegidoPorOasis = 1;
            break;
        case TORMENTA:
            printf("A juzgar por el viento se avecina una tormenta, menos mal que traje paraguas\n\n");
            if(!jugador->protegidoPorOasis)
                {
                   printf("Te costara un turno (-_-)\n\n");
                   jugador->pierdeTurno = 1;
                }
            else
                {
                   printf("Que util el oasis no? Esta vez te salvaste, a seguir jugando!!\n\n");
                   jugador->protegidoPorOasis = 0;
                }

            break;
        default:
            break;
    }
}

void interceptarJugador(tJugador* jugador, tBandido* bandido, tCasillero* cas, tTablero* tablero)
{
    tCasillero* casInicio = (tCasillero*)tablero->inicio->info;

    if(jugador->protegidoPorOasis)
    {
        printf("Buena suerte, tenias blindaje contra bandidos, sigue con cuidado que ya no lo tienes!!\n\n");
        jugador->protegidoPorOasis = 0;
    }
    else
    {
        printf("Fuiste interceptado por el bandido %u, volviste al inicio [);]\n\n", bandido->idBandido);

        // mover jugador al inicio
        cas->tieneJugador = 0;
        casInicio->tieneJugador = 1;
        jugador->posicionActual = tablero->inicio;
        // reducir vida
        jugador->vidas--;
    }
    // desactivar bandido
    cas->idBandido = 0;
    desactivarBandido(bandido);
}

int procesarMovimientos(tCola* cola, tJugador* jugador, tTablero* tablero)
{
    tMovimiento mov;
    tCasillero* casOrigen;
    tCasillero* casDestino;
    tBandido* bandido;
    int ret;

    while(!colaVacia(cola))
    {
        ret = desencolar(cola, &mov, sizeof(tMovimiento));
        if(ret != EXITO)
            return ret;

        casOrigen  = (tCasillero*)mov.origen->info;
        casDestino = (tCasillero*)mov.destino->info;

        if(mov.Actor == ACTOR_JUGADOR && !jugador->pierdeTurno)
        {
            casOrigen->tieneJugador  = 0;
            casDestino->tieneJugador = 1;
            jugador->posicionActual  = mov.destino;
            aplicarEvento(jugador, casDestino, tablero);
        }
        else
        {
            bandido = buscarBandidoPorId(&tablero->bandidos, mov.idActor);
            if(bandido && bandido->activo)
            {
                casOrigen->idBandido    = 0;
                casDestino->idBandido   = bandido->idBandido;
                bandido->posicionActual = mov.destino;
            }
        }
    }

    casDestino = (tCasillero*)jugador->posicionActual->info;
    if(casDestino->idBandido)
    {
        bandido = buscarBandidoPorId(&tablero->bandidos, casDestino->idBandido);
        if(bandido && bandido->activo)
            interceptarJugador(jugador, bandido, casDestino, tablero);
    }

    return EXITO;
}

tResultadoPartida jugarPartida(tJugador* jugador, tTablero* tablero, tConfig *config)
{
    tCola cola;
    tCasillero* casActual;
    tResultadoPartida resultado;
    int ret;

    resultado=inicializarPartida(jugador,tablero,config);

    if(resultado != PARTIDA_EN_CURSO)
        return resultado;

    crearCola(&cola);

    system("cls");

    while(resultado == PARTIDA_EN_CURSO)
    {
        printf("=== TABLERO ACTUAL ===\n");
        mostrarTablero(tablero, stdout);
        printf("\n");

        ret = prepararTurno(jugador, tablero, &cola);
        if(ret != EXITO)
        {
            vaciarCola(&cola);
            return PARTIDA_ERROR;
        }
        ret = procesarMovimientos(&cola, jugador, tablero);
        if(ret != EXITO)
        {
            vaciarCola(&cola);
            return PARTIDA_ERROR;
        }

        casActual = (tCasillero*)jugador->posicionActual->info;
        if(casActual->tipoEvento == SALIDA)
            resultado = PARTIDA_GANADA;
        else if(jugador->vidas <= 0)
            resultado = PARTIDA_PERDIDA;

    }

    vaciarCola(&cola);
    return resultado;
}

void finalizarPartida(tJugador* jugador, tResultadoPartida resultado)
{
    if(resultado == PARTIDA_GANADA)
        printf("Felicitaciones %s, llegaste a la Ciudad Refugio!\n", jugador->nickname);
    else if (resultado == PARTIDA_PERDIDA)
        printf("Game over %s, perdiste todas tus vidas!\n", jugador->nickname);
    else
        printf("Ocurrio un error durante la partida\n");

    //mostrarHistorial(jugador);
    //guardarPartida(jugador, resultado);
}
