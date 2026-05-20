#ifndef ERRORES_H_INCLUDED
#define ERRORES_H_INCLUDED

#define EXITO                1
#define ERROR                0


#define ERROR_MEMORIA          -1
#define ERROR_SIN_MEMORIA      -2


#define ERROR_ARCHIVO          -10
#define ERROR_APERTURA         -11
#define ERROR_LECTURA          -12
#define ERROR_ESCRITURA        -13
#define ERROR_FORMATO_ARCHIVO  -14



#define ERROR_DATO_INVALIDO    -20
#define ERROR_DATO_NULO        -21
#define ERROR_OVERFLOW         -22


#define PILA_VACIA             -30
#define PILA_LLENA             -31


#define COLA_VACIA             -32
#define COLA_LLENA             -33

#define LISTA_VACIA            -34
#define LISTA_LLENA            -35
#define LISTA_NO_ENCONTRADO    -36



#define ERROR_INDICE           -40
#define ERROR_POSICION_INVALIDA -41




#define ERROR_ESTADO           -50
#define ERROR_OPERACION        -51


#define FIN_ARCHIVO            -99
#define POCAS_POSICIONES       -101
#define POCAS_VIDAS            -102
#define EXCESO_EVENTOS         -103


#define JUGADOR_INEXISTENTE    -110


//const char* mensaje_error(int cod);

#endif // ERRORES_H_INCLUDED
