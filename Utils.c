#include "Utils.h"

int TirarDado(void)
{
    int r;
    int limite = RAND_MAX - (RAND_MAX % 6);

    do
    {
        r = rand();
    } while (r >= limite);

    return (r % 6) + 1;
}

int AbrirArchivo(FILE** Pf,const char* NombreArchivo,const char* Modo)
{
    *Pf=fopen(NombreArchivo,Modo);

    if(!*Pf)
    {
        fprintf(stderr,"No se pudo abrir el archivo: %s\n",NombreArchivo);
        return ERROR_APERTURA;
    }

    return EXITO;
}

int trozarLinea(char *linea, char **clave, char **valor)
{
    char *separador = strchr(linea, '=');
    if (separador == NULL)
        return FIN_ARCHIVO;

    *separador = '\0';
    *clave = linea;
    *valor = separador + 1;
    return EXITO;
}
