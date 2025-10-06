#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
#define ERROR -1

// funcion punto 1 (adaptada)
int verifica(char* cadena) {
    int i = 0;
    int c = cadena[i];

    while (c != '\0') {
        if (!(isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/')) {
            return 0;
        }
        i++;
        c = cadena[i];
    }
    return 1;
}


// funcion punto 2
int convierteCaracterNumericoAEntero(const char *caracter)
{  
    int entero;
	if (*caracter>='0' && *caracter<='9')
	{
		entero=(*caracter)-'0';
	    return entero;
	}
	else
	{
		printf("ERROR: no ingreso un caracter numérico\n");
		return ERROR;
	}
}

// funcion auxiliar para saber si num es negativo
int esSignoNegativo(const char* exp, int i) {
    return (i == 0 || exp[i-1] == '+' || exp[i-1] == '-' || 
            exp[i-1] == '*' || exp[i-1] == '/');
}

// Nodos
typedef struct Nodo {
    int valor;
    char operador;
    struct Nodo* siguiente;
} Nodo;

// Apilar y desapilar numeros y operadores
void pushNum(Nodo** tope, int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->siguiente = *tope;
    *tope = nuevo;
}

int popNum(Nodo** tope) {
    if (*tope == NULL) {
        printf("ERROR: pila de números vacía\n");
        return ERROR;
    }
    Nodo* temp = *tope;
    int valor = temp->valor;
    *tope = temp->siguiente;
    free(temp);
    return valor;
}

void pushOp(Nodo** tope, char op) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->operador = op;
    nuevo->siguiente = *tope;
    *tope = nuevo;
}

char popOp(Nodo** tope) {
    if (*tope == NULL) {
        printf("ERROR: pila de operadores vacía\n");
        return '\0';
    }
    Nodo* temp = *tope;
    char op = temp->operador;
    *tope = temp->siguiente;
    free(temp);
    return op;
}

int precedencia(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void aplicarOperacion(Nodo** pilaNum, Nodo** pilaOp) {
    int b = popNum(pilaNum);
    int a = popNum(pilaNum);
    char op = popOp(pilaOp);
    int res = 0;

    if (a == ERROR || b == ERROR || op == '\0') return;

    switch(op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': 
            if (b == 0) {
                printf("ERROR: división por cero\n");
                return;
            }
            res = a / b; 
            break;
    }
    pushNum(pilaNum, res);
}

int evaluar(const char* exp) {
    Nodo* pilaNum = NULL;
    Nodo* pilaOp = NULL;
    int i = 0;
    int esNegativo = 0;


    while (exp[i] != '\0') {
        if (isdigit(exp[i]) || (exp[i] == '-' && esSignoNegativo(exp, i))) {
            
            if (exp[i] == '-') {
                esNegativo = 1;
                i++;
            }
            
            int valor = 0;
            while (isdigit(exp[i])) {
                int digito = convierteCaracterNumericoAEntero(&exp[i]);
                if (digito == ERROR) return ERROR;
                valor = valor * 10 + digito;
                i++;
            }
            
            if (esNegativo) {
                valor = -valor;
            }
            
            pushNum(&pilaNum, valor);
        } else {
            // Es un operador
            char op = exp[i];
            while (pilaOp != NULL) {
                char top = popOp(&pilaOp);
                if (precedencia(top) >= precedencia(op)) {
                    pushOp(&pilaOp, top); 
                    aplicarOperacion(&pilaNum, &pilaOp);
                } else {
                    pushOp(&pilaOp, top);
                    break;
                }
            }
            pushOp(&pilaOp, op);
            i++;
        }
    }

    while (pilaOp != NULL) {
        aplicarOperacion(&pilaNum, &pilaOp);
    }

    return popNum(&pilaNum);
}

void infijoAPostfijo(char *expresion) {
    Nodo* pilaOp = NULL;
    char salida[MAX * 2] = "";
    int k = 0;

    for (int i = 0; expresion[i]; i++) {
        if (isdigit(expresion[i]) || (expresion[i] == '-' && esSignoNegativo(expresion, i))) {
            if (expresion[i] == '-') {
                salida[k++] = '-';
                i++;
            }
            
            while (isdigit(expresion[i])) {
                salida[k++] = expresion[i++];
            }
            salida[k++] = ' ';
            i--;
        } else {
            char op = expresion[i];
            while (pilaOp != NULL) {
                char top = popOp(&pilaOp);
                if (precedencia(top) >= precedencia(op)) {
                    salida[k++] = top;
                    salida[k++] = ' ';
                } else {
                    pushOp(&pilaOp, top);
                    break;
                }
            }
            pushOp(&pilaOp, op);
        }
    }

    while (pilaOp != NULL) {
        salida[k++] = popOp(&pilaOp);
        salida[k++] = ' ';
    }
    salida[k] = '\0';
    printf("Polaca inversa: %s\n", salida);
}

int main() {
    char expresion[MAX];

    printf("Ingrese una expresion: ");

    if (fgets(expresion, MAX, stdin) == NULL) {
        printf("Error al leer la entrada.\n");
        return 1;
    }
    
    expresion[strcspn(expresion, "\n")] = 0;

    // funcion punto 1
    if (!verifica(expresion)) {
        return 1;
    }

	infijoAPostfijo(expresion);
	
    int resultado = evaluar(expresion);
    if (resultado != ERROR) {
        printf("Resultado: %d\n", resultado);
    }

    printf("\nPresione ENTER para salir.");
    getchar();

    return 0;

}

