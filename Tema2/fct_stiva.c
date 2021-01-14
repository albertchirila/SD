/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include "tema2.h"

/* functie initializare stiva */
void *InitS(size_t d)
{
	TStiva *s;
	s = (TStiva*)malloc(sizeof(TStiva)); /* se aloca stiva */
	if(!s) return NULL; /* se verifica alocarea */
	s->dim =d;
	s->vf = NULL;
	return (void*)s;
}

/* functie care verifica daca stiva este vida */
int VidaS(void *s)
{
	if(((TStiva*)s)->vf==NULL) return 1;
	return 0;
}

/* functie care introduce element in stiva */
void *Push(void *s, void *ae, size_t d)
{
	TLG aux = (TLG)malloc(sizeof(TCelula));
	if(!aux) return NULL; /* se verifica alocarea */
	aux->info = (Proces*)malloc(d);
	if(!aux->info) /* se verifica alocarea */
	{
		free(aux);
		return NULL;
	}
	if(VidaS(s)==1)
	{
		((TStiva*)s)->vf=aux;
		aux->urm=NULL;
		memcpy(aux->info, ae, d); /* se copiaza informatia la adresa ae */
		return (void*)s;
	}
	memcpy(aux->info, ae, d); /* se copiaza informatia la adresa ae */
	aux->urm=((TStiva*)s)->vf;
	((TStiva*)s)->vf=aux; /* se insereaza la inceput */
	return (void*)s;
}

/* functie care extrage un element din varful stivei */
TLG Pop(void *s)
{
	TLG aux;
	int x = NrElS(s);
	if(x==1)
	{
		aux = ((TStiva*)s)->vf;
		((TStiva*)s)->vf=NULL;
		return aux;
	}
	/* se extrage elemntu din varful stivei */
	aux = ((TStiva*)s)->vf;
	((TStiva*)s)->vf=aux->urm;

	return aux;
}

/* functie care rastoarna stiva */
void *RastoarnaS(void *s, size_t d)
{
	TLG aux;
	TCoada *c;
	c = InitC(sizeof(TCoada));
	if(!c) return 0;
	while(VidaS(s) != 1)
	{
		aux = Pop(s);
		/* se foloseste coada auxiliara */
		c = IntrQ(c, (Proces*)aux->info);
	}
	while(VidaC(c) != 1)
	{
		aux = ExtrQ(c);
		s = Push(s, (Proces*)aux->info, d);
	}
	return (void*)s;
}

/* functie care concateneaza stiva s2 si stiva vida s1 */
void *ConcatS(void *s1, void *s2)
{
	if(VidaS(s1)==1)
	{
		((TStiva*)s1)->vf = ((TStiva*)s2)->vf;
	}
	return (void*)s1;
}

/* functie care numara elementele stivei */
int NrElS(void *s)
{
	int n=0;
	TLG aux;
	aux = ((TStiva*)s)->vf;
	while(aux)
	{
		aux=aux->urm;
		n++;
	}
	return n;
}
