#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreSBB.h"
#include "TabelaHash.h"

#define FALSE 0
#define TRUE 1

SBBTree* inicializa(){
    SBBTree *raiz = (SBBTree*) malloc(sizeof(SBBTree));
    *raiz = NULL; //raiz aponta pra null
    return raiz;
}

void insere (Dados d, SBBTree *raiz){
    int aux;
    int fim = FALSE;
    int inclinacao = SBB_VERTICAL;
    iinsere (d, raiz, &inclinacao, &fim);
}

void iinsere(Dados d, SBBTree *ptr, int *incli, int *fim){
    //insere ao encontrar folha
    if(*ptr == NULL){

        iinsere_aqui(d, ptr, incli, fim);
    }
    else if(d.chave < (*ptr)->d.chave){ //busca na subarvore a esquerda

        iinsere(d, &(*ptr)->esq, &(*ptr)->esqtipo, fim);
        if(*fim) return;
        if((*ptr)->esqtipo == SBB_VERTICAL){
            *fim = TRUE;
        }
        else if((*ptr)->esq->esqtipo ==SBB_HORIZONTAL){ //verifica se há dois horizontais seguidos a esquerda

            ee(ptr);
            *incli = SBB_HORIZONTAL;
        }
        else if((*ptr)->esq->dirtipo==SBB_HORIZONTAL){
            ed(ptr);
            *incli = SBB_HORIZONTAL;
        }
    }
    else if(d.chave > (*ptr)->d.chave){ //busca na subarvore a direita

        iinsere(d, &(*ptr)->dir, &(*ptr)->dirtipo, fim);
        if(*fim) return;
        if((*ptr)->dirtipo == SBB_VERTICAL){
            *fim = TRUE;
        }
        else if((*ptr)->dir->esqtipo == SBB_HORIZONTAL){
            de(ptr);
            *incli = SBB_HORIZONTAL;
        }
        else if((*ptr)->dir->dirtipo == SBB_HORIZONTAL){
            dd(ptr);
            *incli = SBB_HORIZONTAL;
        }
    } //chave ja existe na arvore
    else {
        //printf("erro: chave ja esta na arvore, adicionado na lista. %s\n", d.date);
        Data data;
        data.chave = d.chave;
        strcpy(data.date, d.date);
        data.p1 = d.p1;
        data.p2 = d.p2;
        data.rodada = d.rodada;
        strcpy(data.time1, d.time1);
        strcpy(data.time2, d.time2);

        criaNode((*ptr)->l, data); //cria nó da lista
        *fim = TRUE;
    }
}

void iinsere_aqui(Dados d, SBBTree *ptr, int *incli, int *fim){
    SBB *no = malloc(sizeof(SBB)); //aloca espaço pra um nó
    if(!no){
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    no->d = d; //recebe os dados
    no->esq = NULL; //define apontador esquerda pra null
    no->dir = NULL; //define apontador direita pra null
    no->esqtipo = SBB_VERTICAL; //define tipo pra vertical
    no->dirtipo = SBB_VERTICAL; //define tipo pra vertical
    no->l = criaLista();

    *ptr = no; //insere na arvore
    *incli = SBB_HORIZONTAL;
    *fim = FALSE;
}

void pesquisaTree(SBBTree *raiz, int chave, char* data){
    if(*raiz==NULL){
        //printf("Chave não encontrada");
    }
    SBB *atual = *raiz;
    while(atual != NULL){
        if(chave == atual->d.chave){
            FILE *file;
            file = fopen("saida.txt", "a+");
            if(strcmp(data, atual->d.date)==0){
                fprintf(file, "%s;%s;%d;%s;%d\n", atual->d.date, atual->d.time1, atual->d.p1, atual->d.time2, atual->d.p2);
            }
            fclose(file);
            if(atual->l->cabeca != NULL){ //verifica se o nó possui uma lista
                imprimeLista(atual->l, atual->d.date); //caso tenha, imprime a lista
            }
            return;
        }
        if(chave > atual->d.chave){
            atual = atual->dir;
        }
        else{
            atual = atual->esq;
        }
    }
}

void percorreArv(SBBTree *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        percorreArv(&((*raiz)->esq));
        printf("%d %s %s %d\n", (*raiz)->d.chave, (*raiz)->d.date,(*raiz)->d.time1, (*raiz)->d.p1);
        percorreArv(&((*raiz)->dir));
    }
}

void ee(SBBTree *ptr){
    SBB *no = (*ptr); //ponteiro auxiliar recebe onde ptr aponta
    SBB *esq = no->esq; //recebe a esquerda do primeiro nó

    no->esq = esq->dir; //esquerda do nó aponta para a direita do nó a esquerda
    esq->dir = no; //direita da esquerda aponta pra nó
    esq->esqtipo = SBB_VERTICAL;
    no->esqtipo = SBB_VERTICAL;
    *ptr = esq; //ptr recebe esquerda (agr novo nó pai)
}

void dd(SBBTree *ptr){
    SBB *no = (*ptr); //ponteiro auxiliar recebe onde ptr aponta
    SBB *dir = no->dir; //recebe a direita do primeiro nó

    no->dir = dir->esq; // direita do no aponta para esquerda do nó a direita
    dir->esq = no; //esquerda do no a direita recebe o nó
    dir->dirtipo = SBB_VERTICAL;
    no->dirtipo = SBB_VERTICAL;
    *ptr = dir; //ptr recebe direita (agr novo nó pai)
}

void ed(SBBTree *ptr){
    SBB *no = (*ptr); //ponteiro auxiliar recebe onde ptr aponta
    SBB *esq = no->esq; //esq recebe a esquerda do primeiro no
    SBB *dir = esq->dir; //dir recebe a direita do nó a esquerda do nó ptr

    esq ->dir = dir->esq;
    no->esq = dir->dir;
    dir->esq = esq;
    dir->dir = no;
    esq->dirtipo = SBB_VERTICAL;
    no->esqtipo = SBB_VERTICAL;
    *ptr = dir;
}

void de(SBBTree *ptr){
    SBB *no = (*ptr);
    SBB *dir = no->dir;
    SBB *esq = dir->esq;

    no->dir = esq->esq;
    dir->esq = esq->dir;
    esq->esq = no;
    esq->dir = dir;
    dir->esqtipo = SBB_VERTICAL;
    no->dirtipo = SBB_VERTICAL;
    *ptr = esq;
}

