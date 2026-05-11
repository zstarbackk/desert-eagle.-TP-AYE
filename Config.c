#include "Config.h"
int crearArchivo(){
    FILE * pf = fopen("config.txt", "wt");
    tConfig config;
    if(pf ==  NULL){
        printf("error al generar archivo de configuracion...\n\n");
        return ERROR_ESCRITURA;
    }
    config.cantidad_posiciones = 10;
    config.maximo_bandidos = 1;
    config.maximo_oasis = 1;
    config.maximo_premios = 2;
    config.maximo_tormentas = 0;
    config.maximo_vidas_extra = 0;
    config.vidas_inicio = 1;
    fprintf(pf, "cantidad_posiciones=%u\n", config.cantidad_posiciones);
    fprintf(pf, "vidas_inicio=%u\n", config.vidas_inicio);
    fprintf(pf, "maximo_bandidos=%u\n", config.maximo_bandidos);
    fprintf(pf, "maximo_premios=%u\n", config.maximo_premios);
    fprintf(pf, "maximo_vidas_extra=%u\n", config.maximo_vidas_extra);
    fprintf(pf, "maximo_oasis=%u\n", config.maximo_oasis);
    fprintf(pf, "maximo_tormentas=%u\n", config.maximo_tormentas);
    fclose(pf);
}

void cargarValor(char *clave, char *valor, tConfig *config)
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

int leerConfiguracion(char *nombreArchivo, tConfig *config)
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

    if ((AbrirArchivo(&archivo,nombreArchivo,"rt"))!=EXITO)
        return ERROR_LECTURA;

    while (fgets(linea, sizeof(linea), archivo))
        if (trozarLinea(linea, &clave, &valor)==EXITO)
            cargarValor(clave, valor, config);

    fclose(archivo);
    return EXITO;
}

int validarConfig(tConfig *config)
{
    unsigned int casillerosDisponibles = config->cantidad_posiciones - 2;
    unsigned int elementosHostiles = config->maximo_bandidos + config->maximo_tormentas;
    unsigned int elementosFavorables = config->maximo_premios +
                                       config->maximo_vidas_extra +
                                       config->maximo_oasis;

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
