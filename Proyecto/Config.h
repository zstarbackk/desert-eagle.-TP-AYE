#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include "Errores.h"
#include "Utils.h"
#include <stdio.h>
#include <string.h>
#define MAX_PORCENTAJE_HOSTILES 45
#define MAX_PORCENTAJE_FAVORABLES 50

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
int crearArchivoPrueba();
void cargarValor(const char *clave,const char *valor, tConfig *config);
int leerConfiguracion(const char *nombreArchivo, tConfig *config);
int validarConfig(const tConfig *config);
int cargarConfiguracion(const char *nombreArchivo, tConfig *config);


#endif // CONFIG_H_INCLUDED
