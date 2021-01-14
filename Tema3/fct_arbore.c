/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include "tema3.h"

/* functie care creeaza radacina arborelui (root) */
TArb InitArbore(char x)
{
	TArb a;
	a=(TArb)malloc(sizeof(TNod)); /* se aloca nodul */
	if(!a) return NULL; /* se verifica alocarea nodului */
	a->info=x; /* se introduce informatia in nod */
	a->p=NULL; /* se initializeaza lista nodului cu NULL */
	return a;
}

/* functie care aloca o celula */
TLista AlocCelula()
{
	TLista aux;
	aux=(TLista)malloc(sizeof(TCelula)); /* se aloca celula */
	if(!aux) return NULL; /* se verifica alocarea */
	aux->q=NULL; /*se initializeaza nodul cu NULL */
	aux->urm=NULL;
	return aux;
}

/* functie care aloca un nod */
TArb AlocNod(char x)
{
	TArb aux;
	aux=(TArb)malloc(sizeof(TNod)); /* se aloca nodul */
	if(!aux) return NULL; /* se verifica alocarea */
	aux->info=x; /* se introduce informatia in nod */
	aux->p=NULL; /* se initializeaza lista nodului cu NULL */
	return aux;
}

/* functie care cauta in arbore sirul de caractere x */
int cautaArb(TArb a, char *x)
{
	int i=0, j=0;
	TArb arb=a;
	int k=numara(x);

	/* daca exista doar root */
	if(arb->p==NULL) return 0;

	if(x[i]=='/')
	{
		i++;
		k--;
	}

	while(arb->p!=NULL && x[i]!='\0')
	{
		TLista l=muta_pointer(arb->p, x[i]);
		if(l==NULL) return 0; /* daca nu s-a gasit caracterul */
		arb=l->q;
		i++;
		j++;
	}
	if(k!=j) return 0;
	return 1;
}