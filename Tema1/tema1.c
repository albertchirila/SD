/* NUME: CHIRILA ALBERT, GRUPA:314CB */

#include "tema1.h"
#include <stdlib.h>

LC *add_card(LC *L, char *cn,  char *date, char *pin, char *cvv, int nmc)  
/* functie de adaugare card */
{
 	LC *p=L, *q=L, *cp, *cL=L;
 	LC *y=L;						
 	LSC  *b;
 	int poz, s=0, k, i, j, k1;
 	k = cardinal(L);
 	
 	FILE *output_file=fopen("output.out", "at");  /* deschidere fisier 
 													pentru scriere */
 	if(Verificare(cL, cn) == 1)			/* verifica daca un card exista 
 											deja in baza de date */
 	{
 		fprintf(output_file, "The card already exists\n");
 		fclose(output_file);	
 		return cL;
 	}
 	for(j=0; j<strlen(cn); j++)		/* se calculeaza suma cifrelor cardului */
 	{
 		k1 = cn[j] - '0';		
 		s += k1;
 	}
 	poz = s % nmc;	/* se calculeaza pozitia pe care se va insera cardul */

 	if(p==NULL)
 	{
 		if(poz > k)
 		{
 			p=AlocCelulaLC();	/* se aloca celula LC */
 			if(!p) return NULL;		/* verificare alocare celula */
 			L=p;
 			cp=p;
 			p=p->urm;
 			k++;
 			for(i=1;i<=poz;i++)
 			{
 				p = AlocCelulaLC();		/* se aloca celula LC */
 				if(!p) return NULL;		/* verificare alocare celula */
 				cp->urm=p;
 				p=p->urm;
 				cp=cp->urm;
 				k++;
 			}
 			b=cp->info;
 			b =AlocCelulaLSC();		/* se aloca celula LSC */
 			if(!b) return NULL;		/* verificare alocare celula */
 			b->urm=cp->info;
 			cp->info=b;
			b->info_card->cn = calloc(18 ,sizeof(char));	/* se introduce
												 informatia in celula LSC */
 			strcpy(b->info_card->cn, cn);
 			b->info_card->pin = calloc(6 ,sizeof(char));
 			strcpy(b->info_card->pin, pin);
 			b->info_card->date = calloc(6 ,sizeof(char));
 			strcpy(b->info_card->date, date);
 			b->info_card->status = calloc(10 ,sizeof(char));
 			strcpy(b->info_card->status, "NEW");
 			b->info_card->cvv = calloc(4 ,sizeof(char));
 			strcpy(b->info_card->cvv, cvv);
 			b->info_card->sold = 0;
 		}

 		else
 		{
 			p = AlocCelulaLC();		/* se aloca celula LC */
 			if(!p) return NULL;		/* verificare alocare celula */
 			L=p;
 			k++;
 			LSC *t=p->info;
 			t = AlocCelulaLSC();	/* se aloca celula LSC */
 			if(!t) return NULL;		/* verificare alocare celula */
 			t->urm=p->info;
 			p->info=t;
 			t->info_card->cn = calloc(18 ,sizeof(char));	/* se introduce
 												 informatia in celula LSC */
 			strcpy(t->info_card->cn, cn);
 			t->info_card->pin = calloc(6 ,sizeof(char));
 			strcpy(t->info_card->pin, pin);
 			t->info_card->date = calloc(6 ,sizeof(char));
 			strcpy(t->info_card->date, date);
 			t->info_card->status = calloc(10 ,sizeof(char));
 			strcpy(t->info_card->status, "NEW");
 			t->info_card->cvv = calloc(4 ,sizeof(char));
 			strcpy(t->info_card->cvv, cvv);
 			t->info_card->sold = 0;

		}
 		return L;
	} 

 	y=L;
 	if(poz < k)
 	{
 		for(i=0; i<poz;i++) y=y->urm;
 		
 		LSC *cy=y->info;
 		cy = AlocCelulaLSC();	/* se aloca celula LSC */
 		if(!cy) return NULL;	/* verificare alocare celula */
 		cy->urm=y->info;
 		y->info=cy;
 		cy->info_card->cn = calloc(18 ,sizeof(char));	/* se introduce
 												 informatia in celula LSC */
 		strcpy(cy->info_card->cn, cn);
 		cy->info_card->pin = calloc(6 ,sizeof(char));
 		strcpy(cy->info_card->pin, pin);
 		cy->info_card->date = calloc(6 ,sizeof(char));
 		strcpy(cy->info_card->date, date);
 		cy->info_card->status = calloc(10 ,sizeof(char));
 		strcpy(cy->info_card->status, "NEW");
 		cy->info_card->cvv = calloc(4 ,sizeof(char));
 		strcpy(cy->info_card->cvv, cvv);
 		cy->info_card->sold = 0;
 		return L;
	}
 	
 	q = L;
 	while(q->urm!=NULL) q =q->urm;

 	LC *a=q;
 	if(poz > k)
 	{
		for(i=k;i<=poz;i++)
 		{
 			q->urm = AlocCelulaLC();	/* se aloca celula LC */
 			if(!q->urm) return NULL;	/* verificare alocare celula */
 			q=q->urm;
 			a->urm=q;
 			a=a->urm;
 			k++;
 		}
 		LSC *z = q->info;
 		z = AlocCelulaLSC();	/* se aloca celula LSC */
 		if(!z) return NULL;		/* verificare alocare celula */
 		z->urm=q->info;
 		q->info=z;
		z->info_card->cn = calloc(18 ,sizeof(char));	/* se introduce
												 informatia in celula LSC */
 		strcpy(z->info_card->cn, cn);
 		z->info_card->pin = calloc(6 ,sizeof(char));
 		strcpy(z->info_card->pin, pin);
 		z->info_card->date = calloc(6 ,sizeof(char));
 		strcpy(z->info_card->date, date);
 		z->info_card->status = calloc(10 ,sizeof(char));
 		strcpy(z->info_card->status, "NEW");
 		z->info_card->cvv = calloc(4 ,sizeof(char));
 		strcpy(z->info_card->cvv, cvv);
 		z->info_card->sold = 0;
		return L;
	}

 	if(poz == k)
 	{
 		q->urm = AlocCelulaLC();	/* se aloca celula LC */
 		if(!q->urm) return NULL;
 		q = q->urm;
 		a->urm=q;
 		a=a->urm;
 		k++;
 		LSC *z = q->info;
 		z = AlocCelulaLSC();	/* se aloca celula LSC */
 		if(!z) return NULL;		/* verificare alocare celula */
 		z->urm=q->info;
 		q->info=z;
 		z->info_card->cn = calloc(18 ,sizeof(char));	/* se introduce 
 												informatia in celula LSC */
 		strcpy(z->info_card->cn, cn);
 		z->info_card->pin = calloc(6 ,sizeof(char));
 		strcpy(z->info_card->pin, pin);
 		z->info_card->date = calloc(6 ,sizeof(char));
		strcpy(z->info_card->date, date);
		z->info_card->status = calloc(10 ,sizeof(char));
 		strcpy(z->info_card->status, "NEW");
 		z->info_card->cvv = calloc(4 ,sizeof(char));
 		strcpy(z->info_card->cvv, cvv);
 		z->info_card->sold = 0;				
		return L;
	}
	return L;	/* se returneaza mereu capul listei */
}

