#include "test.h"
void test_config(){
    tConfig conf;
    crearArchivo();
    leerConfiguracion("config.txt",&conf);
    printf("\n========================================\n");
    printf("        CONFIGURACION DEL JUEGO         \n");
    printf("========================================\n");
    printf("%-25s: %u\n", "Cantidad de posiciones", conf.cantidad_posiciones);
    printf("%-25s: %u\n", "Vidas de inicio",        conf.vidas_inicio);
    printf("----------------------------------------\n");
    printf("%-25s: %u\n", "Maximo Bandidos",       conf.maximo_bandidos);
    printf("%-25s: %u\n", "Maximo Premios",        conf.maximo_premios);
    printf("%-25s: %u\n", "Maximo Vidas Extra",    conf.maximo_vidas_extra);
    printf("%-25s: %u\n", "Maximo Oasis",          conf.maximo_oasis);
    printf("%-25s: %u\n", "Maximo Tormentas",       conf.maximo_tormentas);
    printf("========================================\n\n");
}
