#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include "Errores.h"
#include "Utils.h"
#include <stdio.h>
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

void cargarValor(char *clave, char *valor, tConfig *config);
int leerConfiguracion(char *nombreArchivo, tConfig *config);
int validarConfig(tConfig *config);
int crearArchivo();


#endif // CONFIG_H_INCLUDED
