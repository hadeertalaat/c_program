#include "centrifugeuse.h"

// returns a new centrifuge in the EN_ARRET state-> Its initial probability of breakage is given by a constant of the module->
struct t_centrifugeuse* init_centrifugeuse(void)
{
    t_centrifugeuse* t_cent= (t_centrifugeuse*)malloc(sizeof(struct t_centrifugeuse));
    t_cent->state = EN_ARRET;
    t_cent->counters[0]= 0;//??
    t_cent->counters[1]= 0 ;//??
    t_cent->counters[2]= 0;//??
    t_cent->counters[3]= 0;//??
    t_cent->count_break=0;
    t_cent->prob_breakage=0;
    t_cent->last_en_fonction =0;
    t_cent->last_en_attente =0;
    t_cent->countdown=INFINITE ;
    return t_cent;
}
// allows to put a centrifuge EN_ATTENTE in the state EN_FONCTION-> Return 1 if successful, 0 otherwise (if it is not in state EN_ATTENTE)->
static double random(int x){
    return (((float)(rand()%x))/x);
}

int set_en_fonction(t_centrifugeuse * ptr_cnt)
{
    if( ptr_cnt->state == EN_ATTENTE )
    {
        ptr_cnt->state = EN_FONCTION;
        return 1;
    }
    return 0;
}
//allows to put a centrifuge EN_ARRET or EN_FONCTION in the state EN_ATTENTE-> Return 1 if successful, 0 otherwise->
int set_en_attente(t_centrifugeuse * ptr_cnt)
{
    if( ptr_cnt->state == EN_ARRET || ptr_cnt->state == EN_FONCTION )
    {
        ptr_cnt->state = EN_ATTENTE;
        return 1;
    }
    return 0;
}
// allows to put a centrifuge EN_ATTENTE or EN_FONCTION in the state EN_ARRET-> Return 1 if successful, 0 otherwise->
int set_en_arret(t_centrifugeuse * ptr_cnt)
{
    if( ptr_cnt->state == EN_ATTENTE || ptr_cnt->state == EN_FONCTION )
    {
        ptr_cnt->state = EN_ARRET;
        return 1;
    }
    return 0;
}
/* triggers the meter changes according to its state->
If the centrifuge is EN_BRIS and its countdown ≠ INFINITE then decrement the countdown
and if it falls to 0, the centrifuge goes to the state EN_ARRET and the two counters like the
probability of breakage are reset to their values of departure->
If the centrifuge is EN_ATTENTE or EN_FONCTION, the probability of breakage applies and triggers a break test,
if the centrifuge passes EN_BRIS following this test, its countdown is fixed to a very big constant of the module (INFINI)
and its number of breaks is incremented-> Otherwise, only the probability of breakage will increase (with a static
function of the module)-> The function returns the state of the centrifuge->
*/
int toc_centrifugeuse(t_centrifugeuse * ptr_cnt)
{
    if( ptr_cnt->state == EN_BRIS && ptr_cnt->countdown == INFINITE )
    {
        ptr_cnt->countdown --;
        if( ptr_cnt->countdown == 0 )
            ptr_cnt->state = EN_ARRET;
            ptr_cnt->last_en_attente = ptr_cnt->prob_breakage;//??
            ptr_cnt->last_en_fonction = ptr_cnt->prob_breakage;//??
    }
    else if( ptr_cnt->state == EN_ATTENTE || ptr_cnt->state == EN_FONCTION )
    {
         if(ptr_cnt->prob_breakage==1)
         {
             ptr_cnt->state=EN_BRIS ;
             ptr_cnt->countdown= INFINITE;
             ptr_cnt->count_break++;
         }
         else
            ptr_cnt->prob_breakage = ptr_cnt->prob_breakage+random(10);
    }
    return ptr_cnt->state;
}
/*which applies only to a centrifuge EN_BRIS whose countdown is equal to INFINI, it then sets the countdown of the
centrifuge to the time received in parameter and returns 1, otherwise it returns 0->
*/
int set_temps_reparation(t_centrifugeuse * ptr_cnt, unsigned int temps)
{
    if( ptr_cnt->state == EN_BRIS && ptr_cnt->countdown > INFINITE )
    {
        ptr_cnt->countdown = temps;
        return 1;
    }
    return 0;
}
/* which will place from the address received and in the prescribed order the eight counters present in the
variable: the four state counters followed by the number of breaks, the two counters since the last repair and countdown -> */
void get_compteurs(const t_centrifugeuse * ptr_cnt, unsigned int * compteurs)//??
{
    unsigned int com[8];
    com[0]=ptr_cnt->counters[0];
    com[1]=ptr_cnt->counters[1];
    com[2]=ptr_cnt->counters[2];
    com[3]=ptr_cnt->counters[3];
    com[4]=ptr_cnt->count_break;
    com[5]=ptr_cnt->prob_breakage;
    com[6]=ptr_cnt->last_en_fonction;
    com[7]=ptr_cnt->last_en_attente;
    compteurs = com;
}
//returns the probability of current breakage of the centrifuge
double get_prob_bris(const t_centrifugeuse * ptr_cnt)
{
        return ptr_cnt->prob_breakage;
}

/* which increases the probability of breaking a centrifuge EN_ATTENTE or EN_FONCTION after a knock without breakage->
ATTENTION, in its definition the calculated increase will depend on three counters of the centrifuge:
mainly the number of breakages already suffered and the two counters since the repair-> This process
remains personal to your team-> The increase given to a centrifuge EN_ATTENTE must be a fraction less
than that given to an EN_FONCTION (this fraction must be defined by a constant of the module)->
*/
void accroitre_prob(t_centrifugeuse * ptr_cnt)//static
{
    if( ptr_cnt->state == EN_ATTENTE)
        ptr_cnt->prob_breakage=ptr_cnt->prob_breakage+random(10);
    else if(ptr_cnt->state == EN_FONCTION)
        ptr_cnt->prob_breakage=ptr_cnt->prob_breakage+random(5);
}

void print_centrifuge (const t_centrifugeuse* ptr_cnt){
    printf("count break  : %s\n",bits2string(ptr_cnt->count_break));
    printf("stat         : %d\n",ptr_cnt->state);
    printf("counter[0]   : %s\n",bits2string(ptr_cnt->counters[0]));
    printf("counter[1]   : %s\n",bits2string(ptr_cnt->counters[1]));
    printf("counter[2]   : %s\n",bits2string(ptr_cnt->counters[2]));
    printf("counter[3]   : %s\n",bits2string(ptr_cnt->counters[3]));
    printf("CountDown    : %s\n",bits2string(ptr_cnt->countdown));
    printf("probBreakage : %f\n",ptr_cnt->prob_breakage);
}

