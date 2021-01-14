/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct celula
{
	void *info;
	struct celula *urm;

}TCelula, *TLG, **ALG;

typedef struct stiva
{
	size_t dim;
	TLG vf;
}TStiva;

typedef struct proces
{
	int pid;
	int priority;
	int time;
	int size;
	int exec_time; //copie a lui time
	int copy_size; //copie a lui size
	int mem;
	TStiva *stiva;
}Proces;

typedef struct coada
{
	size_t dim;
	TLG ic,sc;
}TCoada;


/* functii coada: fisier fct_coada.c */
void *InitC(size_t d);
int VidaC(void *c);
TLG ExtrQ(void *c);
void *IntrQ(void *c, void *ae);
int NrElQ(void *c);
void *sort(void *c);
void *ConcatQ(void *c1, void *c2);
void *RastoarnaC(void *c);


/*functii ajutatoare: fisier fct_ajutor.c */
Proces *AlocProces();
int time_min(void *c, int n);
int pid_min(void *c, int n);
void *pid_sort(void *c);
void *time_sort(void *c);         
int priority_min(void *c, int n);
TLG find_pid(void *c, int pid);
int find_free_pid(void *c);
int find_free_memory(void *c);

/*functii stiva: fisier fct_stiva.c */
void *InitS(size_t d);
int VidaS(void *s);
void *Push(void *s, void *ae, size_t d);
TLG Pop(void *s);
int NrElS(void *s);
void *RastoarnaS(void *s, size_t d);
void *ConcatS(void *s1, void *s2);

