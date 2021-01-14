/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include "tema2.h"

/* functie care adauga un proces */
int add(void *c, void *cw, void *cr,void *cp, void *cm, int *size, int *time, int priority, FILE *f, int *total, int *S)
{
	TLG aux;
	TCoada *caux, *caux1;
	caux=InitC(sizeof(TCoada));
	if(!caux) return 0;
	caux1=InitC(sizeof(TCoada));
	if(!caux1) return 0;

	/* se verifica daca inainte de adaugare procesul ar avea loc */
	(*S) += (*size);
	if((*S)>(*total))
	{
		fprintf(f, "Cannot reserve memory for PID %d.\n",
		 ((Proces*)(((TCoada*)cp)->sc->info))->pid +1);
		fclose(f);
		(*S) -= (*size);
		return 0;
	}
	(*S) -= (*size);

	int x=find_free_pid(cp);

	Proces *p;
	p = AlocProces(); /* se aloca procesul cu informatiile de mai jos */
		p->priority=priority;
		p->time=*time;
		p->size=*size;
		p->exec_time=*time; //copie pt afisare
		p->copy_size=*size; //copie pt marime
		p->mem=0;

	if(VidaC(c)==1)
	{
		p->pid=1;
		c=IntrQ(c,p);
		cr=IntrQ(cr,p);
		cp=IntrQ(cp,p);
		cm=IntrQ(cm,p);
		fprintf(f, "Process created successfully: PID: %d, Memory starts at 0x%x.\n", p->pid, p->mem);
		fclose(f);
		(*S) += (*size);
		return 1;
	}


	if(x==0) //pid indisponibil
	{
		int y=find_free_memory(cm);
		if(y==0) //memorie indisponibila
		{
			p->pid = ((Proces*)(((TCoada*)cp)->sc->info))->pid + 1;
			p->mem = ((Proces*)(((TCoada*)c)->sc->info))->mem + 
			((Proces*)(((TCoada*)c)->sc->info))->size;
			c=IntrQ(c,p);
			cw=IntrQ(cw,p);
			cp=IntrQ(cp,p);
			cm=IntrQ(cm,p);
			(*S) += (*size);
			fprintf(f, "Process created successfully: PID: %d, Memory starts at 0x%x.\n", p->pid, p->mem);
			fclose(f);
			return 1;
		}
		if(y!=0) //memorie disponibila
		{
			while((y-1)>0)
			{
				aux=ExtrQ(c);
				caux=IntrQ(caux,(Proces*)aux->info);
				y--;
			}

			aux=ExtrQ(c);
			if((*size) < ((Proces*)aux->info)->copy_size)
			{
				p->pid=((Proces*)(((TCoada*)cp)->sc->info))->pid + 1;
				p->mem = ((Proces*)aux->info)->mem;
				cp=IntrQ(cp,p);
				caux=IntrQ(caux,p);
				cw=IntrQ(cw,p);
				while(VidaC(c)!=1)
				{
					aux=ExtrQ(c);
					caux=IntrQ(caux, (Proces*)aux->info);
				}
				c=ConcatQ(c,caux);
				fprintf(f, "Process created successfully: PID: %d, Memory starts at 0x%x.\n", p->pid, p->mem);
				fclose(f);
				(*S) -= (*size);
				while(VidaC(cm)!=1)
				{
					aux=ExtrQ(cm);
					if(((Proces*)aux->info)->size == 0)
					{
						((Proces*)aux->info)->size = (*size);
					}
					caux1=IntrQ(caux1, (Proces*)aux->info);
				}
				cm=ConcatQ(cm,caux1); //memoria devine indisponibila
				return 1;
			}
			else
			{
				p->pid=((Proces*)(((TCoada*)cp)->sc->info))->pid + 1;
				p->mem = ((Proces*)(((TCoada*)c)->sc->info))->mem + 
				((Proces*)(((TCoada*)c)->sc->info))->size;
				c=IntrQ(c,p);
				cm=IntrQ(cm,p);
				cp=IntrQ(cp,p);
				fprintf(f, "Process created successfully: PID: %d, Memory starts at 0x%x.\n", p->pid, p->mem);
				fclose(f);
				(*S) += (*size);
				return 1;
			}

		}
	}

	if(x!=0) //pid disponibil
	{
		int y=find_free_memory(cm);
		int copie=x;
		while(VidaC(cp)!=1)
		{
			aux=ExtrQ(cp);
			if(((Proces*)aux->info)->pid == 0)
			{
				((Proces*)aux->info)->pid = copie;
			}
			caux1=IntrQ(caux1, (Proces*)aux->info);
		}
		cp=ConcatQ(cp,caux1); //pidul devine indisponibil


		if(y!=0) //memorie disponibila
		{
			while((y-1)>0)
			{
				aux=ExtrQ(c);
				caux=IntrQ(caux,(Proces*)aux->info);
				y--;
			}
			aux=ExtrQ(c);
			if((*size) < ((Proces*)aux->info)->copy_size)
			{
				p->pid=copie;
				p->mem = ((Proces*)aux->info)->mem;
				caux=IntrQ(caux,p);
				cw=IntrQ(cw,p);
				while(VidaC(c)!=1)
				{
					aux=ExtrQ(c);
					caux=IntrQ(caux, (Proces*)aux->info);
				}
				c=ConcatQ(c,caux);
				fprintf(f, "Process created successfully: PID: %d, Memory starts at 0x%x.\n", p->pid, p->mem);
				fclose(f);
				(*S) -= (*size);
				while(VidaC(cm)!=1)
				{
					aux=ExtrQ(cm);
					if(((Proces*)aux->info)->size == 0)
					{
						((Proces*)aux->info)->size = (*size);
					}
					caux1=IntrQ(caux1, (Proces*)aux->info);
				}
				cm=ConcatQ(cm,caux1); //memoria devine indisponibila
				return 1;
			}
			if((*size) > ((Proces*)aux->info)->copy_size)
			{
				caux=IntrQ(caux,(Proces*)aux->info);
				while(VidaC(c)!=1)
				{
					aux=ExtrQ(c);
					caux=IntrQ(caux,(Proces*)aux->info);
				}
				c=ConcatQ(c,caux);
				p->pid=copie;
				p->mem=((Proces*)(((TCoada*)c)->sc->info))->mem + 
				((Proces*)(((TCoada*)c)->sc->info))->size;
				c=IntrQ(c,p);
				cw=IntrQ(cw,p);
				fprintf(f, "Process created successfully: PID: %d, Memory starts at 0x%x.\n", p->pid, p->mem);
				fclose(f);
				(*S) += (*size);
				return 1;
			}
		}
	}
	return 0;
}

