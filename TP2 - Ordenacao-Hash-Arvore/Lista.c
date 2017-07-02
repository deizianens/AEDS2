#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Lista.h"

Lista* criaLista(){
	Lista *l = (Lista*) malloc(sizeof(Lista)); //aloca espaço na memoria
	l->tamanho = 0; //tamanho 0 = lista vazia
	l->cabeca = NULL;

	return l;
}

void criaNode(Lista *l, Data d){
	Node *n = (Node*) malloc (sizeof(Node));

	n->data = d; //adiciona as informações do nó
	n->prox = l->cabeca;
	l->cabeca = n;
	l->tamanho++;
}

//imprime a lista de amigos (utilizada em testes apenas)
void imprimeLista(Lista* l, char *data){

    if(vazia(l)){
        //printf("Lista Vazia\n");
        return;
    }

	Node *ponteiro = l->cabeca;
	int i;
    FILE *file;
    file = fopen("saida.txt", "a+");

	while (ponteiro != NULL){
        if(strcmp(ponteiro->data.date, data)==0){
            fprintf(file, "%s;%s;%d;%s;%d\n", ponteiro->data.date, ponteiro->data.time1, ponteiro->data.p1, ponteiro->data.time2, ponteiro->data.p2);
		}

		ponteiro = ponteiro->prox;
	}
    fclose(file);
}

//verifica se lista esta vazia
bool vazia(Lista* l){
	return (l->tamanho==0);
}

