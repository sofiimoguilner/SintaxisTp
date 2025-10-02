# include<stdio.h>
// Desarrollamos una función que recibe un caracter numerico y retorna un número entero
# define ERROR -1

int convierteCaracterNumericoAEntero (char *caracter);

int main (void)
{
   int unEntero;
   char unCaracter;
   printf("ingrese un caracter numerico\n");
   scanf ("%c", &unCaracter);
   unEntero= convierteCaracterNumericoAEntero(&unCaracter);

  return 0;
}

int convierteCaracterNumericoAEntero (char *caracter)
{  
    int entero;
	if (*caracter>='0' && *caracter<='9')
	{
		entero=(*caracter)-'0';
		printf("El caracter '%c' convertido a numero entero es '%d'\n", *caracter, entero);
	    return entero;
	}
	else
	{
		printf("ERROR: no ingreso un caracter numérico\n");
		return ERROR;
	}
}
