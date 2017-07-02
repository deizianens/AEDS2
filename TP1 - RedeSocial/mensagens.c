#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mensagens.h"
#include "usuarios.h"

//cria pilha vazia
Pilha* criaPilha(){
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
	p->topo = NULL;
	p->size = 0;

	return p;
}

//verifica se pilha esta vazia
bool pilhaVazia(Pilha* p){
	return (p->size==0);
}



//posta a mensagem no topo da pilha :)
void postarMensagem(Pilha* p, Mensagem m){
	Celula* cel = (Celula *) malloc(sizeof(Celula));

	cel->msg = m;
	cel->prox_c = p->topo;
	p->topo = cel;
	p->size++;

}

int atCelula(Pilha* p  , int id_m){
    int indice =0;
	Celula *ponteiro = p->topo;

	//percorre lista enquanto o ponteiro não for igual ao final da lista
	while(ponteiro!=NULL && ponteiro->msg.id_m!=id_m){
		ponteiro = ponteiro->prox_c;
		indice++;
	}

	//retorna o indice, caso o item exista
	if(ponteiro != NULL){
		return indice;
	}
	else{
        indice = -1; //retorna -1 caso não exista
        return indice;
	}
}

Celula* atIndexCel(Pilha* p, int indice){
    int i;

	//verifica se o indice é valido
	if(indice >=0 && indice< p->size){
		Celula *c = p->topo;

		for(i=0; i<indice; i++){
			c = c->prox_c; //recebe proximo nó até chegar no desejado
		}

		return c;
	}
	else {
		printf("Mensagem: Indice invalido :(");
	}
}

//retira o primeiro elemento da pilha
void popMsg(Pilha* p){
    if(!pilhaVazia(p)){
        Celula* ponteiro = p->topo; //cria ponteiro auxiliar pro topo da pilha
        p->topo = ponteiro->prox_c; //liga o topo ao proximo elemento da pilha
        p->size--;
    }
    else{
        printf("Pilha Vazia!\n");
    }
}

void excluiMsg(Pilha* p, int indice){
    if(indice == 0){
        popMsg(p); //caso seja a primeira posição da pilha, remove-a
    }
    else{
        Celula* c = atIndexCel(p, indice);

        if(c != NULL){
            Celula* c_anterior = atIndexCel(p, indice-1); //pega o nó anterior ao no que se quer excluir
            c_anterior->prox_c = c->prox_c;
            free(c); //libera posição da memoria
            p->size--; //diminui tamanho da pilha
        }
        else{
            printf("Erro ao excluir!\n");
        }
    }
}

int curtirMensagem(Pilha* p, int id_m, Pilha* pd){
    int aux, aux2;
    Mensagem m;

    aux = atCelula(p, id_m); //verifica se o usuario possui a mensagem em sua pilha de mensagens
    if(aux!=-1){ //caso tenha
        Celula *c = atIndexCel(p, aux);
        c->msg.likes++;

        m.id_m = c->msg.id_m;
        m.likes = c->msg.likes;
        m.tempo = c->msg.tempo;
        m.id_user = c->msg.id_user;
        strcpy(m.texto, c->msg.texto);

        excluiMsg(p, aux); //exclui mensagem da pilha
        postarMensagem(p, m); //adiciona a mensagem no topo da pilha
    }
    else{ //caso não tenha
        aux = atCelula(pd, id_m); //pega a mensagem da pilha do dono (o que postou a mensagem)
        Celula *c = atIndexCel(pd, aux); //oega a celula da mensagem
        c->msg.likes++;

        m.id_m = c->msg.id_m;
        m.likes = c->msg.likes;
        m.tempo = c->msg.tempo;
        m.id_user = c->msg.id_user;
        strcpy(m.texto, c->msg.texto);

        postarMensagem(p, m); //somente adiciona a mensagem no topo da pilha
    }
    return aux;
}


