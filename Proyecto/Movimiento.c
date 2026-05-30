#include "Movimiento.h"

tMovimiento crearMovimiento(tTipoActor tipo ,unsigned id, tPosicion origen,tPosicion destino,tDireccion direccion)
{
    tMovimiento mov;

    mov.actor=tipo;
    mov.idActor=id;
    mov.origen=origen;
    mov.destino=destino;
    mov.direccion=direccion;
    return mov;
}


tMovimientoHistorico crearMovimientoHistorico(tDireccion direccion,unsigned cantidad)
{
    tMovimientoHistorico movHist;

    movHist.direccion=direccion;
    movHist.cantidad=cantidad;

    return movHist;
}