int delete_card(LC *L, char *x, int *k1, int*k3) /* functie care sterge 
													cardul din baza de date */
{
	*k1=0;	
	LC *y=L;	/* copie pentru a nu pierde capul listei */
	for(;y!=NULL;y=y->urm)	/* parcurgere lista */
	{
		LSC *p=y->info, *ant;
		for(ant=NULL;p!=NULL;ant=p, p=p->urm)
		{
			if(strcmp(p->info_card->cn , x) == 0)	/* se gaseste cardul care
													 va urma a fi eliminat */
			{
				if(ant == NULL) y->info=p->urm;	/* se elimina cardul din 
														baza de date */
				else ant->urm = p->urm;
				free(p);
				(*k1)++;
				*k3=0;
				return 1;			
			}
		}
	}
	return 0;
}

 int pin_change(LC *L, char *x, char *new_pin, int *k4, int *k2) /*functie care
 													schimba pinul unui card */
 {
 	int k=0,ok=0, i;
 	*k4=0;
 	LC *y=L;
 	for(i=0;i<strlen(new_pin);i++)	/* se calculeaza lungimea pinului */
 	{
 		k++;
 		if(new_pin[i] >= 65)	/* se verifica daca acesta contine litere */
 		{
 			ok=1;
 		}
 	}

 	if(k==4 && ok == 0)	 /* daca pinul are lungimea corecta
 							 si nu contine alte caractere */
 	{
 		for(;y!=NULL;y=y->urm)	/* se parcurge lista */
 		{
 			LSC *p = y->info;
 			for(;p!=NULL;p=p->urm)
 			{
 				if(strcmp(p->info_card->cn , x) == 0)	/* se gaseste 
 													cardul in baza de date */
 				{	
 					(*k4)++;
 					if(*k4 == *k2)	/* daca s-a schimbat pinul si se realizeaza
 										 inserarea se actualizeaza statusul */
 					{	
 						strcpy(p->info_card->status, "ACTIVE");
 					}
 					strcpy(p->info_card->pin, new_pin); /* se realizeaza 
 													schimbarea pinului */
 					History *q=p->info_card->hinfo;
					q=AlocCelulaH();	/* se aloca celula History */
					if(!q) return 0;	/* se verifica alocarea celulei */
					q->urm=p->info_card->hinfo;
					p->info_card->hinfo =q;
					sprintf(q->info, "%s, %s %s %s", "SUCCESS", "pin_change",
					p->info_card->cn, p->info_card->pin);	/* se introduce 
											operatia in istoricul cardului */
 					return 1;
 				}
 			}
 		}
 	}

 	else	/* daca pinul nu are lungimea corecta sau contine alte caractere */
 	{
 		FILE *output_file=fopen("output.out", "at");
 		fprintf(output_file, "Invalid PIN\n");	/* se afiseaza informatia
 													 in fisierul output */
 		fclose(output_file);
 		*k4 = 0;
 		LC *t=L;
		for(;t!=NULL;t=t->urm)	/* se parcurge lista */
		{
			LSC *h=t->info;
			for(;h!=NULL; h=h->urm)
			{
				if(strcmp(h->info_card->cn ,x) == 0)	/* se gaseste cardul 
															in baza de date */
				{
					History *z=h->info_card->hinfo;
					z=AlocCelulaH();	/* se aloca celula H */
					if(!z) return 0;	/* se verifica alocarea celulei */
					z->urm=h->info_card->hinfo;
					h->info_card->hinfo =z;
					sprintf(z->info, "%s, %s %s %s", "FAIL", "pin_change",
					 h->info_card->cn, new_pin);	/* se adauga operatia
					 							 in istoricul cardului */
					return 0;
				}
			}
		}
 	}
 	return 0;
}

