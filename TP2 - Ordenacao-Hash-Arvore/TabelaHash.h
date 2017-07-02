#ifndef FUTEBOL_TABELAHASH_H
#define FUTEBOL_TABELAHASH_H

#include "ArvoreSBB.h"

typedef struct jogos{
    int rodada;
    int chave;
    char date[12];
    char time1[50];
    int p1;
    char time2[50];
    int p2;
}Jogos;

typedef struct hashtable{
    int qtd_itens, hash_size;
    Jogos **itens;
}HashTable;


HashTable *criaHash(int hash_size); //aloca espaço para o "array" de ponteiros e os inicializa com NULL
int funcaoHash(int chave, int hash_size);
void insereHash(HashTable* h, Jogos s, SBBTree *raiz);
void buscaHash (HashTable* h, int chave, SBBTree *raiz, char* data);
int transformaChave(char *str);

#endif //FUTEBOL_TABELAHASH_H
