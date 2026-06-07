#include "Juego.h"
#include "Bandido.h"
#include "Utils.h"


void generarNickname(char* nombre, char* nickname, unsigned tam)
{
    int n = rand() % 10000;
    snprintf(nickname, tam, "%s%d", nombre, n);
}

void mostrarJugadoresEncontrados(const void* dato, unsigned inc)
{
    tJugadorArchivo registro = *(tJugadorArchivo*)dato;
    printf("%u. %s\n",inc+1, registro.nickname);
}

int seleccionarJugador(int cantidad)
{
    int opcion;
    do {
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        if(opcion < 1 || opcion > (cantidad + 1))
            printf("Opcion invalida, reingrese: ");
    } while(opcion < 1 || opcion > (cantidad + 1));
    return opcion;
}

int ingresarJugador(tJugador* jugador, tArbol *indiceJugador)
{
    char nombre[TAM_NICKNAME];
    char nickname[TAM_NICKNAME];
    FILE* archivo;
    tLista resultados;
    tJugadorArchivo jugadorEncontrado;
    tIndiceJugador indiceEncontrado;
    int cantidad;
    int opcion;
    unsigned posRegistro;

    printf("Bienvenido a 'Caravana del desierto'\n");
    printf("Ingrese su nombre: ");
    fgets(nombre, TAM_NICKNAME, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    if(abrirArchivo(&archivo, ARCH_JUGADORES, "a+b") != EXITO)
        return ERROR_APERTURA;
    crearLista(&resultados);


    cantidad=buscarJugadoresPorNombre(archivo, nombre, &resultados);

    if(cantidad == 0)
    {
        printf("Generando apodo...\n");
        do
        {
            generarNickname(nombre, nickname, TAM_NICKNAME);
        } while(buscarIndiceJugador(indiceJugador, nickname, &indiceEncontrado) != JUGADOR_INEXISTENTE);

        printf("Su apodo sera: %s\nNo lo olvides!\n", nickname);
        fseek(archivo, 0,SEEK_END);
        posRegistro = ftell(archivo);
        darDeAltaJugador(archivo, nombre, nickname, jugador);
        insertarIndiceJugador(indiceJugador,nickname,posRegistro);
    }
    else if(cantidad != ERROR)
    {
        printf("\nJugadores encontrados con ese nombre:\n");
        mostrarLista(&resultados,mostrarJugadoresEncontrados);
        printf("%u. Ninguno es el mio\n", cantidad + 1);
        opcion = seleccionarJugador(cantidad);

        if(opcion == (cantidad + 1))
        {
            printf("Generando apodo...\n");
            do
            {
                generarNickname(nombre, nickname, TAM_NICKNAME);
            } while(buscarIndiceJugador(indiceJugador, nickname, &indiceEncontrado) != JUGADOR_INEXISTENTE);
            printf("Su apodo sera: %s\nNo lo olvides!\n", nickname);
            fseek(archivo, 0,SEEK_END);
            posRegistro = ftell(archivo);
            darDeAltaJugador(archivo, nombre, nickname, jugador);
            insertarIndiceJugador(indiceJugador,nickname,posRegistro);
        }
        else
        {
            if(buscarEnListaPorPosicion(&resultados, opcion - 1, &jugadorEncontrado, sizeof(tJugadorArchivo)) == EXITO)
            {
                jugador->idJugador = jugadorEncontrado.idJugador;
                strcpy(jugador->nickname, jugadorEncontrado.nickname);
                printf("Bienvenido de vuelta, %s!\n", jugador->nickname);

            }
            else
            {
                printf("Error al recuperar el jugador seleccionado.\n");
                fclose(archivo);
                vaciarLista(&resultados);
                return ERROR;
            }
        }
    }
    else
    {
        printf("Error en recuperacion de apodos. Contacte al equipo de desarrollo\n");
        fclose(archivo);
        vaciarLista(&resultados);
        return ERROR;
    }

    fclose(archivo);
    vaciarLista(&resultados);
    return EXITO;
}
void mostrarRanking(int cant){
    FILE * pf = fopen(ARCH_PARTIDAS, "rb");
    tLista listaId, listaRank;
    if(pf==NULL){
        fclose(pf);
        return ERROR_APERTURA;
    }
    crearLista(&listaId);
    crearLista(&listaRank);
    cargarRanking(pf,&listaId);
    generarListaTop(&listaId, &listaRank);
    listarTopJugadores(&listaRank, cant);
    vaciarLista(&listaRank);
    vaciarLista(&listaId);
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
            case 2:
                mostrarRanking(10);
                break;
            /*case 3:
                mostrarAyuda();
                break;  */
            case 4:
                printf("Hasta luego, %s!\n", jugador->nickname);
                break;
            default:
                printf("Opcion invalida.\n");
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


    printf("Tablero valido.\n");

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

tDireccion pedirDireccion(const tJugador* jugador, unsigned dado)
{
    char dir;

    if(puedeRetroceder(jugador,dado)!=EXITO)
    {
        printf("No tenes espacio para retroceder %u casilleros. La caravana debe avanzar.\n", dado);
        return ADELANTE;
    }

    do
    {
        printf("Puede elegir entre avanzar o retroceder.\n");
        printf("Presione 'F' para avanzar o 'B' para retroceder.\n");

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
        printf("Ha perdido un turno por la tormenta, es el turno de los bandidos, tenga cuidado!!.\n\n");
    }
    else
    {

        do
        {
           printf("Presione ENTER para tirar el dado..\n");
           fflush(stdin);
           scanf("%c", &tecla);
           if(tecla != '\n')
            printf("Tecla invalida.\n");
        }while(tecla != '\n');

        dado=tirarDado();

        //system("cls");

        printf("El dado giro en el aire y cayo, el numero es: %u.\n", dado);

        direccion = pedirDireccion(jugador, dado);

        if(direccion == ATRAS)
           printf("Retrocede %u casilleros, suerte!!.\n\n", dado);
        else
           printf("Avanza %u casilleros, suerte!!.\n\n", dado);

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


void aplicarEvento(tJugador* jugador, tCasillero* cas)
{
    switch(cas->tipoEvento)
    {
        case PREMIO:
            printf("Felicidades, se ha topado con un premio, su puntaje se ha incrementado con exito!!.\n\n");
            jugador->puntaje++;
            cas->tipoEvento = DESPEJADO;
            break;
        case VIDA_EXTRA:
            printf("Parece que es su dia de suerte, ha conseguido una vida extra, aprovechela! \n\n");
            jugador->vidas++;
            cas->tipoEvento = DESPEJADO;
            break;
        case OASIS:
            printf("Llegaste a un oasis. Tendras proteccion contra el proximo peligro.\n\n");
            jugador->protegidoPorOasis = 1;
            cas->tipoEvento = DESPEJADO;
            break;
        case TORMENTA:
            printf("A juzgar por el viento se avecina una tormenta, menos mal que traje paraguas.\n\n");
            if(!jugador->protegidoPorOasis)
                {
                   printf("Te costara un turno (-_-)\n\n");
                   jugador->pierdeTurno = 1;
                }
            else
                {
                   printf("Que util el oasis no? Esta vez te salvaste, a seguir jugando!!.\n\n");
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
        printf("Buena suerte, tenias blindaje contra bandidos, sigue con cuidado que ya no lo tienes!!.\n\n");
        jugador->protegidoPorOasis = 0;
    }
    else
    {
        printf("Fuiste interceptado por el bandido %u, volviste al inicio [);].\n\n", bandido->idBandido);

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

        if(mov.actor == ACTOR_JUGADOR) //en preparar turno ya se contempla si pierde el turno porque no genera el movimiento
        {
            casOrigen->tieneJugador  = 0;
            casDestino->tieneJugador = 1;
            jugador->posicionActual  = mov.destino;
            aplicarEvento(jugador, casDestino);
        }
        else
        {
            bandido = buscarBandidoPorId(&tablero->bandidos, mov.idActor);

            if(bandido && bandido->activo)
            {
                ajustarDestinoBandido(&mov);

                casOrigen = (tCasillero*)bandido->posicionActual->info;
                casDestino = (tCasillero*)mov.destino->info;

                if(mov.destino != bandido->posicionActual)
                    {
                        if(casOrigen->idBandido == bandido->idBandido)
                        casOrigen->idBandido = 0;

                        casDestino->idBandido = bandido->idBandido;
                        bandido->posicionActual = mov.destino;
                    }
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

    //system("cls");

    printf("\n");
    printf("Cuenta con %d vidas, a jugar!\n", jugador->vidas);

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
        printf("Felicitaciones %s, llegaste a la Ciudad Refugio!.\n", jugador->nickname);
    else if (resultado == PARTIDA_PERDIDA)
        printf("Game over %s, perdiste todas tus vidas!.\n", jugador->nickname);
    else
        printf("Ocurrio un error durante la partida.\n");

    mostrarHistorialJugador(jugador);
    if(guardarPartida(ARCH_PARTIDAS,jugador, resultado)!=EXITO)
        printf("No se pudo guardar la partida.\n");
}