int recharge(LC *L, char *x, int suma)	/* functie care adauga numerarul pe card*/
{
	LC *y=L;

	if(suma % 10 != 0)	/* se verifica daca suma este multiplu de 10 */
	{	
		FILE *output_file=fopen("output.out", "at");
		fprintf(output_file, "The added amount must be multiple of 10\n");
		fclose(output_file);
		LC *t=L;
		for(;t!=NULL;t=t->urm)
		{
			LSC *h=t->info;
			for(;h!=NULL; h=h->urm)
			{
				if(strcmp(h->info_card->cn, x) == 0)	/* se gaseste cardul */
				{
					History *z=h->info_card->hinfo;
					z=AlocCelulaH();	/* se aloca celula H */
					if(!z) return 0;	/* se verifica alocarea celulei */
					z->urm=h->info_card->hinfo;
					h->info_card->hinfo =z;
					sprintf(z->info, "%s, %s %s %d", "FAIL", "recharge",
					h->info_card->cn, suma);	/* se introduce operatia 
												in istoricul cardului */
					return 0;
				}
			}
		}
	}

	for(;y!=NULL;y=y->urm)
	{
		LSC *p=y->info;
		for(;p!=NULL;p=p->urm)
		{
			if(strcmp(p->info_card->cn, x) == 0)
			{
				p->info_card->sold = p->info_card->sold + suma;
				FILE *output_file=fopen("output.out", "at");
				fprintf(output_file, "%d\n", p->info_card->sold);
				fclose(output_file);
				History *q=p->info_card->hinfo;
				q=AlocCelulaH();	/* se aloca celula H */
				if(!q) return 0;	/* se verifica alocarea celulei */
				q->urm=p->info_card->hinfo;
				p->info_card->hinfo =q;
				sprintf(q->info, "%s, %s %s %d", "SUCCESS", "recharge",
				p->info_card->cn, suma);	/* se introduce operatia
											 in istoricul cardului */
				return 1;
			}
		}
	}
	return 0;
}

int balance_inquiry(LC *L, char *x)	/* functie care afiseaza soldul curect */
{
	LC *y=L;

	for(;y!=NULL;y=y->urm)	/* parcurgere lista */
	{
		LSC *p=y->info;
		for(;p!=NULL;p=p->urm)
		{
			if(strcmp(p->info_card->cn ,x) == 0)
			{
				FILE *output_file=fopen("output.out", "at");
				fprintf(output_file, "%d\n", p->info_card->sold);	
										/* afisare soldul curect */
				fclose(output_file);
				History *q=p->info_card->hinfo;
				q=AlocCelulaH();	/* se aloca celula H */
				if(!q) return 0;	/* se verifica alocarea celulei */
				q->urm=p->info_card->hinfo;
				p->info_card->hinfo =q;
				sprintf(q->info, "%s, %s %s", "SUCCESS", "balance_inquiry",
				p->info_card->cn);	/* se introduce operatia 
										in istoricul cardului */
				return 1;
			}
		}
	}

	return 0;
}

