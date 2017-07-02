#ifndef REDESOCIAL_AMIGOS_H
#define REDESOCIAL_AMIGOS_H

#include <stdbool.h>

typedef struct dadosmigos {
	int id_migo; //id do amigo
}DadosMigos;

typedef struct nodemigos{
	DadosMigos data_migo;
	struct nodemigos *prox_migo;
}NodeMigos;

typedef struct listamigos{
	int tamanho;
	NodeMigos *top;
}ListaMigos;

ListaMigos* criaListaMigos();
void criaNodeMigos(ListaMigos *l, DadosMigos d); //cria no da lista
bool isEmpty(ListaMigos* l); //verifica lista vazia
int atNodeMigos(ListaMigos* l, int id_migo); //retorna o indice do n� com o determinado id
NodeMigos* atIndexMigos(ListaMigos *l, int indice); //retorna qual o no de um determinado indice
void excluiMigo(ListaMigos* lm, int indice);
void pop(ListaMigos* lm); //remove n� do topo

#endif //REDESOCIAL_AMIGOS_H
