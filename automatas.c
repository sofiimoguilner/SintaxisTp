#include <stdio.h>
#include <ctype.h>

// Funcion para mapear cada caracter a una columna de la tabla
int columna(int c) 
{
    if (c == '+' || c == '-') return 0;
    if (c == '0') return 1;
    if (c >= '1' && c <= '9') return 2;
    if (c >= '0' && c <= '7') return 3;
    if (c == '8' || c == '9') return 4;
    if (c == 'x' || c == 'X') return 5;
    if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return 6;
    if (c == '#') return 7;
    return -1;
}

// Funcion que valida que la cadena solo tenga caracteres permitidos
int verifica(char* cadena) 
{
    int i = 0;
    int c = cadena[i];

    while (c != '\0') 
    {
        if (!(c == '+' || c == '-' || isdigit(c) || c == 'x' || c == 'X' ||
              (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || c == '#')) 
              {
            return 0;
        }
        i++;
        c = cadena[i];
    }
    return 1;
}

// Función que recorre la tabla de transiciones
int esPalabra(char* cadena, int* estadoFinal) 
{
    static int tt[11][8] = 
    {
        /*        +/-   0     1-9   0-7   8-9   xX    a-f   # */
        /*0*/ {   1,    4,    3,   -1,   -1,   -1,   -1,   -1 },
        /*1*/ {  -1,    4,    3,   -1,   -1,   -1,   -1,   -1 },
        /*2*/ {  -1,    3,    3,   -1,   -1,   -1,   -1,   -1 },
        /*3*/ {  -1,    3,    3,   -1,    3,   -1,   -1,    3 }, // acepta decimal
        /*4*/ {  -1,    8,    9,    9,   -1,    5,   -1,   -1 }, //
        /*5*/ {  -1,    6,    6,   -1,   -1,   -1,    6,   -1 },
        /*6*/ {  -1,    7,    7,   -1,   -1,   -1,    7,   -1 },
        /*7*/ {  -1,    7,    7,   -1,   -1,   -1,    7,    7 }, // acepta hexa
        /*8*/ {  -1,    9,   -1,    9,   -1,   -1,   -1,    9 }, // acepta "0" octal
        /*9*/ {  -1,   10,   10,   10,   -1,   -1,   -1,   -1 },
        /*10*/{  -1,   10,   10,   10,   -1,   -1,   -1,   -1 }  // acepta octal
    };

    int e = 0;
    int i = 0;
    int c = cadena[i];
    int col;

    while (c != '\0') 
    {
        col = columna(c);
        if (col == -1) return 0;

        e = tt[e][col];
        if (e == -1) return 0;

        i++;
        c = cadena[i];
    }

    *estadoFinal = e;

    if (e == 3 || e == 7 || e == 8 || e == 9 || e == 10)
        return 1;
    else
        return 0;
}

int main() 
{
    char cadena[200];
    int estadoFinal;
    int decimales = 0, octales = 0, hexadecimales = 0, errores = 0;

    printf("Ingrese la cadena (numeros separados por #): ");
    scanf("%s", cadena);

    // Separar en tokens por '#'
    char *token = strtok(cadena, "#");
    while (token != NULL) 
    {
        if (verifica(token)) 
        {
            if (esPalabra(token, &estadoFinal)) 
            {
                if (estadoFinal == 3) 
                {
                    printf("%s -> DECIMAL\n", token);
                    decimales++;
                } else if (estadoFinal == 7) 
                {
                    printf("%s -> HEXADECIMAL\n", token);
                    hexadecimales++;
                } else if (estadoFinal == 8 || estadoFinal == 9 || estadoFinal == 10) 
                {
                    printf("%s -> OCTAL\n", token);
                    octales++;
                }
            } else 
            {
                printf("%s -> ERROR LEXICO\n", token);
                errores++;
            }
        } else 
        {
            printf("%s -> CARACTER INVALIDO\n", token);
            errores++;
        }
        token = strtok(NULL, "#");
    }

    printf("\nResumen:\n");
    printf("Decimales: %d\n", decimales);
    printf("Octales: %d\n", octales);
    printf("Hexadecimales: %d\n", hexadecimales);
    printf("Errores lexicos: %d\n", errores);

    return 0;
}