int cash_withdrawal(LC *L, char *x, int suma) /* functie care extrage 
												numerarul de pe card */
{
	LC *y=L;
	if(suma % 10 != 0)	/* se verifica daca suma esre multiplu de 10 */
	{
		FILE *output_file=fopen("output.out", "at");
		fprintf(output_file, "The requested amount must be multiple of 10\n");
		fclose(output_file);
		LC *t=L;
		for(;t!=NULL;t=t->urm) /* parcurgere lista */
		{
			LSC *h=t->info;
			for(;h!=NULL; h=h->urm)
			{
				if(strcmp(h->info_card->cn , x) == 0)
				{
					History *z=h->info_card->hinfo;
					z=AlocCelulaH();	/* se aloca celula H */
					if(!z) return 0;	/* se verifica alocarea celulei */
					z->urm=h->info_card->hinfo;
					h->info_card->hinfo =z;
					sprintf(z->info, "%s, %s %s %d", "FAIL", "cash_withdrawal",
					h->info_card->cn, suma);	/* se introduce operatia 
												in istoricul cardului */
					return 0;
				}
			}
		}
	}

	for(;y!=NULL;y=y->urm)
	{
		LSC *p=y->info;
		for(;p!=NULL;p=p->urm)
		{
			if(strcmp(p->info_card->cn , x) == 0)
			{
				if(p->info_card->sold < suma)
				{
					FILE *output_file=fopen("output.out", "at");
					fprintf(output_file, "Insufficient funds\n");
					fclose(output_file);
					History *q=p->info_card->hinfo;
					q=AlocCelulaH();	/* se aloca celula H */
					if(!q) return 0;	/* se verifica alocarea celulei */
					q->urm=p->info_card->hinfo;
					p->info_card->hinfo =q;
					sprintf(q->info, "%s, %s %s %d", "FAIL", "cash_withdrawal",
					p->info_card->cn, suma);	/* se introduce operatia 
												in istoricul cardului */
					return 0;
				}
				else
				{
					p->info_card->sold = p->info_card->sold - suma;
					FILE *output_file=fopen("output.out", "at");
					fprintf(output_file, "%d\n", p->info_card->sold);
					fclose(output_file);
					History *q=p->info_card->hinfo;
					q=AlocCelulaH();	/* se aloca celula H */
					if(!q) return 0;	/* se verifica alocarea celulei */
					q->urm=p->info_card->hinfo;
					p->info_card->hinfo =q;
					sprintf(q->info, "%s, %s %s %d", "SUCCESS", "cash_withdrawal",
					p->info_card->cn, suma);	/* se introduce operatia 
												in istoricul cardului */
					return 1;
				}
			}
		}
	}
	return 0;
}


int transfer_funds(LC *L, char *a, char *b, int suma) 
						/* functie care transfera bani */
{
	if(suma % 10 != 0)	/* se verifica daca suma esre multiplu de 10 */
	{
		FILE *output_file=fopen("output.out", "at");
		fprintf(output_file, "The transferred amount must be multiple of 10\n");
		fclose(output_file);
		LC *t=L;
		for(;t!=NULL;t=t->urm)
		{
			LSC *h=t->info;
			for(;h!=NULL; h=h->urm)
			{
				if(strcmp(h->info_card->cn ,a) == 0)
				{				
					History *z=h->info_card->hinfo;
					z=AlocCelulaH();	/* se aloca celula H */
					if(!z) return 0;	/* se verifica alocarea celulei */
					z->urm=h->info_card->hinfo;
					h->info_card->hinfo =z;
					sprintf(z->info, "%s, %s %s %s %d", "FAIL",
					"transfer_funds", a, b, suma);	/* se introduce operatia 
													in istoricul cardului */
					return 0;
				}
			}

		}
	}

	LC *y=L;
	for(;y!=NULL;y=y->urm)
	{
		LSC *p=y->info;
		for(;p!=NULL; p=p->urm)
		{
			if(strcmp(p->info_card->cn, a) == 0)
			{
				if(p->info_card->sold < suma) /* se verifica daca cardul sursa 
													are suficienti bani */
				{
					FILE *output_file=fopen("output.out", "at");
					fprintf(output_file, "Insufficient funds\n");
					fclose(output_file);
					History *q=p->info_card->hinfo;
					q=AlocCelulaH();	/* se aloca celula H */
					if(!q) return 0;	/* se verifica alocarea celulei */
					q->urm=p->info_card->hinfo;
					p->info_card->hinfo =q;
					sprintf(q->info, "%s, %s %s %s %d", "FAIL", 
					"transfer_funds", a, b, suma);	/* se introduce operatia
													 in istoricul cardului */
					return 0;
				}

				else 
				{
					p->info_card->sold = p->info_card->sold - suma;
					FILE *output_file=fopen("output.out", "at");
					fprintf(output_file, "%d\n", p->info_card->sold); 
										/* se afiseaza suma */
					fclose(output_file);
					History *q=p->info_card->hinfo;
					q=AlocCelulaH();	/* se aloca celula H */
					if(!q) return 0;	/* se verifica alocarea celulei */
					q->urm=p->info_card->hinfo;
					p->info_card->hinfo =q;
					sprintf(q->info, "%s, %s %s %s %d", "SUCCESS",
					"transfer_funds", a, b, suma);	/* se introduce operatia 
												in istoricul cardului */
				}
			}
		}
	}


	LC *q=L;
	for(;q!=NULL;q=q->urm)
	{
		LSC *p=q->info;
		for(;p!=NULL; p=p->urm)
		{
			if(strcmp(p->info_card->cn ,b) == 0)
			{
				p->info_card->sold = p->info_card->sold + suma;
				History *q=p->info_card->hinfo;
				q=AlocCelulaH();	/* se aloca celula H */
				if(!q) return 0;	/* se verifica alocarea celulei */
				q->urm=p->info_card->hinfo;
				p->info_card->hinfo =q;
				sprintf(q->info, "%s, %s %s %s %d", "SUCCESS",
				"transfer_funds", a, b, suma);	/* se introduce operatia 
												in istoricul cardului */
				return 1;
			}
		}
	}
	return 0;
}

