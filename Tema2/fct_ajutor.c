/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include "tema2.h"

/* functie care construieste structura proces */
Proces *AlocProces()
{
	Proces *aux;
	aux = (Proces*)malloc(sizeof(Proces)); /* se aloca structura proces */
	if(!aux) return NULL; /* se verifica daca alocarea a avut loc */
	aux->pid=0;
	aux->priority=0;  //initializari
	aux->time=0;
	aux->exec_time=0;
	aux->size=0;
	aux->stiva = (TStiva*)malloc(sizeof(TStiva)); /*se aloca stiva procesului */
	if(!aux->stiva) /* se verifica alocarea */
	{
		free(aux);
		return NULL;
	}
	aux->stiva->dim=sizeof(TStiva);
	aux->stiva->vf=NULL;
	return aux;
}

/* functie care verifica existenta pidului */
TLG find_pid(void *c, int pid)
{
	int ok=0;
	TLG aux, copie;
	TCoada *caux;
	caux = InitC(sizeof(TCoada));
	if(!caux) return NULL;
	while(VidaC(c) != 1)
	{
		aux = ExtrQ(c);
		if(((Proces*)aux->info)->pid == pid)
		{
			copie=aux;
			ok=1;
		}
		caux = IntrQ(caux, (Proces*)aux->info);
	}
	c = ConcatQ(c, caux);
	if(ok==0) return NULL;
	return copie;
}

/* functie care cauta pid-ul disponibil */
int find_free_pid(void *c)
{
	int k=0, copie=k;
	TLG aux;
	TCoada *caux;
	caux=InitC(sizeof(TCoada));
	if(!caux) return 0;
	while(VidaC(c)!=1)
	{
		aux=ExtrQ(c);
		k++;
		if(((Proces*)aux->info)->pid==0)
		{
			copie=k;
		}
		caux=IntrQ(caux,(Proces*)aux->info);
	}
	c=ConcatQ(c,caux);
	c=pid_sort(c);

	return copie;
}

/* functie care cauta memoria disponibila */
int find_free_memory(void *c)
{
	int k=0, copie=k;
	TLG aux;
	TCoada *caux;
	caux=InitC(sizeof(TCoada));
	if(!caux) return 0;
	while(VidaC(c)!=1)
	{
		aux=ExtrQ(c);
		k++;
		if(((Proces*)aux->info)->size==0)
		{
			copie=k;
		}
		caux=IntrQ(caux,(Proces*)aux->info);
	}
	c=ConcatQ(c,caux);
	c=pid_sort(c);

	return copie;
}

/* functie care calculeaza pid-ul min */
int pid_min(void *c, int n)
{
	TLG aux;
	int minim, i=2;
	void *caux;
	caux = InitC(sizeof(TCoada));
	if(!caux) return 0;
	aux = ExtrQ(c);
	caux = IntrQ(caux, (Proces*)aux->info);
	minim = ((Proces*)aux->info)->pid;

	while(i<=n)
	{
		aux = ExtrQ(c);
		caux = IntrQ(caux, (Proces*)aux->info);
		if(((Proces*)aux->info)->pid< minim)
			{minim = ((Proces*)aux->info)->pid;}
		i++;
	}
	while(VidaC(c)!=1)
	{
		aux = ExtrQ(c);
		caux = IntrQ(caux, (Proces*)aux->info);
	}
	c = ConcatQ(c, caux);
	return minim;
}

/* functie care sorteaza coada crescator dupa pid */
void *pid_sort(void *c)
{
	TLG aux, copie;
	int min, n=NrElQ(c), i=n;
	void *caux;
	caux = InitC(sizeof(TCoada));
	if(!caux) return NULL;
	while(i>=1)
	{
		min = pid_min(c, i);
		while(VidaC(c)!=1)
		{
			aux = ExtrQ(c);
			if(min != ((Proces*)aux->info)->pid)
			{
				caux = IntrQ(caux, (Proces*)aux->info);		
			}
			else
			{
				copie=aux;
			}
		}
		caux = IntrQ(caux, (Proces*)copie->info);

		c = ConcatQ(c, caux);
		caux=InitC(sizeof(TCoada));
		if(!caux) return NULL;
		i--;
	}
	return (void*)c;
}

/* functie care calculeaza timpul minim de executie*/
int time_min(void *c, int n)
{
	TLG aux;
	int minim, i=2;
	void *caux;
	caux = InitC(sizeof(TCoada));
	if(!caux) return 0;
	aux = ExtrQ(c);
	caux = IntrQ(caux, (Proces*)aux->info);
	minim = ((Proces*)aux->info)->time;

	while(i<=n)
	{
		aux = ExtrQ(c);
		caux = IntrQ(caux, (Proces*)aux->info);
		if(((Proces*)aux->info)->time < minim)
			{minim = ((Proces*)aux->info)->time;}
		i++;
	}
	while(VidaC(c)!=1)
	{
		aux = ExtrQ(c);
		caux = IntrQ(caux, (Proces*)aux->info);
	}
	c = ConcatQ(c, caux);
	return minim;
}

/* functie care sorteaza coada crescator dupa timpul de executie */
void *time_sort(void *c)
{
	TLG aux;
	int min, n=NrElQ(c), i=n, k, j;
	void *caux, *caux1;
	caux = InitC(sizeof(TCoada));
	if(!caux) return NULL;
	caux1=InitC(sizeof(TCoada));
	if(!caux1) return NULL;

	while(i>=1)
	{
		k=0;
		min = time_min(c, i);
		while(VidaC(c)!=1)
		{
			aux = ExtrQ(c);
			if(min != ((Proces*)aux->info)->time)
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
		/* se sorteaza coada dupa pid */
		caux1=pid_sort(caux1);
		while(j>=1)
		{
			aux=ExtrQ(caux1);
			caux=IntrQ(caux, (Proces*)aux->info);
			j--;
		}
		c = ConcatQ(c, caux);
		caux=InitC(sizeof(TCoada));
		if(!caux) return NULL;
		caux1=InitC(sizeof(TCoada));
		if(!caux1) return NULL;
		i=i-k;
	}
	c = RastoarnaC(c);

	return (void*)c;
}

/* functie care calculeaza prioritatea minima */
int priority_min(void *c, int n)
{
	TLG aux;
	int minim, i=2;
	void *caux;
	caux = InitC(sizeof(TCoada));
	if(!caux) return 0;
	aux = ExtrQ(c);
	caux = IntrQ(caux, (Proces*)aux->info);
	minim = ((Proces*)aux->info)->priority;

	while(i<=n)
	{
		aux = ExtrQ(c);
		caux = IntrQ(caux, (Proces*)aux->info);
		if(((Proces*)aux->info)->priority< minim)
			{minim = ((Proces*)aux->info)->priority;}
		i++;
	}
	while(VidaC(c)!=1)
	{
		aux = ExtrQ(c);
		caux = IntrQ(caux, (Proces*)aux->info);
	}
	c = ConcatQ(c, caux);
	return minim;
}