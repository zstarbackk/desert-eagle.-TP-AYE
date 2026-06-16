#include "Config.h"

void cargarValor(const char *clave,const char *valor, tConfig *config)
{
    if (strcmp(clave, "cantidad_posiciones") == 0)
        sscanf(valor, "%u", &config->cantidad_posiciones);
    else if (strcmp(clave, "vidas_inicio") == 0)
        sscanf(valor, "%u", &config->vidas_inicio);
    else if (strcmp(clave, "maximo_bandidos") == 0)
        sscanf(valor, "%u", &config->maximo_bandidos);
    else if (strcmp(clave, "maximo_premios") == 0)
        sscanf(valor, "%u", &config->maximo_premios);
    else if (strcmp(clave, "maximo_vidas_extra") == 0)
        sscanf(valor, "%u", &config->maximo_vidas_extra);
    else if (strcmp(clave, "maximo_oasis") == 0)
        sscanf(valor, "%u", &config->maximo_oasis);
    else if (strcmp(clave, "maximo_tormentas") == 0)
        sscanf(valor, "%u", &config->maximo_tormentas);
}

int leerConfiguracion(const char *nombreArchivo, tConfig *config)
{
    FILE *archivo;
    char linea[100];
    char *clave, *valor;
    //Borramos basura
    config->cantidad_posiciones = 0;
    config->maximo_bandidos = 0;
    config->maximo_oasis = 0;
    config->maximo_premios = 0;
    config->maximo_tormentas = 0;
    config->maximo_vidas_extra = 0;
    config->vidas_inicio = 0;

    if ((abrirArchivo(&archivo,nombreArchivo,"rt"))!=EXITO)
        return ERROR_ARCHIVO;

    while (fgets(linea, sizeof(linea), archivo))
        if (trozarLinea(linea, &clave, &valor)==EXITO)
            cargarValor(clave, valor, config);

    fclose(archivo);
    return EXITO;
}

int validarConfig(const tConfig *config)
{
    unsigned int casillerosDisponibles;
    unsigned int elementosHostiles;
    unsigned int elementosFavorables;

    if (config->cantidad_posiciones < 3)
    {
        printf("Error: cantidad_posiciones debe ser al menos 3\n");
        return POCAS_POSICIONES;
    }

    if (config->vidas_inicio == 0)
    {
        printf("Error: vidas_inicio debe ser mayor a 0\n");
        return POCAS_VIDAS;
    }
    casillerosDisponibles = config->cantidad_posiciones - 2;
    elementosHostiles = config->maximo_bandidos + config->maximo_tormentas;
    elementosFavorables = config->maximo_premios +
                                       config->maximo_vidas_extra +
                                       config->maximo_oasis;
    if(elementosHostiles + elementosFavorables > casillerosDisponibles)
    {
        printf("Error: demasiados eventos para el tamanio del tablero\n");
        return EXCESO_EVENTOS;
    }
    if (elementosHostiles > casillerosDisponibles * MAX_PORCENTAJE_HOSTILES / 100)
    {
        printf("Error: demasiados elementos hostiles para el tamanio del tablero\n");
        return EXCESO_EVENTOS;
    }

    if (elementosFavorables > casillerosDisponibles * MAX_PORCENTAJE_FAVORABLES / 100)
    {
        printf("Error: demasiados elementos favorables para el tamanio del tablero\n");
        return EXCESO_EVENTOS;
    }

    return EXITO;
}

int cargarConfiguracion(const char *nombreArchivo, tConfig *config)
{
    int ret=leerConfiguracion(nombreArchivo,config);

    if(ret!=EXITO)
    return ret;

    return validarConfig(config);
}
