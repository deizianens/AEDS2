#ifndef FUTEBOL_LISTA_H
#define FUTEBOL_LISTA_H

#include <stdbool.h>

typedef struct data {
	int rodada;
    int chave;
    char date[11];
    int date_f; //data formatada sem o /
    char time1[50];
    int p1;
    char time2[50];
    int p2;
}Data;

typedef struct node{
	Data data;
	struct node *prox;
}Node;

typedef struct lista{
	int tamanho;
	Node *cabeca;
}Lista;

//cabeçalho de funções
Lista* criaLista();
void criaNode(Lista *l, Data d); //cria no da lista
void imprimeLista(Lista* l, char* data); //imprime lista (utilizada apenas para testes)
bool vazia(Lista* l);

#endif //FUTEBOL_LISTA_H
