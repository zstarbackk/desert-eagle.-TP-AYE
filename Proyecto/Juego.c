#include "Juego.h"
#include "Utils.h"
#include "../Bibliotecas/listaDobleCircular.h"
#include "../Bibliotecas/TdaListaDinamica.h"
typedef struct
{
    const tJugador* jugador;
    const tTablero* tablero;
    tCola* colaMovimientos;
} tCtxEncolarBandidos;

static int accionEncolarMovimientoBandido(void* dato, unsigned tamDato, void* ctx)
{
    tBandido* bandido = (tBandido*)dato;
    tCtxEncolarBandidos* contexto = (tCtxEncolarBandidos*)ctx;
    tMovimiento mov;

    if(!bandido->activo)
        return EXITO;

    mov = generarMovimientoBandido(bandido, contexto->jugador, contexto->tablero);

    return encolar(contexto->colaMovimientos, &mov, sizeof(tMovimiento));
}

static void accionCambiarEvento(void* dato, void* ctx)
{
    tCasillero* cas = (tCasillero*)dato;
    tTipoEvento* evento = (tTipoEvento*)ctx;

    cas->tipoEvento = *evento;
}

void generarNickname(char* nombre, char* nickname, unsigned tam)
{
    int n = rand() % 10000;
    snprintf(nickname, tam, "%s%d", nombre, n);
}

