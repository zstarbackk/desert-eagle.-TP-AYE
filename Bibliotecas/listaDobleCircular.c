#include "listaDobleCircular.h"


void crearListaDC(tListaDC* pl)
{
    *pl = NULL;
}

int insertarAlFinal(tListaDC *pl,const void *d,unsigned tamInfo)
{
    tNodoListaDC *nue;
    nue=(tNodoListaDC*)malloc(sizeof(tNodoListaDC));
    if(!nue)
        return ERROR_MEMORIA;
    nue->info=malloc(tamInfo);
    if(!nue->info)
    {
        free(nue);
        return ERROR_MEMORIA;
    }

    memcpy(nue->info,d,tamInfo);
    nue->tamInfo=tamInfo;

    if(!*pl)
    {
        nue->ant=nue;
        nue->sig=nue;
    }else
    {
        nue->sig=(*pl)->sig;
        nue->ant=(*pl);
        (*pl)->sig=nue;
        (*pl)->sig->ant=nue;
    }
    *pl=nue;
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
