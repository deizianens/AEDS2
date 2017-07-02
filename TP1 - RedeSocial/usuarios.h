#ifndef REDESOCIAL_USUARIOS_H
#define REDESOCIAL_USUARIOS_H

#include <stdbool.h>
#include "amigos.h"
#include "mensagens.h"

typedef struct dados {
	int id; //armazena o id do usuario
	char nome[50]; //armazena o nome
	ListaMigos *migos; //armazena a lista de amigos
	int num_migos; //armazena o numero de amigos
	Pilha *mensagens; //armazena a pilha de mensagens
	int num_msg; //armazena o numero de mensagens
}Dados;

typedef struct node{
	Dados data;
	struct node *prox;
}Node;

typedef struct lista{
	int tamanho;
	Node *cabeca;
}Lista;

//cabeçalho de funções
Lista* criaLista();
void criaNode(Lista *l, Dados d); //cria no da lista
void imprimeLista(Lista* l, Dados d); //imprime lista (utilizada apenas para testes)
bool vazia(Lista* l); //verifica lista vazia
int atNode(Lista* l, int n); //retorna o indice do nó com o determinado id
Node* atIndex(Lista *l, int indice); //retorna qual o no de um determinado indice
void iniciarAmizade (Lista* l, int id_1, int id_2);
void cancelarAmizade (Lista* l, int id_1, int id_2);
void exibirTimeline(Node *n, char* argv);
NodeMigos* verAmigos(Node *n); //função nunca utilizada nesta implementação

#endif //REDESOCIAL_USUARIOS_H
