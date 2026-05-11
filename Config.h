#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "Utils.h"
#include <string.h>
#define MAX_PORCENTAJE_HOSTILES 30
#define MAX_PORCENTAJE_FAVORABLES 40

typedef struct
{
    unsigned cantidad_posiciones;
    unsigned vidas_inicio;
    unsigned maximo_bandidos;
    unsigned maximo_premios;
    unsigned maximo_vidas_extra;
    unsigned maximo_oasis;
    unsigned maximo_tormentas;
} tConfig;

int leerConfiguracion(char *nombreArchivo, tConfig *config);
int validarConfig(tConfig *config);

#endif // CONFIG_H_INCLUDED