int cancel(LC *L, char *x) /* functie care deconecteaza cardul */
{
	LC *y=L;
	for(;y!=NULL;y=y->urm)
	{
		LSC *p=y->info;
		for(;p!=NULL; p=p->urm)
		{
			if(strcmp(p->info_card->cn, x) == 0)
			{
				History *q = p->info_card->hinfo;
				q=AlocCelulaH();	/* se aloca celula H */
				if(!q) return 0;	/* se verifica alocarea celulei */
				q->urm = p->info_card->hinfo;
				p->info_card->hinfo = q;
				sprintf(q->info, "%s, %s %s", "SUCCESS",
				"cancel", p->info_card->cn);	/* se introduce operatia
												 in istoricul cardului */
			}
		}
	}
	return 1;
}



int insert_card(LC *L, char *x, char *pin, int *k1, int *k2, int *k3, int *k4) 
							/* functie care insereaza cardul */
{
	*k2=0;
	int k=0, i;
	for(i=0;i<strlen(pin);i++) /* se calculeaza lungimea pinului */
 	{
 		k++;
 	}

 	if(*k3==3)	/* se verifica daca cardul nu este blocat */
 	{
 		FILE *output_file = fopen("output.out", "at");
		fprintf(output_file, "The card is blocked. Please contact the administrator.\n");
		fclose(output_file);
		LC *y=L;
		for(;y!=NULL;y=y->urm)
		{
			LSC *p=y->info;
			for(;p!=NULL; p=p->urm)
			{
				if(strcmp(p->info_card->cn, x) == 0)
				{
					History *q = p->info_card->hinfo;
					q=AlocCelulaH();	/* se aloca celula H */
					if(!q) return 0;	/* se verifica alocarea celulei */
					q->urm = p->info_card->hinfo;
					p->info_card->hinfo = q;
					sprintf(q->info, "%s, %s %s %s", "FAIL",
					"insert_card", p->info_card->cn, pin);	/* se introduce operatia
					 										in istoricul cardului */
					return 0;
				}
			}
		}
 	}

 	if(*k4 == 1) /* se verifica daca s-a facut schimbarea de pin */
 	{
 		LC *y=L;
		for(;y!=NULL;y=y->urm)
		{
			LSC *p=y->info;
			for(;p!=NULL; p=p->urm)
			{
				if(strcmp(p->info_card->cn, x) == 0)
				{
					if(strcmp(p->info_card->pin , pin) == 0)
					{ 
					
						History *t = p->info_card->hinfo;
						t=AlocCelulaH();/* se aloca celula H */
						if(!t) return 0;/* se verifica alocarea celulei */
						t->urm = p->info_card->hinfo;
						p->info_card->hinfo = t;
						sprintf(t->info, "%s, %s %s %s", "SUCCESS",
						"insert_card", p->info_card->cn, pin);	
							/* se introduce operatia in istoricul cardului */
						(*k2)++;
						*k3=0;
						return 1;
					}
				}
			}
		}
 	}

 	if(k==4)
	{	
		LC *y=L;
		for(;y!=NULL;y=y->urm)
		{
			LSC *p=y->info;
			for(;p!=NULL; p=p->urm)
			{
				if(strcmp(p->info_card->cn, x) == 0)
				{
					if(strcmp(p->info_card->pin , pin) == 0)
					{ 

						FILE *output_file = fopen("output.out", "at");
						fprintf(output_file, "You must change your PIN.\n");
						fclose(output_file);
						LC *z=L;
						for(;z!=NULL;z=z->urm)
						{
							LSC *q=z->info;
							for(;q!=NULL; q=q->urm)
							{
								if(strcmp(q->info_card->cn, x) == 0)
								{
									History *t = q->info_card->hinfo;
									t=AlocCelulaH();	/* se aloca celula H */
									if(!q) return 0;	
									/* se verifica alocarea celulei */
									t->urm = q->info_card->hinfo;
									q->info_card->hinfo = t;
									sprintf(t->info, "%s, %s %s %s", "SUCCESS",
									"insert_card", q->info_card->cn, pin);	
							/* se introduce operatia in istoricul cardului */
									(*k2)++;
									*k3=0;
									return 1;
								}
							}
						}
					}
					else 
					{
						FILE *output_file = fopen("output.out", "at");
						fprintf(output_file, "Invalid PIN\n");
						fclose(output_file);
						(*k2)++;
						(*k3)++;
						if(*k3==3) /* se verifica daca s-au facut 3 inserari gresite */
 						{
 							FILE *output_file = fopen("output.out", "at");
							fprintf(output_file, "The card is blocked. Please contact the administrator.\n");
							fclose(output_file);
						}
						LC *z=L;
						for(;z!=NULL;z=z->urm)
						{
							LSC *q=z->info;
							for(;q!=NULL; q=q->urm)
							{
								if(strcmp(q->info_card->cn, x) == 0)
								{
									if(*k1 == *k2)
									{
										*k2=0;
										*k3 =0;
									}
									History *t = q->info_card->hinfo;
									t=AlocCelulaH();	/* se aloca celula H */
									if(!q) return 0;	/* se verifica alocarea celulei */
									t->urm = q->info_card->hinfo;
									q->info_card->hinfo = t;
									sprintf(t->info, "%s, %s %s %s", "FAIL",
									"insert_card", q->info_card->cn, pin);	
							/* se introduce operatia in istoricul cardului */
									return 0;
								}
							}
						}
					}
					
				}
			}
		}
	}
	else 
	{	
		FILE *output_file = fopen("output.out", "at");
		fprintf(output_file, "Invalid PIN\n");
		fclose(output_file);
		(*k2)++;
		(*k3)++;
		if(*k3==3)	/* se verifica daca s-au facut 3 inserari gresite */
 		{
 			FILE *output_file = fopen("output.out", "at");
			fprintf(output_file, "The card is blocked. Please contact the administrator.\n");
			fclose(output_file);
		}
		LC *z=L;
		for(;z!=NULL;z=z->urm)
		{
			LSC *q=z->info;
			for(;q!=NULL; q=q->urm)
			{
				if(strcmp(q->info_card->cn, x) == 0)
				{
					History *t = q->info_card->hinfo;
					t=AlocCelulaH();	/* se aloca celula H */
					if(!q) return 0;	/* se verifica alocarea celulei */
					t->urm = q->info_card->hinfo;
					q->info_card->hinfo = t;
					sprintf(t->info, "%s, %s %s %s", "FAIL",
					"insert_card", q->info_card->cn, pin);	
					/* se introduce operatia in istoricul cardului */
					return 0;
				}
			}
		}
	}
	return 1;
}

