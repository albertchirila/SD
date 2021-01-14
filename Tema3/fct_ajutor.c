/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include "tema3.h"

/* functie care cauta in lista caracterul x */
int cautaL(TLista L, char x)
{
	TLista p=L;
	for(;p!=NULL;p=p->urm) /* parcurg lista */
	{
		if(p->q->info == x) return 1;
	}
	return 0;
}

/* functie care imi insereaza in lista caracterul x */
TLista Inserare(TLista L, char x)
{
	TLista p=L;
	TLista aux;
	if(cautaL(L, x)==1) return p;
	aux=AlocCelula(); /* se aloca celula */
	if(!aux) return NULL; /* se verifica alocarea celulei */
	aux->q=AlocNod(x);  /* se aloca nodul */
	if(!aux->q) return NULL; /* se verifica alocarea nodului */
	aux->urm=p;
	p=aux;
	return p;
}

/* functie care muta pointer-ul la lista pe elementul de lista cautat */
TLista muta_pointer(TLista L, char x)
{
	TLista p=L;
	for(;p!=NULL;p=p->urm)
	{
		if(p->q->info == x) return p;
	}
	return NULL;
}

/* functie care muta pointer-ul la nod pe nodul cautat */
TArb muta(TArb a, char *x)
{
	TArb arb=a;
	int i=0;
	if(x[i]=='/') i=1;
	while(x[i]!='\0')
	{
		TLista l=muta_pointer(arb->p, x[i]);
		arb=l->q;
		i++;
	}
	return arb;
}

/* functie care returneaza lungimea unui sir de caractere */
int numara(char *x)
{
	int n=strlen(x);
	return n;
}