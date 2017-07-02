#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "usuarios.h"
#include "mensagens.h"

Lista* criaLista(){
	Lista *l = (Lista*) malloc(sizeof(Lista)); //aloca espaço na memoria
	l->tamanho = 0; //tamanho 0 = lista vazia
	l->cabeca = NULL;

	return l;
}

void criaNode(Lista *l, Dados d){
	Node *n = (Node*) malloc (sizeof(Node));

	n->data = d; //adiciona as informações do nó
	n->prox = l->cabeca;
	l->cabeca = n;
	l->tamanho++;
}

//imprime a lista de amigos (utilizada em testes apenas)
void imprimeLista(Lista* l, Dados d){

    if(vazia(l)){
        printf("Lista Vazia\n");
        return;
    }

	Node *ponteiro = l->cabeca;
	int i;

	while (ponteiro != NULL){
		printf("%d %s ", ponteiro->data.id, ponteiro->data.nome);

        imprimeMigos(ponteiro->data.migos);

		printf("\n");
		ponteiro = ponteiro->prox;
	}
	printf("\n");
}

//verifica se lista esta vazia
bool vazia(Lista* l){
	return (l->tamanho==0);
}

//retorna o indice do nó com o determinado id
int atNode(Lista* l, int n){
	int indice =0;
	Node *ponteiro = l->cabeca;

	//percorre lista enquanto o ponteiro não for igual ao final da lista
	while(ponteiro->data.id!=n && ponteiro!=NULL){
		ponteiro = ponteiro->prox;
		indice++;
	}

	//retorna o indice, caso o item exista
	if(ponteiro != NULL){
		return indice;
	}
}

//retorna o indice do nó com o determinado id
Node* atIndex(Lista *l, int indice){
	int i;

	//verifica se o indice é valido
	if(indice >=0 && indice< l->tamanho){
		Node *n = l->cabeca;

		for(i=0; i<indice; i++){
			n = n->prox; //recebe proximo nó até chegar no desejado
		}

		return n;
	}
	else {
		printf("Indice invalido :( User");
	}
}

void iniciarAmizade (Lista* l, int id_1, int id_2){
    int aux;
    DadosMigos dm;

    dm.id_migo= id_2;

	aux = atNode(l, id_1); //acha o indice do usuario na lista
	Node* node_aux = atIndex(l, aux); //acha o nó do usuario na lista
	node_aux->data.num_migos++;

	criaNodeMigos(node_aux->data.migos, dm); //cria um nó na lista de amigos

    dm.id_migo = id_1;

	aux = atNode(l, id_2); //acha o indice do usuario na lista
	node_aux = atIndex(l, aux); //acha o nó do usuario na lista
	node_aux->data.num_migos++;

    criaNodeMigos(node_aux->data.migos, dm); //cria um nó na lista de amigos
}

void cancelarAmizade (Lista* l, int id_1, int id_2){
    int aux, aux2;

    aux = atNode(l, id_1); //acha o indice do usuario na lista
	Node* node_aux = atIndex(l, aux); //acha o nó do usuario na lista
	aux2 = atNodeMigos(node_aux->data.migos, id_2); //acha o indice do usuario na lista
	node_aux->data.num_migos--;

	excluiMigo(node_aux->data.migos, aux2); //excluir nó da pilha

    aux = atNode(l, id_2); //acha o indice do usuario na lista
	node_aux = atIndex(l, aux); //acha o nó do usuario na lista
	aux2 = atNodeMigos(node_aux->data.migos, id_1); //acha o indice do usuario na lista
	node_aux->data.num_migos--;

    excluiMigo(node_aux->data.migos, aux2); //excluir nó da pilha
}

void exibirTimeline(Node *n, char *argv){

    FILE *file;
    char t[20]= "log.";
    strcat(t, argv);
	file = fopen(t, "a"); //escreve em arquivo de saida
    Celula* ponteiro = n->data.mensagens->topo;
    int i;
    fprintf(file, "%d %s\n", n->data.id, n->data.nome);

    //imprime até a flag, que é o numero de mensagens novas do usuario
	for(i=0; i<n->data.num_msg; i++){
        fprintf(file, "%d %s %d\n", ponteiro->msg.id_m, ponteiro->msg.texto, ponteiro->msg.likes);
		ponteiro = ponteiro->prox_c;
	}
	fclose(file);

    n->data.num_msg = 0; //zera o numero de mensagens novas, isso ajuda na hora de exibir a timeline novamente,
                        //assim só vão aparecer as novas mensagens
}

NodeMigos* verAmigos(Node *n){
    return n->data.migos; //retorna a lista de amigos, para exibir tal lista, basta chamar o procedimento imprimePilha();
}
