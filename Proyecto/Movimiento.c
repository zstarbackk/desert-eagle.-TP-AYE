#include "Movimiento.h"

tMovimiento crearMovimiento(tTipoActor tipo ,unsigned id, tPosicion origen,tPosicion destino)
{
    tMovimiento mov;

    mov.Actor=tipo;
    mov.idActor=id;
    mov.origen=origen;
    mov.destino=destino;
    return mov;
}


tMovimientoHistorico crearMovimientoHistorico(tDireccion direccion,unsigned cantidad)
{
    tMovimientoHistorico movHist;

    movHist.direccion=direccion;
    movHist.cantidad=cantidad;

    return movHist;
}
