#pragma once

typedef struct t_ligne_centrifugeuse{
     struct t_centrifugeuse* t_cen[32];
     unsigned int en_fonction;
     unsigned int en_attente;
     unsigned int en_bris;
     unsigned int en_arret;
     unsigned int pos_fonction;// configuration_valid()
     unsigned int pos_bris;
     unsigned int pos_attente;
     unsigned int pos_arret;
}t_ligne_centrifugeuse;

//int init_ligne_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, unsigned int nb);
int ajouter_cnt(t_ligne_centrifugeuse *ptr_lig);
int reduire_cnt(t_ligne_centrifugeuse *ptr_lig);
void toc_ligne(t_ligne_centrifugeuse *ptr_lig);
struct t_centrifugeuse* remplacer_cnt(t_ligne_centrifugeuse *ptr_lig, unsigned int pos);
unsigned int get_en_etat(const t_ligne_centrifugeuse * ptr_lig, int etat);
struct t_centrifugeuse* get_centrifugeuse(const t_ligne_centrifugeuse *ptr_lig, unsigned int pos);
void permuter_centrifugeuse(t_ligne_centrifugeuse * ptr_lig, unsigned int pos1, unsigned int pos2);
