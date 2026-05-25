#include "Movimiento.h"

tMovimiento crearMovimiento(tTipoActor tipo ,unsigned id, tDireccion direccion,unsigned cantidad)
{
    tMovimiento mov;

    mov.tipoActor=tipo;
    mov.idActor=id;
    mov.direccion=direccion;
    mov.cantidad=cantidad;

    return mov;
}


tMovimientoHistorico crearMovimientoHistorico(tDireccion direccion,unsigned cantidad)
{
    tMovimientoHistorico movHist;

    movHist.direccion=direccion;
    movHist.cantidad=cantidad;

    return movHist;
}
