# include<stdio.h>
// Desarrollamos una función que recibe un caracter numerico y retorna un número entero
# define ERROR -1

int convierteCaracterNumericoAEntero (char caracter);

int main (void)
{
  char unCaracter='3';
  char otroCaracter='7';
  char caracterNoNumerico= 'z';
  
  int unNumero;
  int otroNumero;
  int noNumero;
  
  unNumero=convierteCaracterNumericoAEntero (unCaracter);
  printf("El caracter '%c' convertido a numero entero es '%d'\n", unCaracter, unNumero);
 
  otroNumero=convierteCaracterNumericoAEntero (otroCaracter);
  printf("El caracter '%c' convertido a numero entero es '%d'\n", otroCaracter, otroNumero);

  noNumero=convierteCaracterNumericoAEntero (caracterNoNumerico);
  printf("El caracter '%c' convertido a numero entero es '%d'\n", caracterNoNumerico, noNumero);

 return 0;
}

int convierteCaracterNumericoAEntero (char caracter)
{  int entero;
	if (caracter>='0' && caracter<='9')
	{
		entero=caracter-'0';
	    return entero;
	}
	else
	{
		printf("ERROR: ingrese un caracter numérico\n");
		return ERROR;
	}
}

