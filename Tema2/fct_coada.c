/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include "tema2.h"

void *InitC(size_t d)
{
	TCoada *c;
	c = (TCoada*)malloc(sizeof(TCoada));
	if(!c) return NULL; /* se verifica alocarea */
	c->dim =d;
	c->ic=NULL;
	c->sc=NULL;
	return (void*)c;
}

int VidaC(void *c)
{
	if(((TCoada*)c)->ic==NULL && ((TCoada*)c)->sc==NULL) return 1;
	return 0;
}

TLG ExtrQ(void *c)
{
	TLG aux;
	if(((TCoada*)c)->ic != ((TCoada*)c)->sc)
	{
		/* se extrage primul element */
		aux=((TCoada*)c)->ic;
		((TCoada*)c)->ic= aux->urm;
	}
	else
	{
		/* coada devine vida */
		aux=((TCoada*)c)->ic;
		((TCoada*)c)->ic=NULL;
		((TCoada*)c)->sc=NULL;
	}
	return aux;

}

void *IntrQ(void *c, void *ae)
{
	TLG aux;
	aux = (TLG)malloc(sizeof(TCelula));
	if(!aux) return NULL; /* se verifica alocarea */
	aux->info = (Proces*)malloc(sizeof(Proces));
	if(!aux->info)  /* se verifica alocarea */
	{
		free(aux);
		return NULL;
	}
	if(VidaC(c)==1)
	{
		((TCoada*)c)->ic=aux;
		((TCoada*)c)->sc=aux;
		aux->urm=NULL;
		/* se copiaza informatia la adresa ae */
		memcpy(aux->info, ae, sizeof(Proces)); 
		return (void*)c;
	}
	((TCoada*)c)->sc->urm=aux; /* se face inserarea la sfarsit */
	((TCoada*)c)->sc=aux;
	/* se copiaza informatia la adresa ae */
	memcpy(aux->info, ae, sizeof(Proces)); 
	return (void*)c;
}

/* functie care numara elementele unei cozi */
int NrElQ(void *c)
{
	int n=0;
	TLG aux;
	TCoada *caux;
	caux = InitC(sizeof(TCoada));
	if(!caux) return 0;
	while(VidaC(c) != 1)
	{
		aux = ExtrQ(c);
		caux = IntrQ(caux, (Proces*)aux->info);
		n++;
	}
	c = ConcatQ(c, caux);

	return n;
}

/* functie care rastoarna o coada */
void *RastoarnaC(void *c)
{
	TLG aux;
	TStiva *s;
	int n=NrElQ(c), i=n, j=n;
	s=InitS(sizeof(TStiva));
	if(!s) return 0;
	while(i>=1)
	{
		/* se foloseste o stiva auxiliara */
		aux = ExtrQ(c);
		s = Push(s, (Proces*)aux->info, sizeof(Proces));
		i--;
	}
	while(j>=1)
	{
		aux = Pop(s);
		c = IntrQ(c, (Proces*)aux->info);
		j--;
	}

	return (void*)c;
}

/* functie care concateneaza doua cozi */
void *ConcatQ(void *c1, void *c2)
{
	if(VidaC(c1)==1)
	{
		((TCoada*)c1)->ic=((TCoada*)c2)->ic;
		((TCoada*)c1)->sc = ((TCoada*)c2)->sc;;
	}
	else
	{
		((TCoada*)c2)->sc->urm = ((TCoada*)c1)->ic;
		((TCoada*)c2)->sc = ((TCoada*)c1)->sc;
		((TCoada*)c1)->sc=NULL;
	}
	return (void*)c1;
}

/* functie care sorteaza coada */
void *sort(void *c)
{
	TLG aux;
	int min, n=NrElQ(c), i=n, k=0, j;
	void *caux, *caux1;
	caux = InitC(sizeof(TCoada));
	if(!caux) return 0;
	caux1=InitC(sizeof(TCoada));
	if(!caux1) return 0;
	
	while(i>=1)
	{
		k=0;
		min = priority_min(c, i);
		while(VidaC(c)!=1)
		{
			aux = ExtrQ(c);
			if(min != ((Proces*)aux->info)->priority)
			{
				caux = IntrQ(caux, (Proces*)aux->info);		
			}
			else
			{
				caux1 = IntrQ(caux1, (Proces*)aux->info);
				k++;
				j=k;
			}
		}
		/* se sorteaza coada dupa timp */
		caux1=time_sort(caux1);
		while(j>=1)
		{
			aux=ExtrQ(caux1);
			caux=IntrQ(caux, (Proces*)aux->info);
			j--;
		}
		c = ConcatQ(c, caux);
		caux=InitC(sizeof(TCoada));
		caux1=InitC(sizeof(TCoada));
		i=i-k;
	}
	
	c = RastoarnaC(c);

	return (void*)c;
}