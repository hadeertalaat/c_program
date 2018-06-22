#pragma once

enum state {EN_BRIS = 1, EN_ARRET = 2, EN_ATTENTE = 3, EN_FONCTION = 4};

int INFINITE = 1000;

typedef struct t_centrifugeuse
{
    int state;
    unsigned int counters[4];
    unsigned int count_break;
    double prob_breakage;
    unsigned int last_en_fonction;
    unsigned int last_en_attente;
    unsigned countdown;
}t_centrifugeuse;

t_centrifugeuse* init_centrifugeuse(void);
int set_en_fonction(t_centrifugeuse * ptr_cnt);
int set_en_attente(t_centrifugeuse * ptr_cnt);
int set_en_arret(t_centrifugeuse * ptr_cnt);
int toc_centrifugeuse(t_centrifugeuse * ptr_cnt);
int set_temps_reparation(t_centrifugeuse * ptr_cnt, unsigned int temps);
void get_compteurs(const t_centrifugeuse * ptr_cnt, unsigned int * compteurs);
double get_prob_bris(const t_centrifugeuse * ptr_cnt);
void accroitre_prob(t_centrifugeuse * ptr_cnt);//static
void print_centrifuge (const t_centrifugeuse * ptr_cnt);


/*#include <stdio.h>
#include <stdlib.h>
//#include "centrifugeuse.h"
int main()
{
printf("hello");
/*
unsigned int temps=0;
unsigned int compteurs[8]={0};

struct t_centrifugeuse* x;
x = init_centrifugeuse();
print_centrifuge(x);
printf("%d\n",set_en_fonction(x));
printf("%d\n",set_en_attente(x));
printf("%d\n",set_en_arret(x));

printf("%d\n",toc_centrifugeuse(x));
printf("%d\n",set_temps_reparation(x,temps));
printf("%f\n",get_prob_bris(x));
get_compteurs(x,compteurs);
accroitre_prob(x);//static
*/
/*    return 0;
}
*/