int run(void *cw, void *cf, void *cm , void *cr, void *cp, int exec_time, int *T)
{
	int x=*T;
	TLG aux, aux1, aux2;
	TCoada *caux1, *caux2;
	if(exec_time % x == 0)
	{
		int y=exec_time/x;
		if(y%2==0)
		{
			while(y)
			{
				if(VidaC(cw)==1)
				{
					aux=ExtrQ(cr);
					((Proces*)aux->info)->time -= x;
					cr=IntrQ(cr,(Proces*)aux->info);
					y--;				
				}
				if(VidaC(cw)!=1)
				{
					aux=ExtrQ(cr);
					((Proces*)aux->info)->time -= x;
					y--;
					if(((Proces*)aux->info)->time == 0)
					{
						caux1=InitC(sizeof(TCoada));
						if(!caux1) return 0;
						while(VidaC(cp)!=1)
						{
							aux1=ExtrQ(cp);
							if(((Proces*)aux->info)->pid == ((Proces*)aux1->info)->pid)
							{
								((Proces*)aux1->info)->pid =0;
							}
							caux1=IntrQ(caux1,(Proces*)aux1->info);
						}
						cp=ConcatQ(cp,caux1);

						caux2=InitC(sizeof(TCoada));
						if(!caux2) return 0;
						while(VidaC(cm)!=1)
						{
							aux2=ExtrQ(cm);
							if(((Proces*)aux->info)->pid == ((Proces*)aux2->info)->pid)
							{
								((Proces*)aux2->info)->size=0;
							}
							caux2=IntrQ(caux2,(Proces*)aux2->info);
						}
						cm=ConcatQ(cm,caux2);

						cf=IntrQ(cf,(Proces*)aux->info);
						aux1=ExtrQ(cw);
						cr=IntrQ(cr,(Proces*)aux1->info);
					}
					else
					{
						aux1=ExtrQ(cw);
						cw=IntrQ(cw,(Proces*)aux->info);
						cw=sort(cw);
						cr=IntrQ(cr,(Proces*)aux1->info);
					}
				}
			}	
		}

		if(y%2!=0)
		{
			y=y-1;
			while(y)
			{
				if(VidaC(cw)==1)
				{
					aux=ExtrQ(cr);
					((Proces*)aux->info)->time -= x;
					cr=IntrQ(cr,(Proces*)aux->info);
					y--;
					if(((Proces*)aux->info)->time == 0)
					{
						caux1=InitC(sizeof(TCoada));
						if(!caux1) return 0;
						while(VidaC(cp)!=1)
						{
							aux1=ExtrQ(cp);
							if(((Proces*)aux->info)->pid == ((Proces*)aux1->info)->pid)
							{
								((Proces*)aux1->info)->pid =0;
							}
							caux1=IntrQ(caux1,(Proces*)aux1->info);
						}
						cp=ConcatQ(cp,caux1);

						caux2=InitC(sizeof(TCoada));
						if(!caux2) return 0;
						while(VidaC(cm)!=1)
						{
							aux2=ExtrQ(cm);
							if(((Proces*)aux->info)->pid == ((Proces*)aux2->info)->pid)
							{
								((Proces*)aux2->info)->size=0;
							}
							caux2=IntrQ(caux2,(Proces*)aux2->info);
						}
						cm=ConcatQ(cm,caux2);

						cf=IntrQ(cf,(Proces*)aux->info);
						aux1=ExtrQ(cw);
						cr=IntrQ(cr,(Proces*)aux1->info);
					}				
				}
				if(VidaC(cw)!=1)
				{
					aux=ExtrQ(cr);
					((Proces*)aux->info)->time -= x;
					y--;
					if(((Proces*)aux->info)->time == 0)
					{
						caux1=InitC(sizeof(TCoada));
						if(!caux1) return 0;
						while(VidaC(cp)!=1)
						{
							aux1=ExtrQ(cp);
							if(((Proces*)aux->info)->pid == ((Proces*)aux1->info)->pid)
							{
								((Proces*)aux1->info)->pid =0;
							}
							caux1=IntrQ(caux1,(Proces*)aux1->info);
						}
						cp=ConcatQ(cp,caux1);

						caux2=InitC(sizeof(TCoada));
						if(!caux2) return 0;
						while(VidaC(cm)!=1)
						{
							aux2=ExtrQ(cm);
							if(((Proces*)aux->info)->pid == ((Proces*)aux2->info)->pid)
							{
								((Proces*)aux2->info)->size=0;
							}
							caux2=IntrQ(caux2,(Proces*)aux2->info);
						}
						cm=ConcatQ(cm,caux2);

						cf=IntrQ(cf,(Proces*)aux->info);
						aux1=ExtrQ(cw);
						cr=IntrQ(cr,(Proces*)aux1->info);
					}
					else
					{
						aux1=ExtrQ(cw);
						cw=IntrQ(cw,(Proces*)aux->info);
						cw=sort(cw);
						cr=IntrQ(cr,(Proces*)aux1->info);
					}
				}	
			}

			aux=ExtrQ(cr);
			((Proces*)aux->info)->time -= x;
			if(VidaC(cw)==1) return 1;
			if(((Proces*)aux->info)->time == 0)
			{
				caux1=InitC(sizeof(TCoada));
				if(!caux1) return 0;
				while(VidaC(cp)!=1)
					{
						aux1=ExtrQ(cp);
						if(((Proces*)aux->info)->pid == ((Proces*)aux1->info)->pid)
						{
							((Proces*)aux1->info)->pid =0;
						}
						caux1=IntrQ(caux1,(Proces*)aux1->info);
					}
					cp=ConcatQ(cp,caux1);
					cf=IntrQ(cf,(Proces*)aux->info);
					if(VidaC(cw)==1) return 1;
					aux1=ExtrQ(cw);
					cr=IntrQ(cr,(Proces*)aux1->info);
			}
			else
			{
				cw=IntrQ(cw, (Proces*)aux->info);
				aux1=ExtrQ(cw);
				cr=IntrQ(cr,(Proces*)aux1->info);
				cw=sort(cw);
			}
		}
	}


	return 1;
}