int reverse_transaction(LC *L, char *x, char *y, int suma) 
				/* functie care anuleaza o tranzactie facuta */
{
	LC *p=L;
	for(;p!=NULL;p=p->urm)
	{
		LSC *q=p->info;
		for(;q!=NULL;q=q->urm)
		{
			if(strcmp(q->info_card->cn, y) == 0)
			{
				if(q->info_card->sold < suma) /* se verifica daca exita 
										suficienti bani pe cardul destinatie */
				{
					FILE *output_file = fopen("output.out", "at");
					fprintf(output_file, "The transaction cannot be reversed\n");
					fclose(output_file);
					return 0;
				}
				else
				{
					char z[200];
					sprintf(z, "%s, %s %s %s %d", "SUCCESS",
					"transfer_funds", x, y, suma);
					q->info_card->sold = q->info_card->sold - suma;
					History *t = q->info_card->hinfo, *aux=NULL;
					for(;t!=NULL;aux=t, t=t->urm)
					{
						if(strcmp(t->info, z)==0) /* se gaseste tranzactia in istoric */
							{
								break;
							}
					}
					if(aux==NULL) q->info_card->hinfo = t->urm;
					else aux->urm = t->urm;
					free(t); /* se elimina tranzactia din istoricul 
										cardului destinatie */
				}	
			}
		}
	}

	LC *z=L;
		for(;z!=NULL;z=z->urm)
		{
			LSC *q=z->info;
			for(;q!=NULL; q=q->urm)
			{
				if(strcmp(q->info_card->cn, x) == 0)
				{
					q->info_card->sold = q->info_card->sold + suma;
					History *t = q->info_card->hinfo;
					t=AlocCelulaH();	/* se aloca celula H */
					if(!q) return 0;	/* se verifica alocarea celulei */
					t->urm = q->info_card->hinfo;
					q->info_card->hinfo = t;
					sprintf(t->info, "%s, %s %s %s %d", "SUCCESS",
					"reverse_transaction", x, y, suma);/* se introduce operatia
													 in istoricul cardului */
					return 1;
				}
			}
		}
	return 0;
}

