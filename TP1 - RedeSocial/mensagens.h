#ifndef REDESOCIAL_MENSAGENS_H
#define REDESOCIAL_MENSAGENS_H

#include <stdbool.h>

typedef struct mensagem{
	int id_m; //id mensagem
	char texto[145]; //texto da mensagem
	int tempo; //tempo (useless)
	int likes; // numero de likes da mensagem
	int id_user; //id do usuario que postou a mensagem
}Mensagem;

typedef struct celula {
	Mensagem msg;
	struct celula *prox_c;
}Celula;

typedef struct pilha {
	int size;
	Celula *topo;
}Pilha;

//cabeçalho das funções
Pilha* criaPilha();
bool pilhaVazia(Pilha* p); //verifica se a pilha está vazia
void postarMensagem(Pilha* p, Mensagem m); //posta a mensagem na pilha de mensagens de cada usuario
int atCelula(Pilha* p, int id_m); //retorna o indice da celula com o determinado id
Celula* atIndexCel(Pilha* p, int indice); //retorna qual a celula de um determinado indice
void excluiMsg(Pilha* p, int indice); //utilizada como auxiliar do curtirMensagem
void popMsg(Pilha* p); //remove nó do topo (utilizada como auxiliar do curtirMensagem)
int curtirMensagem(Pilha* p, int id_m, Pilha* pd);

#endif //REDESOCIAL_MENSAGENS_H