/* functie care afla starea unui proces */
int get(void *cr, void *cw, void *cf, int pid, FILE *f)
{
	TLG aux;
	int r=0;

	if((aux=find_pid(cw, pid)))
	{
		r=1;
		fprintf(f, "Process %d is waiting (remaining_time: %d).\n", pid, ((Proces*)aux->info)->time);
		fclose(f);
	}

	if((aux=find_pid(cr, pid)))
	{
		r=1;
		fprintf(f, "Process %d is running (remaining_time: %d).\n", pid, ((Proces*)aux->info)->time);
		fclose(f);
	}

	if((aux=find_pid(cf, pid)))
	{
		r=1;
		fprintf(f, "Process %d is finished.\n", pid);
		fclose(f);
	}

	if(r==0)
	{
		fprintf(f, "Process %d not found.\n", pid);
		fclose(f);
	}

	return 0;
}

/* functie care extrage din stiva 4 octeti */
void *pop_stiva(void *s, int pid, void *c,FILE *f)
{
	TLG aux, aux1;
	aux=find_pid(c,pid);
	if(aux==NULL)
	{
		fprintf(f, "PID %d not found.\n", pid);
		fclose(f);
		return (void*)s;
	}
	s = (TStiva*)(((Proces*)aux->info)->stiva);
	if(VidaS(s)==1)
	{
		fprintf(f,"Empty stack PID %d.\n", pid);
		fclose(f);
		return (void*)s;
	}
	aux1=Pop(s);
	free(aux1->info);
	free(aux1);
	return (void*)s;
}

