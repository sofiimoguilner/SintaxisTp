#include <stdio.h>
#include <ctype.h>

// Función octal: valida si la cadena es octal
int esOctal(const char *cadena) {
    int i = 0;
    
    if (cadena[i] != '0') return 0;  // octales empiezan con 0
    i++;
    if (cadena[i] == '\0') return 1; // el "0" solo es octal
    for (; cadena[i]; i++) {
        if (cadena[i] < '0' || cadena[i] > '7') return 0;
    }
    return 1;
}

// Función para mapear cada caracter a una columna de la tabla
int columna(int c) {
    if (c == '+' || c == '-') return 0;                  // Columna +/- 
    if (c == '0') return 1;                              // Columna 0
    if (c >= '1' && c <= '9') return 2;                  // Columna 1-9
    if (c >= '0' && c <= '7') return 3;                  // Columna 0-7
    if (c == '8' || c == '9') return 4;                  // Columna 8-9
    if (c == 'x' || c == 'X') return 5;                  // Columna x/X
    if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return 6; // Columna a-f
    if (c == '#') return 7;                              // Columna #
    return -1;                                           // Carácter inválido
}

// Función que valida que la cadena solo tenga caracteres permitidos
int verifica(char* cadena) {
    int i = 0;
    int c = cadena[i];

    while (c != '\0') {
        if (!(c == '+' || c == '-' || isdigit(c) || c == 'x' || c == 'X' ||
              (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || c == '#')) {
            return 0; // Carácter inválido
        }
        i++;
        c = cadena[i];
    }
    return 1;
}

// Función que recorre la tabla de transiciones
int esPalabra(char* cadena, int* estadoFinal) {
    // Matriz de transición: estados (filas) x columnas (símbolos)
    // -1 indica error/transición inválida
    static int tt[11][8] = {
        /*        +/-   0     1-9   0-7   8-9   xX    a-f   # */
        /*q0*/ {   1,    4,    3,   -1,   -1,   -1,   -1,   -1 },
        /*q1*/ {  -1,    4,    3,   -1,   -1,   -1,   -1,   -1 },
        /*q2*/ {  -1,    3,    3,   -1,   -1,   -1,   -1,   -1 },
        /*q3*/ {  -1,    3,    3,   -1,    3,   -1,   -1,    3 }, // acepta DEC
        /*q4*/ {  -1,    8,   -1,    9,   -1,    5,   -1,   -1 }, // <- CAMBIO: ya no va a decimal con 1-9
        /*q5*/ {  -1,    6,    6,   -1,   -1,   -1,    6,   -1 },
        /*q6*/ {  -1,    7,    7,   -1,   -1,   -1,    7,   -1 },
        /*q7*/ {  -1,    7,    7,   -1,   -1,   -1,    7,    7 }, // acepta HEX
        /*q8*/ {  -1,    9,   -1,    9,   -1,   -1,   -1,    9 }, // acepta OCT=0
        /*q9*/ {  -1,   10,   -1,   10,   -1,   -1,   -1,   -1 },
        /*q10*/{  -1,   10,   -1,   10,   -1,   -1,   -1,   -1 }  // acepta OCT
    };

    int e = 0;   // estado inicial q0
    int i = 0;
    int c = cadena[i];
    int col;

    while (c != '\0') {
        col = columna(c);
        if (col == -1) return 0; // caracter inválido

        e = tt[e][col]; // transición
        if (e == -1) return 0; // transición inválida

        i++;
        c = cadena[i];
    }

    *estadoFinal = e; // guardamos dónde terminó

    // Estados de aceptación: q3 (DEC), q7 (HEX), q8/q10 (OCT)
    if (e == 3 || e == 7 || e == 8 || e == 10)
        return 1;
    else
        return 0;
}

int main() {
    char cadena[100];
    int estadoFinal;

    printf("Ingrese la cadena: ");
    scanf("%s", cadena);

    if (verifica(cadena)) {
        if (esPalabra(cadena, &estadoFinal)) {
            if (estadoFinal == 3)
                printf("Es un numero DECIMAL\n");
            else if (estadoFinal == 7)
                printf("Es un numero HEXADECIMAL\n");
            else if (estadoFinal == 8 || estadoFinal == 10)
                printf("Es un numero OCTAL\n");
        } else {
            printf("No es palabra del lenguaje\n");
        }
    } else {
        printf("Posee caracteres invalidos\n");
    }
    return 0;
}
