#ifndef TDALISTADINAMICA_H_INCLUDED
#define TDALISTADINAMICA_H_INCLUDED

typedef struct sNodoL
{
    void* info;
    unsigned tamInfo;
    struct sNodoL* sig;
} tNodoL;

typedef tNodoL* tLista;

void crearLista(tLista* pl);
int listaLlena(const tLista* pl, unsigned tamInfo);
int listaVacia(const tLista* pl);
int insertarAlFinal(tLista* pl, const void* info, unsigned tamInfo);
void vaciarLista(tLista* pl);
int mapLista(tLista* pl, int (*accion)(void* dato, unsigned tamDato, void* ctx), void* ctx);

int insertarOrdenado(tLista* pl, const void* info, unsigned tamInfo,
                     int (*cmp)(const void*, const void*),
                     void (*accion)(void*, const void*));

int insertarOrdenadoAdelante(tLista* pl, const void* info, unsigned tamInfo,
                             int (*cmp)(const void*, const void*), int duplicados,
                             void (*accion)(void*, const void*));

int insertarOrdenadoAtras(tLista* pl, const void* info, unsigned tamInfo,
                          int (*cmp)(const void*, const void*), int duplicados,
                          void (*accion)(void*, const void*));

int eliminarNodoPrimerApEnListaOrdenada(tLista* pl, void* info, unsigned tamBuffer,
                                        int (*cmp)(const void*, const void*));

int eliminarNodoTodasApEnListaOrdenada(tLista* pl, void* info,
                                       int (*cmp)(const void*, const void*));

int eliminarNodoPrimerApEnListaDesordenada(tLista* pl, void* info, unsigned tamBuffer,
                                           int (*cmp)(const void*, const void*));

int eliminarNodoTodasApEnListaDesordenada(tLista* pl, void* info,
                                          int (*cmp)(const void*, const void*));

void seleccionSortLista(tLista* pl, int (*cmp)(const void*, const void*));

void mostrarLista (const tLista* L, void(*mostrar)(const void*, unsigned));

int buscarEnListaPorPosicion(const tLista* pl, int pos, void* res, unsigned cantBytes);
int buscarEnListaPorClave(const tLista* pl,void* datoEncontrado,unsigned tamDato,const void* clave,
                          int (*cmp)(const void* clave, const void* dato));

int modificarEnListaPorClave(tLista* pl,const void* clave,int (*cmp)(const void* clave, const void* dato),void (*accion)(void* dato, void* ctx),
                             void* ctx);


#endif // TDALISTADINAMICA_H_INCLUDED
