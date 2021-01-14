/* NUME: CHIRILA ALBERT, GRUPA:314CB*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



typedef struct history
{
	char info[200];
	struct history *urm;
}History;

typedef struct card
{
	char *cn;
	char *pin;
	char *date; 
	char *cvv;
	int sold;
	char *status;
	History* hinfo ;
}CARD;

typedef struct submultime
{
	CARD* info_card;
	struct submultime *urm;
}LSC, *TLSC, **ALSC;

typedef struct lista
{
	LSC* info;
	struct lista *urm;
}LC, *TLC, **ALC;

History *AlocCelulaH();
LSC *AlocCelulaLSC(void);
LC *AlocCelulaLC(void);
int Inserare_InceputH(History **aL);
int Verificare(LC *L, char *x);
int cardinal(LC *L);
int afisare(LC *L);