/* functie care introduce in stiva 4 octeti */
void *push_stiva(void *s, int pid, int *nr, void *c, void *cm ,FILE *f)
{
	TLG aux, aux1;
	int y= find_free_memory(cm);
	if(y==pid) //proces terminat
	{
		fprintf(f,"PID %d not found.\n", pid);
		fclose(f);
		return NULL;
	}

	aux=find_pid(c,pid);
	if(aux==NULL)
	{
		fprintf(f,"PID %d not found.\n", pid);
		fclose(f);
		return NULL;
	}
	aux1=(TLG)malloc(sizeof(TCelula));
	if(!aux1) return NULL;
	aux1->info=malloc(sizeof(int));
	if(!aux1->info)
	{
		free(aux1);
		return NULL;
	} 
	s = (TStiva*)(((Proces*)aux->info)->stiva);
	memcpy(aux1->info, nr, sizeof(int));
	//introducerea in stiva
	if(VidaS(s)==1)
	{
		((TStiva*)s)->vf=aux1;
		aux1->urm=NULL;
		return (void*)s;
	}
	aux1->urm = ((TStiva*)s)->vf;
	((TStiva*)s)->vf = aux1;

	return (void*)s;
}

/* functie care afiseaza stiva unui proces */
void *print_stack(void *s, int pid, void *c, FILE *f)
{
	TLG aux, aux1;
	TStiva *saux;
	saux=InitS(sizeof(TStiva));
	if(!saux) return 0;
	aux=find_pid(c,pid);
	if(aux==NULL)
	{
		fprintf(f,"PID %d not found.\n", pid);
		fclose(f);
		return NULL;
	}
	s = (TStiva*)(((Proces*)aux->info)->stiva);
	if(VidaS(s)==1)
	{
		fprintf(f, "Empty stack PID %d.\n", pid);
		fclose(f);
		return NULL;
	}
	fprintf(f, "Stack of PID %d:", pid);
	/* se rastoarna stiva */
	s = RastoarnaS(s, sizeof(int));
	while(VidaS(s)!=1)
	{
		/* se face afisarea inversa a stivei */
		aux1=Pop(s);
		fprintf(f, " %d", *(int*)aux1->info);
		saux=Push(saux, (int*)aux1->info, sizeof(int));
	}
	fprintf(f, ".\n");
	fclose(f);
	/* se reface stiva */
	s = ConcatS(s, saux);
	
	return (void*)s;
}

/* functie care afiseaza coada proceselor aflate in asteptare */
void print_waiting(void *cw, FILE *f)
{
	TLG aux;
	TCoada *caux;
	caux=InitC(sizeof(TCoada));
	if(!caux) return;
	fprintf(f,"Waiting queue:\n");
	fprintf(f,"[");
	while(VidaC(cw)!=1)
	{
		aux = ExtrQ(cw);
		if(((TCoada*)cw)->ic==NULL)
		{
			fprintf(f,"(%d: priority = %d, remaining_time = %d)", 
				((Proces*)aux->info)->pid, ((Proces*)aux->info)->priority,
				 ((Proces*)aux->info)->time);
		}
		else
		{
			fprintf(f,"(%d: priority = %d, remaining_time = %d),\n", 
				((Proces*)aux->info)->pid, ((Proces*)aux->info)->priority, 
				((Proces*)aux->info)->time);
		}
		caux=IntrQ(caux, (Proces*)aux->info);
	}
	fprintf(f,"]\n");
	fclose(f);
	cw = ConcatQ(cw,caux);
}

