/* NUME: CHIRILA ALBERT, GRUPA:314CB */

#include "tema1.h"

History *AlocCelulaH()          
{ 
	History* aux = (History*)malloc(sizeof(History)); /*se incearca alocarea */
  	if (!aux) return NULL; 	/* verifica alocare */ 
  	strcpy(aux->info, "\0");               
  	aux->urm=NULL;					
  	return aux;
}

LSC *AlocCelulaLSC(void)
{
	LSC *aux = (LSC*)calloc(1, sizeof(LSC));	 /* se incearca alocarea */
	if(!aux) return NULL;	/* verifica alocare */ 
	aux->info_card = (CARD*) calloc(1, sizeof(CARD)); /* se incearca alocarea */
	if(!aux->info_card) /* verifica alocare */ 
	{
		free(aux);
		return NULL;
	}
	aux->info_card->hinfo=NULL;
	aux->urm=NULL;
	return aux;
}

LC *AlocCelulaLC(void)
{
	LC *aux = (LC*) malloc(sizeof(LC));	 /* se incearca alocarea */
	if(!aux) return NULL;	/* verifica alocare */ 
	aux->info=NULL;
	aux->urm=NULL;
	return aux;
}

int Inserare_InceputH(History **aL)
{
	History *aux = AlocCelulaH();	 /* se incearca alocarea */
	if(!aux) return 0;	/* verifica alocare */ 
	aux->urm = *aL;
	*aL = aux;
	return 1;
}



int Verificare(LC *L, char *x) /* functie care verifica 
							existenta unui card in baza de date */
{	
	for(;L!=NULL;L=L->urm)
	{
		LSC *p=L->info;
		for(;p!=NULL;p=p->urm)
		{
			if(strcmp(p->info_card->cn , x) == 0)
				return 1;
		}
	}
	return 0;
}

int cardinal(LC *L) /* functie care calculeaza lungimea listei LC */
{
	int k=0;
	for(;L!=NULL;L=L->urm)
	{
		k++;
	}
	return k;
}

int afisare(LC *L) /* functie care afiseaza informatiile
						 despre toate cardurile existente */
{
	
	LC *y=L;
	int i, k=cardinal(L);
	FILE *output_file = fopen("output.out", "at");
	for(i=0;i<k;i++)
	{
		fprintf(output_file, "pos%d: [", i);
		if(y)
		{
			LSC *p=y->info;
			for(;p!=NULL;p=p->urm)
			{
				fprintf(output_file, "\n(");
				fprintf(output_file, "card number: %s, ", p->info_card->cn);
				fprintf(output_file, "PIN: %s, ", p->info_card->pin);
				fprintf(output_file, "expiry date: %s, ", p->info_card->date);
				fprintf(output_file, "CVV: %s, ", p->info_card->cvv);
				fprintf(output_file, "balance: %d, ", p->info_card->sold);
				fprintf(output_file, "status: %s, ", p->info_card->status);
				fprintf(output_file, "history: [");

				History *q = p->info_card->hinfo;
				for(;q!=NULL;q=q->urm)
				{
					if(q->urm!=NULL)
					{
						fprintf(output_file, "(%s), ", q->info);
					}	
					else
					{
						fprintf(output_file, "(%s)", q->info);
					}
				}

				if(p->urm != NULL)
				{
					fprintf(output_file, "])");
				}
				else
				{
					fprintf(output_file, "])\n");
				}
			}
			fprintf(output_file, "]\n");
		}
		y=y->urm;	
	}
	fclose(output_file);
	
	return 0;
}


