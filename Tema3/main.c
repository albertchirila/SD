/* NUME: CHIRILA ALBERT
   GRUPA: 314CB */

#include "tema3.h"

/* functie care creeaza un director */
int mkdir(TArb a, char *x, char *y)
{
	int i=0, j, k, k1=0, ok=0;
	char v[50];
	TArb arbore=a;

	if(x[0]=='/') i=1;
	int n=numara(x);

	/* in cazul unui exemplu /ana/are/mere
		se  cauta existenta directoarelor ana si ana/are */
	for(k=i;k<n;k++)
	{
		if(x[k]=='/')
		{
			ok=1;
			v[k1]='\0';
			int b = cautaArb(a,v);
			if(b==0)
			{
				FILE *error_file=fopen("error.out", "at");
				fprintf(error_file, "%s: No such file or directory\n",x);
				fclose(error_file);
				return 0;
			}
			v[k1]='/';
			k1++;
		}
		else
		{
			v[k1]=x[k];
			k1++;
		}
	}

	if(ok==1) arbore=muta(a,y);


	for(j=i;j<n;j++)
	{
		if(cautaL(arbore->p, x[i])==0)
		{
			arbore->p=Inserare(arbore->p, x[i]);
			TLista l=muta_pointer(arbore->p, x[i]);
			arbore=l->q;
			i++;
		}
		if(cautaL(arbore->p,x[i])!=0)
		{
			TLista l=muta_pointer(arbore->p,x[i]);
			arbore=l->q;
			i++;
		}
	}

	arbore->p=Inserare(arbore->p, '/');

	return 0;
}

/* functie care schimba directorul */
int cd(TArb a, char *x, TArb *arb, char *y, int *ok)
{
	/* trecere in directorul parinte */
	if(x[0]=='.' && x[1]=='.')
	{
		/* daca se afla in rot */
		if(strcmp(y, "/")==0)
		{
			FILE *error_file=fopen("error.out", "at");
			fprintf(error_file, "%s: No such file or directory\n",x);
			fclose(error_file);
			return -1;
		}
		int i;
		int n=strlen(y);
		/* se schimba sirul de carcatere y */
		for(i=n;i>=1;i--)
		{
			if(y[i]=='/') break;
			y[i]='\0';
		}
		return 0;
	}

	/* daca nu se gaseste directorul */
	if(cautaArb(a, x) == 0)
	{
		FILE *error_file=fopen("error.out", "at");
		fprintf(error_file, "%s: No such file or directory\n",x);
		fclose(error_file);
		return -1;
	}
	/* se construieste sirul de caractere y
		folosit in funtia pwd */
	strcat(y,x);
	*ok=1;
	return 1;
}

/* functie care afiseaza calea absoluta */
int pwd(char *x, int *ok)
{	
	/* daca nu s-a schimbat directorul */
	if(*ok==0)
	{
		FILE *out_file=fopen("output.out", "at");
		fprintf(out_file, "%s", "/\n");
		fclose(out_file);
		return 0;
	}
	/* se afiseaza caracterul x, obtinut din "cd" */
	FILE *out_file=fopen("output.out", "at");
	fprintf(out_file, "%s\n", x);
	fclose(out_file);
	return 1;
}

int main()
{

	TArb a=NULL;
	a=InitArbore('/');
	TArb arb=NULL;
	char *y=calloc(100,sizeof(char));
	if(!y) return 0;

	int ok=0;

	FILE *input_file = fopen("input.in" , "r"); /* se deschide fisierul pentru citire */

	char *buf; 
	char original[10000][500]; /* matrice folosita pentru citirea fisierului */
	int original_line_count=0, i;	/* nr-ul de linii din fisierul de citire */

	buf = (char*) calloc(10000, sizeof(char));
	if(!buf) return 0;
	while (fgets(buf, 10000, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++; }

    fclose(input_file);

    FILE *out_file=fopen("output.out", "at");
	fprintf(out_file, "\n");
	fclose(out_file);

    for(i=1;i<original_line_count;i++) /*parcurgere linie cu linie */
	{
		char *p;
		p=strtok(original[i]," "); /* se alege primul cuvant */
		int nr=strlen(original[i]);
		if(p[nr-1] == '\n')
		{
			p[nr-1] = '\0'; /* se elimina spatiul de la final */
		}
		if(strcmp(p, "mkdir")==0)
		{
			char *q=p;
			int nr=strlen(q);
			int k=1;
			if(q[nr+2]=='\0')
			{
				FILE *error_file=fopen("error.out", "at");
				fprintf(error_file, "mkdir: missing operand\n");
				fclose(error_file);
			}
			else
			{
				while(k)
				{
					q=strtok(NULL, " ");
					int nr1=strlen(q);
					if(q[nr1-1] == '\n')
					{
						q[nr1-1] = '\0'; /* se elimina spatiul de la final */
						k=0;
					}
					mkdir(a,q,y);
				}
			}
		}
		if(strcmp(p,"cd")==0)
		{
			char *q=p;
			q=strtok(NULL," ");
			int nr=strlen(q);
			if(q[nr-1] == '\n')
			{
				q[nr-1] = '\0'; /* se elimina spatiul de la final */
			}
			cd(a,q, &arb, y, &ok);
		}

		if(strcmp(p,"pwd")==0)
		{
			int nr=strlen(p);
			if(p[nr-1] == '\n')
			{
				p[nr-1] = '\0'; /* se elimina spatiul de la final */
			}
			pwd(y, &ok);
		}
	}
	free(buf);
	free(y);

	return 0;
}