/* functie care afiseaza coada proceselor terminate */
void print_finished(void *cf, FILE *f)
{
	TLG aux;
	TCoada *caux;
	caux=InitC(sizeof(TCoada));
	if(!caux) return;
	fprintf(f,"Finished queue:\n");
	fprintf(f,"[");
	while(VidaC(cf)!=1)
	{
		aux = ExtrQ(cf);
		if(((TCoada*)cf)->ic==NULL)
		{
			fprintf(f,"(%d: priority = %d, executed_time = %d)", 
				((Proces*)aux->info)->pid, ((Proces*)aux->info)->priority, 
				((Proces*)aux->info)->exec_time);
		}
		else
		{
			fprintf(f,"(%d: priority = %d, executed_time = %d),\n", 
				((Proces*)aux->info)->pid, ((Proces*)aux->info)->priority, 
				((Proces*)aux->info)->exec_time);
		}
		caux=IntrQ(caux, (Proces*)aux->info);
	}
	fprintf(f,"]\n");
	fclose(f);
	cf = ConcatQ(cf,caux);
}

/* functie care calculeaza timpul ramas pentru terminarea proceselor ramase */
int finish(void *cw, void *cr, FILE *f)
{
	TLG aux, aux1;
	int s=0;
	while(VidaC(cw)!=1)
	{
		aux=ExtrQ(cw);
		s += ((Proces*)aux->info)->time;
	}
	while(VidaC(cr)!=1)
	{
		aux1=ExtrQ(cr);
		s += ((Proces*)aux1->info)->time;
	}
	fprintf(f, "Total time: %d\n", s);
	fclose(f);
	return 0;
}

/* functie de distrugere */
int Distruge(void *c, void *cw, void *cf, void *cr)
{
	TLG aux, aux1;
	while(VidaC(cr)!=1)
	{
		aux=ExtrQ(cr);
		TStiva *s=((TStiva*)(((Proces*)aux->info)->stiva));
		while(VidaS(s)!=1)
		{
			aux1=Pop(s);
			free(aux1->info);
			free(aux1);
		}
		free(aux->info);
		free(aux);
	}

	free(cr);

	while(VidaC(cw)!=1)
	{
		aux=ExtrQ(cw);
		TStiva *s=((TStiva*)(((Proces*)aux->info)->stiva));
		while(VidaS(s)!=1)
		{
			aux1=Pop(s);
			free(aux1->info);
			free(aux1);
		}
		free(aux->info);
		free(aux);
	}
	free(cw);

	while(VidaC(c)!=1)
	{
		aux=ExtrQ(c);
		TStiva *s=((TStiva*)(((Proces*)aux->info)->stiva));
		while(VidaS(s)!=1)
		{
			aux1=Pop(s);
			free(aux1->info);
			free(aux1);
		}
		free(aux->info);
		free(aux);
	}
	free(c);

	while(VidaC(cf)!=1)
	{
		aux=ExtrQ(cf);
		TStiva *s=((TStiva*)(((Proces*)aux->info)->stiva));
		while(VidaS(s)!=1)
		{
			aux1=Pop(s);
			free(aux1->info);
			free(aux1);
		}
		free(aux->info);
		free(aux);
	}
	free(cf);
	return 1;
}

