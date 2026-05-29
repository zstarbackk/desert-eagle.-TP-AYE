#include "listaDobleCircular.h"


void crearListaDC(tListaDC* pl)
{
    *pl = NULL;
}

int insertarAlFinalDC(tListaDC *pl,const void *d,unsigned tamInfo)
{
    tNodoListaDC *nue;

    nue = (tNodoListaDC*)malloc(sizeof(tNodoListaDC));
    if(!nue)
        return ERROR_MEMORIA;

    nue->info = malloc(tamInfo);
    if(!nue->info)
    {
        free(nue);
        return ERROR_MEMORIA;
    }

    memcpy(nue->info, d, tamInfo);
    nue->tamInfo = tamInfo;

    if(!*pl)
    {
        nue->sig = nue;
        nue->ant = nue;
    }
    else
    {
        nue->sig = (*pl)->sig;   // apunta al primero
        nue->ant = *pl;          // apunta al ultimo

        (*pl)->sig->ant = nue;   // el primero ahora apunta atras al nuevo
        (*pl)->sig = nue;        // el ultimo ahora apunta adelante al nuevo
    }

    *pl = nue; // el nuevo pasa a ser el ultimo

    return EXITO;
}

void vaciarListaDC(tListaDC *pl)
{
    tNodoListaDC *elim;

    if(!*pl)
        return;
    while((*pl)->sig !=*pl)
    {
        //pl siempre apunta al ultimo, y siempre elimino en el segundo
        elim=(*pl)->sig;
        (*pl)->sig=elim->sig;
        elim->sig->ant=*pl;

        free(elim->info);
        free(elim);

    }
    free((*pl)->info);
    free(*pl);

    *pl=NULL;

}