int unblock_card(LC *L, char *x, int *k3)
					/* functie care deblocheaza cardul */
{
	LC *z=L;
	for(;z!=NULL;z=z->urm)
	{
		LSC *q=z->info;
		for(;q!=NULL; q=q->urm)
		{
			if(strcmp(q->info_card->cn, x) == 0)
			{
				*k3 = 0;	/* se reseteaza numarul de inserari gresite */
				strcpy(q->info_card->status, "ACTIVE"); 
								/* statusul devine ACTIVE */
			}
		}
	}
	return 1;
}

int show(LC *L, char *cn) /* functie de afisare informatii despre card */
{
	FILE *output_file=fopen("output.out", "at");
	LC *y=L;
	for(;y!=NULL;y=y->urm)
	{
		LSC *p=y->info;
		for(;p!=NULL; p=p->urm)
		{
			if(strcmp(p->info_card->cn, cn) == 0)
			{
				fprintf(output_file, "(");
				fprintf(output_file,"card number: %s, ", p->info_card->cn);
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
						fprintf(output_file, "(%s)])\n", q->info);
						fclose(output_file);
						return 0;
					}
				}
				fprintf(output_file, "])\n");
			}
		}
	}
	return 0;
}

LC *DistrugeStruct(LC *L) /* functie care distruge baza de date */
{
	LC *y=L, *x=L, *aux2;
	for(;y!=NULL;y=y->urm)
	{
		LSC *p = y->info;
		for(;p!=NULL;p=p->urm)
		{
			History *t=p->info_card->hinfo, *aux;
			while(t)
			{
				aux=t;
				t=t->urm;
				free(aux); /* se elimina istoricul fiecarui card */
			}
		}
	}

	for(;x!=NULL;x=x->urm)
	{
		LSC *q = x->info, *aux1;
		while(q)
		{
			aux1=q;
			q=q->urm;
			free(aux1->info_card->cn);
			free(aux1->info_card->pin);
			free(aux1->info_card->date);
			free(aux1->info_card->cvv);
			free(aux1->info_card->status);
			free(aux1->info_card);
			free(aux1);		/* se elimina fiecare card */
		}
	}

	while(L)
	{
		aux2=L;
		L=L->urm;
		free(aux2);	/* se elimina fiecare celula LC */
	}
	return L;
}


LC *new_add_card(LC *L, char *cn,  char *date, char *pin, char *cvv, int nmc) 
							/* functie care redimensioneaza baza de date */
{
	LC *L1 = NULL;
	LC *cL = L;

 	if(Verificare(cL, cn) == 1)	/* se verifica daca exista deja 
 									cardul in baza de date */
 	{
 		FILE *output_file=fopen("output.out", "at");
 		fprintf(output_file, "The card already exists\n");
 		fclose(output_file);
 		return cL;
 	}

 	LC *x=L;
 	for(;x!=NULL;x=x->urm)
 	{
 		LSC *y=x->info; 
 		for(;y!=NULL; y=y->urm)
 		{
 			L1 = add_card(L1, y->info_card->cn, y->info_card->date,
 			y->info_card->pin, y->info_card->cvv, nmc); 
 	/* se aseaza cardurile anterioare pe noile pozitii, avnd nmc actualizat*/
 		}

 	}
	L1 = add_card(L1, cn, date, pin, cvv, nmc); 
	/* se insereaza noul card cu nmc actualizat */
 	return L1; /*se returneaza noul cap al liste */

}

