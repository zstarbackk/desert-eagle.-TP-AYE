#ifndef LISTADOBLECIRCULAR_H_INCLUDED
#define LISTADOBLECIRCULAR_H_INCLUDED

typedef struct tnodo
{
    void* info;
    unsigned tamInfo;
    struct tnodo* sig;
    struct tnodo* ant;
} tNodoListaDC;

typedef tNodoListaDC* tListaDC; // siempre apunta al ultimo por ser circular
typedef tNodoListaDC* tCursorDC; //pos especifica en la lista

void crearListaDC(tListaDC* pl);

int insertarAlFinalDC(tListaDC *pl,const void *d,unsigned tamInfo);
void vaciarListaDC(tListaDC *pl);

int listaVaciaDC(const tListaDC* pl);

tCursorDC obtenerPrimeroDC(const tListaDC* pl);
tCursorDC obtenerUltimoDC(const tListaDC* pl);
tCursorDC siguienteDC(tCursorDC cursor);
tCursorDC anteriorDC(tCursorDC cursor);

int verActualDC(tCursorDC cursor, void* dato, unsigned tamDato);
int modificarActualDC(tCursorDC cursor, void (*accion)(void* dato, void* ctx), void* ctx);

int mismoCursorDC(tCursorDC a, tCursorDC b);

tCursorDC avanzarNDC(tCursorDC cursor, unsigned n);
tCursorDC retrocederNDC(tCursorDC cursor, unsigned n);



#endif // LISTADOBLEF_H_INCLUDED