void mostrarJugadoresEncontrados(const void* dato, unsigned inc)
{
    printf("%u. %s\n", inc + 1, (char*)dato);
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

void altaNuevoJugador(FILE* archivo, char* nombre, tJugador* jugador, tArbol* indice)
{
    char nickname[TAM_NICKNAME];
    tIndiceJugador indiceEncontrado;
    unsigned posRegistro;

    printf("Generando apodo...\n");
    do
    {
        generarNickname(nombre, nickname, TAM_NICKNAME);
    } while(buscarIndiceJugador(indice, nickname, &indiceEncontrado) != JUGADOR_INEXISTENTE);

    printf("Su apodo sera: %s\nNo lo olvides!\n", nickname);
    fseek(archivo, 0, SEEK_END);
    posRegistro = ftell(archivo)/sizeof(tJugadorArchivo);
    darDeAltaJugador(archivo, nombre, nickname, jugador);
    if(insertarIndiceJugador(indice, nickname, posRegistro)==EXITO)
        printf("Indice actualizado correctamente\n");
    else
        printf("Error de actualizacion, contacte al equipo de desarrollo\n");
}

int ingresarJugador(tJugador* jugador, tArbol *indiceJugador)
{
    char nombre[TAM_NICKNAME];
    char nicknameElegido[TAM_NICKNAME];
    FILE* archivo;
    tLista resultados;
    tJugadorArchivo jugadorEncontrado;
    tIndiceJugador indiceEncontrado;
    int cantidad;
    int opcion;

    printf("Bienvenido a 'Caravana del desierto'\n");
    printf("Ingrese su nombre: ");
    fgets(nombre, TAM_NICKNAME, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    if(abrirArchivo(&archivo, ARCH_JUGADORES, "a+b") != EXITO)
        return ERROR_APERTURA;

    crearLista(&resultados);
    cantidad = buscarJugadoresPorNombre(archivo, nombre, &resultados);

    if(cantidad == 0)
    {
        altaNuevoJugador(archivo, nombre, jugador, indiceJugador);
    }
    else if(cantidad != ERROR)
    {
        printf("\nJugadores encontrados con ese nombre:\n");
        mostrarLista(&resultados, mostrarJugadoresEncontrados);
        printf("%u. Ninguno es el mio\n", cantidad + 1);
        opcion = seleccionarJugador(cantidad);

        if(opcion == (cantidad + 1))
        {
            altaNuevoJugador(archivo, nombre, jugador, indiceJugador);
        }
        else
        {
            if(buscarEnListaPorPosicion(&resultados, opcion - 1, nicknameElegido, TAM_NICKNAME)!=EXITO)
            {
                printf("Error al recuperar el nickname seleccionado.\n");
                fclose(archivo);
                vaciarLista(&resultados);
                return ERROR;
            }


            if(buscarIndiceJugador(indiceJugador, nicknameElegido, &indiceEncontrado) == EXITO)
            {
                fseek(archivo, indiceEncontrado.posicionRegistro * sizeof(tJugadorArchivo), SEEK_SET);
                fread(&jugadorEncontrado, sizeof(tJugadorArchivo), 1, archivo);
                jugador->idJugador = jugadorEncontrado.idJugador;
                strcpy(jugador->nickname, jugadorEncontrado.nickname);
                printf("Bienvenido de vuelta, %s!\n", jugador->nickname);
            }
            else
            {
                printf("Error al recuperar el jugador. Contacte al equipo de desarrollo\n");
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

int mostrarRanking(int cant)
{
    FILE *pf;
    tLista listaRank;
    int ret;

    ret = abrirArchivo(&pf, ARCH_PARTIDAS, "rb");
    if(ret != EXITO)
        return ret;

    crearLista(&listaRank);

    ret = cargarRanking(pf, &listaRank);
    fclose(pf);

    if(ret != EXITO)
    {
        vaciarLista(&listaRank);
        return ret;
    }

    seleccionSortLista(&listaRank,cmpRankingPorPuntos);

    ret = listarTopJugadores(&listaRank, cant);
    if(ret != EXITO)
    {
        vaciarLista(&listaRank);
        return ret;
    }

    vaciarLista(&listaRank);

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
        getchar();

        switch(opcion)
        {
            case 1:
                resultado = jugarPartida(jugador, tablero, config);
                finalizarPartida(jugador, resultado);
                vaciarTablero(tablero);
                break;
            case 2:
                if(mostrarRanking(TOTAL_RANKING) != EXITO)
                    printf("No fue posible mostrar el rankig, contacte al equipo de desarrollo\n");
                break;
            case 3:
                mostrarAyuda(ARCH_AYUDA);
                break;
            case 4:
                printf("Hasta luego, %s!\n", jugador->nickname);
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 4);

}

tResultadoPartida inicializarPartida(tJugador* jugador, tTablero* tablero, tConfig* config)
{
    int ret;

    ret = cargarConfiguracion(ARCH_CONFIGURACION, config);
    if(ret != EXITO)
        return PARTIDA_ERROR;

    do
    {
        printf("Generando tablero...\n");

        ret = generarTablero(tablero, config);
        if(ret != EXITO)
        {
            vaciarTablero(tablero);
            return PARTIDA_ERROR;
        }

        printf("Validando tablero...\n");

        ret = validarTablero(tablero);

        if(ret != EXITO)
            vaciarTablero(tablero);

    } while(ret != EXITO);

    printf("Tablero valido.\n");

    ret = exportarTablero(tablero, ARCH_CARAVANA);
    if(ret != EXITO)
    {
        vaciarTablero(tablero);
        return PARTIDA_ERROR;
    }


    inicializarEstadoJugador(jugador, config->vidas_inicio, tablero->inicio);

    return PARTIDA_EN_CURSO;
}


int puedeRetroceder(const tJugador* jugador, unsigned pasos)
{
    tCursorDC act = jugador->posicionActual;
    tCasillero cas;

    while(pasos--)
    {
        if(verActualDC(act, &cas, sizeof(tCasillero)) != EXITO)
            return NO_RETROCEDE;

        if(cas.tipoEvento == INICIO)
            return NO_RETROCEDE;

        act = anteriorDC(act);
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

int prepararTurno(tJugador* jugador, tTablero* tablero, tCola* colaMovimientos)
{
    int ret;
    unsigned dado;
    char tecla;
    tMovimiento mov;
    tDireccion direccion;
    tCtxEncolarBandidos ctxBandidos;

    if(jugador->pierdeTurno)
    {
        jugador->pierdeTurno = 0;
        printf("Perdiste este turno. Los bandidos se mueven...\n\n");
    }
    else
    {
        do
        {
            printf("Presione ENTER para tirar el dado..\n");
            scanf("%c", &tecla);

            if(tecla != '\n')
                printf("Tecla invalida.\n");

        } while(tecla != '\n');

        dado = tirarDado();

        printf("El dado giro en el aire y cayo, el numero es: %u.\n", dado);

        direccion = pedirDireccion(jugador, dado);

        if(direccion == ATRAS)
            printf("Retrocede %u casilleros, suerte!!.\n\n", dado);
        else
            printf("Avanza %u casilleros, suerte!!.\n\n", dado);

        ret = generarMovimientoJugador(jugador, tablero, dado, &mov, direccion);
        if(ret != EXITO)
            return ret;

        ret = encolar(colaMovimientos, &mov, sizeof(tMovimiento));
        if(ret != EXITO)
            return ret;
    }

    ctxBandidos.jugador = jugador;
    ctxBandidos.tablero = tablero;
    ctxBandidos.colaMovimientos = colaMovimientos;

    ret = mapLista(&tablero->bandidos, accionEncolarMovimientoBandido, &ctxBandidos);

    if(ret != EXITO)
        return ret;

    return EXITO;
}


void aplicarEvento(tJugador* jugador, tCursorDC posicion)
{
    tCasillero cas;
    tTipoEvento despejado = DESPEJADO;

    if(verActualDC(posicion, &cas, sizeof(tCasillero)) != EXITO)
        return;

    switch(cas.tipoEvento)
    {
        case PREMIO:
            printf("Encontraste un premio. Sumaste 1 punto.\n\n");
            jugador->puntaje++;
            modificarActualDC(posicion, accionCambiarEvento, &despejado);
            break;

        case VIDA_EXTRA:
            printf("Encontraste una vida extra. Sumaste 1 vida.\n\n");
            jugador->vidas++;
            modificarActualDC(posicion, accionCambiarEvento, &despejado);
            break;

        case OASIS:
            printf("Llegaste a un oasis. Tendras proteccion contra el proximo peligro.\n\n");
            jugador->protegidoPorOasis = 1;
            modificarActualDC(posicion, accionCambiarEvento, &despejado);
            break;

        case TORMENTA:
            printf("Caiste en una tormenta de arena.\n\n");

            if(!jugador->protegidoPorOasis)
            {
                printf("Perdes el proximo turno.\n\n");
                jugador->pierdeTurno = 1;
            }
            else
            {
                printf("La proteccion del oasis te salvo de la tormenta, Suerte!.\n\n");
                jugador->protegidoPorOasis = 0;
            }

            modificarActualDC(posicion, accionCambiarEvento, &despejado);
            break;

        default:
            break;
    }
}

void interceptarJugador(tJugador* jugador, const tBandido* bandido, tCursorDC posicionIntercepcion, tTablero* tablero)
{
    int tieneJugador;
    unsigned idBandido;

    if(jugador->protegidoPorOasis)
    {
        printf("Tenias proteccion de oasis. El bandido no te quita vida.\n\n");
        jugador->protegidoPorOasis = 0;
    }
    else
    {
        printf("Fuiste interceptado por el bandido %u. Volves al inicio.\n\n",
               bandido->idBandido);

        tieneJugador = 0;
        modificarActualDC(posicionIntercepcion, accionCambiarTieneJugador, &tieneJugador);

        tieneJugador = 1;
        modificarActualDC(tablero->inicio, accionCambiarTieneJugador, &tieneJugador);

        jugador->posicionActual = tablero->inicio;
        jugador->vidas--;

        printf("Vidas restantes: %d.\n", jugador->vidas);
    }

    idBandido = 0;
    modificarActualDC(posicionIntercepcion, accionCambiarIdBandido, &idBandido);

    modificarEnListaPorClave(&tablero->bandidos,&bandido->idBandido,cmpBandidoPorId,accionDesactivarBandido,NULL);
}


int procesarMovimientos(tCola* cola, tJugador* jugador, tTablero* tablero)
{
    tMovimiento mov;
    tCasillero casOrigen;
    tCasillero casDestino;
    tBandido bandido;
    int ret;
    int tieneJugador;
    unsigned idBandido;

    while(!colaVacia(cola))
    {
        ret = desencolar(cola, &mov, sizeof(tMovimiento));
        if(ret != EXITO)
            return ret;

        if(mov.actor == ACTOR_JUGADOR)
        {
            tieneJugador = 0;
            ret = modificarActualDC(mov.origen, accionCambiarTieneJugador, &tieneJugador);
            if(ret != EXITO)
                return ret;

            tieneJugador = 1;
            ret = modificarActualDC(mov.destino, accionCambiarTieneJugador, &tieneJugador);
            if(ret != EXITO)
                return ret;

            jugador->posicionActual = mov.destino;

            aplicarEvento(jugador, mov.destino);

            pausar();
        }
        else
        {
            ret = buscarEnListaPorClave(&tablero->bandidos,&bandido,sizeof(tBandido),&mov.idActor,cmpBandidoPorId);

            if(ret == EXITO && bandido.activo)
            {
                ajustarDestinoBandido(&mov);

                if(!mismoCursorDC(mov.destino, bandido.posicionActual))
                {
                    ret = verActualDC(bandido.posicionActual, &casOrigen, sizeof(tCasillero));
                    if(ret != EXITO)
                        return ret;

                    if(casOrigen.idBandido == bandido.idBandido)
                    {
                        idBandido = 0;
                        ret = modificarActualDC(bandido.posicionActual,
                                                accionCambiarIdBandido,
                                                &idBandido);
                        if(ret != EXITO)
                            return ret;
                    }

                    idBandido = bandido.idBandido;
                    ret = modificarActualDC(mov.destino,accionCambiarIdBandido,&idBandido);
                    if(ret != EXITO)
                        return ret;

                    ret = modificarEnListaPorClave(&tablero->bandidos,&bandido.idBandido,cmpBandidoPorId,
                                                   accionActualizarPosicionBandido,&mov.destino);
                    if(ret != EXITO)
                        return ret;
                }
            }
        }
    }

    ret = verActualDC(jugador->posicionActual, &casDestino, sizeof(tCasillero));
    if(ret != EXITO)
        return ret;

    if(casDestino.idBandido)
    {
        ret = buscarEnListaPorClave(&tablero->bandidos,&bandido,sizeof(tBandido),&casDestino.idBandido,cmpBandidoPorId);
        if(ret == EXITO && bandido.activo)
        {
            interceptarJugador(jugador, &bandido, jugador->posicionActual, tablero);
            pausar();
        }
    }

    return EXITO;
}

tResultadoPartida jugarPartida(tJugador* jugador, tTablero* tablero, tConfig* config)
{
    tCola cola;
    tCasillero casActual;
    tResultadoPartida resultado;
    int ret;

    resultado = inicializarPartida(jugador, tablero, config);

    if(resultado != PARTIDA_EN_CURSO)
        return resultado;

    crearCola(&cola);

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

        ret = verActualDC(jugador->posicionActual, &casActual, sizeof(tCasillero));
        if(ret != EXITO)
        {
            vaciarCola(&cola);
            return PARTIDA_ERROR;
        }

        if(casActual.tipoEvento == SALIDA)
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
    {
       printf("Felicitaciones %s, llegaste a la Ciudad Refugio!.\n", jugador->nickname);
            jugador->puntaje++;
    }else if (resultado == PARTIDA_PERDIDA)
        printf("Game over %s, perdiste todas tus vidas!.\n", jugador->nickname);
    else
        printf("Ocurrio un error durante la partida.\n");

    mostrarHistorialJugador(jugador);
    if(guardarPartida(ARCH_PARTIDAS,jugador, resultado)!=EXITO)
        printf("No se pudo guardar la partida.\n");

    vaciarLista(&jugador->historialMovimientos);
}