int main()
{ 	

	LC *L=NULL;
	int nmc, i;
	char *buf; 
	char original[500][500]; /* matrice folosita pentru citirea fisierului */
	int original_line_count=0;	/* nr-ul de linii din fisierul de citire */
	int k1=0, k2=0, k3=0, k4=0;
	int k=0;

	FILE *input_file = fopen("input.in" , "r"); /* se deschide fisierul pentru citire */

	buf = (char*) calloc(100, sizeof(char));
	while (fgets(buf, 100, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++;
  }

	nmc = atoi(original[0]); /* nr-ul maxim de carduri */
	
	char *cn,*cn2, *pin, *cvv, *date;
	cn = (char*) calloc(18, sizeof(char));
	pin = (char*) calloc(6, sizeof(char));
	cvv = (char*) calloc(4, sizeof(char));
	date =(char*) calloc(6, sizeof(char));
	cn2 = (char*) calloc(18, sizeof(char));

	for(i=1;i<original_line_count;i++) /*parcurgere linie cu linie */
	{
		char *p;
		p=strtok(original[i]," "); /* se alege primul cuvant */
		int nr=strlen(original[i]);
		if(p[nr-1] == '\n')
		{
			p[nr-1] = '\0'; /* se elimina spatiul de la final */
		}
			if(strcmp(p, "add_card") == 0)	
			{
				char *q=p;
				q=strtok(NULL, " ");
				strcpy(cn, q);
				q=strtok(NULL, " ");
				strcpy(pin, q);
				q=strtok(NULL, " ");
				strcpy(date, q);
				q=strtok(NULL, " ");
				int nr = strlen(q);
				if(q[nr-1] == '\n')
				{
					q[nr-1] = '\0';
				}
				strcpy(cvv, q);
				if(k1 == 1)
				{
					k--;
				}
				if(nmc == k)
				{
					nmc = 2 * nmc;
					L=new_add_card(L, cn, date, pin, cvv, nmc);
					k++;
				}
				else
				{
					L = add_card(L, cn, date, pin, cvv, nmc);
					k++;
				}

			}
				
			if(strcmp(p, "show") == 0)
			
			{
				char *z=p;
				z=strtok(NULL, " ");
				if(z == NULL)
				{
					afisare(L);
				}
				else
				{
					int nr = strlen(z);
					if(z[nr-1] == '\n')
					{
						z[nr-1] = '\0';
					}
					strcpy(cn,z);
					show(L, cn);
				}
			}

			if(strcmp(p, "delete_card") == 0)
			{
				char *z=p;
				z=strtok(NULL, " ");
				int nr = strlen(z);
				if(z[nr-1] == '\n')
				{
					z[nr-1] = '\0';
				}
				strcpy(cn,z);
				delete_card(L, cn, &k1, &k3);
			}

			if(strcmp(p, "insert_card") == 0)
			{

				char *z=p;
				z=strtok(NULL, " ");
				strcpy(cn, z);
				z=strtok(NULL, " ");
				int nr= strlen(z);
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				strcpy(pin, z);
				insert_card(L, cn, pin, &k1, &k2, &k3, &k4);
				if(k3 == 3)
				{
					
					LC *z=L;
					for(;z!=NULL;z=z->urm)
					{
						LSC *q=z->info;
						for(;q!=NULL; q=q->urm)
						{
							if(strcmp(q->info_card->cn, cn) == 0)
							{
								strcpy(q->info_card->status, "LOCKED");
							}
						}
					}
				}
			}

			if(strcmp(p, "unblock_card") == 0)
			{
				char *z=p;
				z=strtok(NULL, " ");
				int nr=strlen(z);
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				strcpy(cn, z);
				unblock_card(L, cn, &k3);
			}

			if(strcmp(p, "cancel") == 0)
			{
				char *z=p;
				z=strtok(NULL, " ");
				int nr = strlen(z);
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				strcpy(cn, z);
				cancel(L, cn);
			}

			if(strcmp(p, "pin_change") == 0)
			{
				char *z=p;
				z=strtok(NULL, " ");
				strcpy(cn, z);
				z=strtok(NULL, " ");
				int nr=strlen(z);
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				strcpy(pin, z);
				pin_change(L, cn, pin, &k4, &k2);
			}
			if(strcmp(p, "balance_inquiry")==0)	
			{
				char *z=p;
				z=strtok(NULL, " ");
				int nr = strlen(z);
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				strcpy(cn, z);
				balance_inquiry(L, cn);
			}
			if(strcmp(p, "transfer_funds")==0)	
			{
				char *z=p;
				z=strtok(NULL, " ");
				strcpy(cn, z);
				z=strtok(NULL, " ");
				strcpy(cn2, z);
				z=strtok(NULL, " ");
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				int suma = atoi(z);
				transfer_funds(L, cn, cn2, suma);
			}

			if(strcmp(p, "recharge") == 0)	
			{
				char *z=p;
				z=strtok(NULL, " ");
				strcpy(cn, z);
				z=strtok(NULL, " ");
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				int suma = atoi(z);
				recharge(L, cn, suma);
			}

			if(strcmp(p, "cash_withdrawal") == 0)
			{
				char *z=p;
				z=strtok(NULL, " ");
				strcpy(cn, z);
				z=strtok(NULL, " ");
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				int suma = atoi(z);
				cash_withdrawal(L, cn, suma);
			}

			if(strcmp(p, "reverse_transaction") == 0)
			{
				char *z=p;
				z=strtok(NULL, " ");
				strcpy(cn, z);
				z=strtok(NULL, " ");
				strcpy(cn2, z);
				z=strtok(NULL, " ");
				if(z[nr-1] == '\n')
				{	
					z[nr-1] = '\0';
				}
				int suma = atoi(z);
				reverse_transaction(L, cn, cn2, suma);

			}
	}

		fclose(input_file); /*se inchide fisierul de citire */

	free(buf);	/* se elibereaza memoria alocata */
	free(cn);
	free(pin);
	free(cvv);
	free(date);
	free(cn2);
	L=DistrugeStruct(L); /* se distruge baza de date */
	return 0;
}

