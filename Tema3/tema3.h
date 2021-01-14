/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod
{
	char info;
	struct celula *p;
}TNod, *TArb;

typedef struct celula
{
	TNod *q;
	struct celula *urm;
}TCelula, *TLista;


/* functii din fisierul fct_arbore.c */

TArb InitArbore(char x);
TLista AlocCelula();
TArb AlocNod(char x);
int cautaArb(TArb a, char *x);

/* functii din fisierul fct_ajutor.c */

int cautaL(TLista L, char x);
TLista Inserare(TLista L, char x);
TLista muta_pointer(TLista L, char x);
TArb muta(TArb a, char *x);
int numara(char *x);