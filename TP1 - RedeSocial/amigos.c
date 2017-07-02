#include <stdio.h>
#include "amigos.h"
#include "usuarios.h"

ListaMigos* criaListaMigos(){

    ListaMigos *l = (ListaMigos*) malloc(sizeof(ListaMigos)); //aloca espaço na memoria
	l->tamanho = 0; //tamanho 0 = lista vazia
	l->top = NULL;

	return l;
}

void criaNodeMigos(ListaMigos *l, DadosMigos d){
    NodeMigos *n = (NodeMigos*) malloc (sizeof(NodeMigos));

	n->data_migo = d; //adiciona as informações do nó
	n->prox_migo = l->top;
	l->top = n;
	l->tamanho++;
}

//verifica se lista esta vazia
bool isEmpty(ListaMigos* l){
	return (l->tamanho==0);
}

int atNodeMigos(ListaMigos* l, int id_migo){
	int indice =0;
	NodeMigos *ponteiro = l->top;

	//percorre lista enquanto o ponteiro não for igual ao final da lista
	while(ponteiro->data_migo.id_migo!=id_migo && ponteiro!=NULL){
		ponteiro = ponteiro->prox_migo;
		indice++;
	}

	//retorna o indice, caso o item exista
	if(ponteiro != NULL){
		return indice;
	}
}

NodeMigos* atIndexMigos(ListaMigos *l, int indice){
	int i;

	//verifica se o indice é valido
	if(indice >=0 && indice< l->tamanho){
		NodeMigos *n = l->top;

		for(i=0; i<indice; i++){
			n = n->prox_migo; //recebe proximo nó até chegar no desejado
		}

		return n;
	}
	else {
		printf("Amigos: Indice invalido :(");
	}
}


void imprimeMigos(ListaMigos* lm){
    //verifica se a lista está vazia
    if(isEmpty(lm)){
        printf("Sem amigos\n");
        return;
    }

    NodeMigos* ponteiro = lm->top;

	while (ponteiro != NULL){
        printf("%d ", ponteiro->data_migo.id_migo);
		ponteiro = ponteiro->prox_migo;
	}
	printf("\n");
}

//exclui nó do topo da pilha
void pop(ListaMigos* lm){
    if(!isEmpty(lm)){
        NodeMigos* ponteiro = lm->top; //cria ponteiro auxiliar pro topo da pilha
        lm->top = ponteiro->prox_migo; //liga o topo ao proximo elemento da pilha
        lm->tamanho--;
    }
    else{
        printf("Pilha Vazia!\n");
    }
}

void excluiMigo(ListaMigos* lm, int indice){

    if(indice == 0){
        pop(lm);
    }
    else{
        NodeMigos* nm = atIndexMigos(lm, indice);

        if(nm != NULL){
            NodeMigos* nm_anterior = atIndexMigos(lm, indice-1); //pega o nó anterior ao no que se quer excluir
            nm_anterior->prox_migo = nm->prox_migo;
            free(nm);
            lm->tamanho--;
        }
        else{
            printf("Erro!\n");
        }
    }

}
