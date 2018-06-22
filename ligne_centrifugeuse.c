#include "ligne_centrifugeuse.h"
#include "centrifugeuse.h"
#include <stdlib.h>
#include <stdio.h>
/*acts on the line received by reference, fills his table of new centrifuges (with starting configuration of the TP1),
will put nb centrifuges EN_FONCTION and the constant number EN_ATTENTE, all the fields of the
struct are well adjusted. It returns 1 for success or 0 otherwise (a number too big).*/
int init_ligne_centrifugeuse(struct t_ligne_centrifugeuse* ptr_lig, unsigned int nb)//??
{
ptr_lig = (t_ligne_centrifugeuse*)malloc(sizeof(t_ligne_centrifugeuse));
ptr_lig->en_fonction = 0;
ptr_lig->en_attente = 0;

int i;
for(i=0;i<32;i++)
    ptr_lig->t_cen[i] = init_centrifugeuse();
for(i=0;i<32;i++)
    if(get_bit(nb,i))
        ptr_lig->en_fonction++;
    else
        ptr_lig->en_attente++;

return 1;
}
int check_ones_before(t_ligne_centrifugeuse* ptr_lig,int i)
{
    if(i==0)return 0;
    else if(i==1)
    {
        if(ptr_lig->t_cen[0]->state == EN_FONCTION)return 1;
        else return 0;
    }
    else
    {
        if(ptr_lig->t_cen[i-1]->state==EN_ATTENTE)
        {
            return 0;
        }
        else
        {
            if(ptr_lig->t_cen[i-2]->state==EN_ATTENTE)
                return 1;
            else return 2;
        }
    }
    return 2;
}
int check_ones_after(t_ligne_centrifugeuse* ptr_lig,int i)
{
    if(i==31)return 0;
    else if(i==30)
    {
        if(ptr_lig->t_cen[31]->state==EN_FONCTION)return 1;
        else return 0;
    }
    else
    {
        if(ptr_lig->t_cen[i+1]->state==EN_ATTENTE)
        {
            return 0;
        }
        else
        {
            if(ptr_lig->t_cen[i+2]->state==EN_ATTENTE)
                return 1;
            else return 2;
        }
    }
    return 2;
}

//add if possible a centrifuge EN_FONCTION in the line. Return of 1 if successful, 0 otherwise (configuration impossible).
int ajouter_cnt(t_ligne_centrifugeuse *ptr_lig)//??
{
    int i;
    for(i=0; i<32; i++)
    {
        if(ptr_lig->t_cen[i]->state==EN_ATTENTE){
            if((check_ones_before(ptr_lig,i)==0&&check_ones_after(ptr_lig,i)==0)||(check_ones_before(ptr_lig,i)==1&&check_ones_after(ptr_lig,i)==0)||(check_ones_before(ptr_lig,i)==0&&check_ones_after(ptr_lig,i)==1))
            {
                ptr_lig->t_cen[i]->state = EN_FONCTION;
                ptr_lig->en_fonction++;
                return 1;
            }
        }
    }
    return 0;
}
//reduces by one the number of centrifuges EN_FONCTION in the line. Return of 1 if successful, 0 otherwise (no EN_FONCTION).
int reduire_cnt(t_ligne_centrifugeuse *ptr_lig)
{
    int i;
    for(i=0; i<32; i++)
    {
        if(ptr_lig->t_cen[i]->state==EN_FONCTION)
        {
            ptr_lig->t_cen[i]->state=EN_ATTENTE;
            ptr_lig->en_fonction--;
            ptr_lig->en_attente++;
            return 1;
        }
    }
    return 0;
}
/* triggers the function toc_centrifugeuse () for each of the centrifuges in the table and responds correctly to any change of
state of one of the centrifuges.*/
void toc_ligne(t_ligne_centrifugeuse *ptr_lig)//??
{
int i;
    for(i=0;i<32;i++)
        if(toc_centrifugeuse(ptr_lig->t_cen[i])==EN_FONCTION)
                ptr_lig->en_fonction++;
        else if(toc_centrifugeuse(ptr_lig->t_cen[i])==EN_ATTENTE)
                ptr_lig->en_attente++;
}

/*if the position is valid and if this centrifuge of the table is neither EN_FONCTION nor EN_ATTENTE, a new
centrifuge replaces the one in the position given in the table. The function returns a copy of the
eliminated centrifuge, otherwise a centrifuge whose all members are 0 is returned.*/
t_centrifugeuse* remplacer_cnt(t_ligne_centrifugeuse *ptr_lig, unsigned int pos)
{
    if(ptr_lig->t_cen[pos]->state!=EN_FONCTION&&ptr_lig->t_cen[pos]->state!=EN_ATTENTE)
    {
        ptr_lig->t_cen[pos] = init_centrifugeuse();
        return ptr_lig->t_cen[pos];
    }
    else
    {
        ptr_lig->t_cen[pos] = init_centrifugeuse();
        ptr_lig->t_cen[pos]->state=0;
        ptr_lig->t_cen[pos]->counters[0]=0;
        ptr_lig->t_cen[pos]->counters[1]=0;
        ptr_lig->t_cen[pos]->counters[2]=0;
        ptr_lig->t_cen[pos]->counters[3]=0;
        ptr_lig->t_cen[pos]->count_break=0;
        ptr_lig->t_cen[pos]->prob_breakage=0;
        ptr_lig->t_cen[pos]->last_en_fonction=0;
        ptr_lig->t_cen[pos]->last_en_attente=0;
        ptr_lig->t_cen[pos]->countdown=0;
        return ptr_lig->t_cen[pos];
    }
}
/* which returns the bitstream of the line which gives the positions of the centrifuges in this state. SPEC: The
second parameter must be one of the four state constants otherwise the result obtained has no
meaning.*/
unsigned int get_en_etat(const t_ligne_centrifugeuse * ptr_lig, int etat)
{
    unsigned int temp=0;

    int i;
    for(i=0;i<32;i++)
        if(ptr_lig->t_cen[i]->state==etat)
            set_bit(temp,i);

return temp;
}
/*return a copy of the centrifuge to this position in the table. It returns a centrifuge whose
all members are 0 if the position is invalid.*/
t_centrifugeuse* get_centrifugeuse(const t_ligne_centrifugeuse *ptr_lig, unsigned int pos)
{
    if(pos<=32)return ptr_lig->t_cen[pos+1];
    else{
        t_centrifugeuse* x = init_centrifugeuse();
        x->state=0;
        x->counters[0]=0;
        x->counters[1]=0;
        x->counters[2]=0;
        x->counters[3]=0;
        x->count_break=0;
        x->prob_breakage=0;
        x->last_en_fonction=0;
        x->last_en_attente=0;
        x->countdown=0;
        return x;
    }
}
/*this private function of the module switches the centrifuges to positions pos1 and pos2 of the
array and in the corresponding bit streams if their states differ.*/
void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, unsigned int pos1, unsigned int pos2)
{
    t_centrifugeuse* temp=init_centrifugeuse();
    ptr_lig->t_cen[pos1]=ptr_lig->t_cen[pos1];
    ptr_lig->t_cen[pos2]=temp;
}
