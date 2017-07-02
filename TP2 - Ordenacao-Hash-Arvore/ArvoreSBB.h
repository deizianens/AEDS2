#ifndef FUTEBOL_ARVORESBB_H
#define FUTEBOL_ARVORESBB_H

#define SBB_VERTICAL 0
#define SBB_HORIZONTAL 1

#include "Lista.h"

typedef struct dados{
    int rodada;
    int chave;
    char date[11];
    int date_f; //data formatada sem o /
    char time1[50];
    int p1;
    char time2[50];
    int p2;
}Dados;

typedef struct sbb {
    Dados d;
    int alt; //altura da subarvore
    struct sbb *esq;
    struct sbb *dir;
    int esqtipo;
    int dirtipo;
    Lista* l; //ponteiro pra lista
}SBB;

typedef SBB* SBBTree;

void ee(SBBTree *ptr);
void ed(SBBTree *ptr);
void dd(SBBTree *ptr);
void de(SBBTree *ptr);
void percorreArv(SBBTree *raiz);
SBBTree* inicializa();
void iinsere(Dados d, SBBTree *ptr, int *incli, int *fim);
void iinsere_aqui(Dados d, SBBTree *ptr, int *incli, int *fim);
void insere (Dados d, SBBTree *raiz);
void pesquisaTree(SBBTree *raiz, int chave, char* data);

#endif //FUTEBOL_ARVORESBB_H