int main(int argc, char *argv[])
{ 
	int T, size=0, priority, time=0;
	int i, x;
	int total=3145728, S=0;
	TCoada *c, *cw, *cf, *cr, *cp, *cm;
	TStiva *s;
	int exec_time;

	c = InitC(sizeof(TCoada));
	if(!c) return 0;
	cw = InitC(sizeof(TCoada));
	if(!cw) return 0;
	cf = InitC(sizeof(TCoada));
	if(!cf) return 0;
	s = InitS(sizeof(TStiva));
	if(!s) return 0;
	cr=InitC(sizeof(TCoada));
	if(!cr) return 0;
	cp=InitC(sizeof(TCoada));
	if(!cp) return 0;
	cm=InitC(sizeof(TCoada));
	if(!cm) return 0;

	FILE *input_file = fopen(argv[1] , "r"); /* se deschide fisierul pentru citire */

	char *buf; 
	char original[10000][500]; /* matrice folosita pentru citirea fisierului */
	int original_line_count=0;	/* nr-ul de linii din fisierul de citire */

	buf = (char*) calloc(10000, sizeof(char));
	if(!buf) return 0;
	while (fgets(buf, 10000, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++; }

    fclose(input_file);

    T = atoi(original[0]);

    for(i=1;i<original_line_count;i++) /*parcurgere linie cu linie */
	{
		char *p;
		p=strtok(original[i]," "); /* se alege primul cuvant */
		int nr=strlen(original[i]);
		if(p[nr-1] == '\n')
		{
			p[nr-1] = '\0'; /* se elimina spatiul de la final */
		}
		if(strcmp(p, "add")==0)
		{
			char *q=p;
			q = strtok(NULL, " ");
			size =atoi(q);
			q = strtok(NULL, " ");
			time = atoi(q);
			q = strtok(NULL, " ");
			int nr = strlen(q);
			if(q[nr-1] == '\n')
			{
				q[nr-1] = '\0';
			}
			priority=atoi(q);
			FILE *output_file = fopen(argv[2], "at");
			add(c, cw,cr,cp,cm, &size, &time, priority, output_file, &total, &S);
			cw=sort(cw);
		}

		if(strcmp(p, "get")==0)
		{
			char *q=p;
			q = strtok(NULL, " ");
			int nr = strlen(q);
			if(q[nr-1] == '\n')
			{
				q[nr-1] = '\0';
			}
			x = atoi(q);
			FILE *output_file = fopen(argv[2], "at");
			get(cr, cw, cf, x, output_file);
		}

		if(strcmp(p, "print")==0)
		{
			char *q=p;
			q=strtok(NULL, " ");
			int nr = strlen(q);
			if(q[nr-1] == '\n')
			{
				q[nr-1] = '\0';
			}
			if(strcmp(q, "waiting")==0)
			{
				FILE *output_file = fopen(argv[2], "at");
				print_waiting(cw, output_file);
			}
			if(strcmp(q, "finished")==0)
			{
				FILE *output_file = fopen(argv[2], "at");
				print_finished(cf, output_file);
			}
			if(strcmp(q, "stack")==0)
			{
				char *z=q;
				z=strtok(NULL, " ");
				int nr = strlen(z);
				if(z[nr-1] == '\n')
				{
					z[nr-1] = '\0';
				}
				x=atoi(z);
				FILE *output_file = fopen(argv[2], "at");
				print_stack(s,x,c,output_file);
			}
		}

		if(strcmp(p, "pop")==0)
		{
			char *q=p;
			q=strtok(NULL, " ");
			int nr = strlen(q);
			if(q[nr-1] == '\n')
			{
				q[nr-1] = '\0';
			}
			x=atoi(q);
			FILE *output_file = fopen(argv[2], "at");
			s = pop_stiva(s,x,c,output_file);
		}

		if(strcmp(p, "push")==0)
		{
			char *q=p;
			q=strtok(NULL, " ");
			x = atoi(q);
			q=strtok(NULL, " ");
			int numar = strlen(q);
			if(q[numar-1] == '\n')
			{
				q[numar-1] = '\0';
			}
			nr=atoi(q);
			FILE *output_file = fopen(argv[2], "at");
			s = push_stiva(s,x,&nr,c,cm,output_file);
		}

		if(strcmp(p, "run")==0)
		{
			char *q=p;
			q=strtok(NULL, " ");
			int nr = strlen(q);
			if(q[nr-1] == '\n')
			{
				q[nr-1] = '\0';
			}
			exec_time=atoi(q);
			run(cw, cf, cm,cr, cp, exec_time, &T);
		}
		if(strcmp(p, "finish")==0)
		{
			int nr = strlen(p);
			if(p[nr-1] == '\n')
			{
				p[nr-1] = '\0';
			}
			FILE *output_file = fopen(argv[2], "at");
			finish(cw,cr,output_file);
		}

	}

	free(s);
	free(c);
	free(buf);
	Distruge(c,cw,cf,cr);
	return 0;
}
