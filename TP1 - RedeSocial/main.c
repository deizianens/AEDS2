#include <stdio.h>
#include <stdlib.h>
#include "usuarios.h"
#include "mensagens.h"
#include "amigos.h"

int main(int argc, char *argv[]) {

	Lista *l;
	Dados d;
	Mensagem m;
	DadosMigos dm;

	FILE *file;
	file = fopen(argv[1], "r"); //lê arquivo de entrada
	if (file == NULL) {
       printf ("Houve um erro ao abrir o arquivo.\n");
       return 1;
    }

	int i, aux, aux2, j, action, num_user, id_user;
	char trash;
	fscanf(file, "%d", &num_user); //le o numero de usuarios

	l=criaLista(); //cria um lista de usuarios

	for (i=0; i<num_user; i++){
		aux=0;

        d.migos= criaListaMigos(); //cria uma lista de amigos para cada usuario
        d.mensagens = criaPilha(); //cria uma pilha de mensagem para cada usuario

		aux=0;
		fscanf(file, "%d", &d.id); //le id
		fscanf(file, "%c", &trash); //le ;
		fscanf(file, "%[^;];s", &d.nome); //le nome

		d.num_migos=0;
		d.num_msg=0;

		//le o numero de amigos e seus ids
		for (j=0; trash==';'; j++){
			fscanf(file, "%d", &dm.id_migo);
			fscanf(file, "%c", &trash);
			d.num_migos++;
			criaNodeMigos(d.migos, dm);
		}

		criaNode(l, d);
	}

	while(!feof(file)){
		fscanf(file, "%d", &m.tempo);
		fscanf(file, "%c", &trash); //le ;
		fscanf(file, "%d", &action);
		fscanf(file, "%c", &trash); //le ;

		if (action==1){
			fscanf(file, "%d", &m.id_user); //le o id do usuario que vai postar a mensagem
			aux = atNode(l, m.id_user); //acha o indice do usuario na lista
			Node* node_aux = atIndex(l, aux); //acha o nó do usuario na lista
			node_aux->data.num_msg++;

			fscanf(file, "%c", &trash); //le ;
			fscanf(file, "%d", &m.id_m); //le o id da mensagem
			fscanf(file, "%c", &trash); //le ;
			fscanf(file, "%[^\n]s", &m.texto);
			m.likes=0;

			postarMensagem(node_aux->data.mensagens, m);

			for(i=0; i<node_aux->data.num_migos; i++){

                NodeMigos* nm = atIndexMigos(node_aux->data.migos, i); //retorna todas as celulas da pilha

                aux = atNode(l, nm->data_migo.id_migo); //acha o indice do usuario na lista
                Node* n = atIndex(l, aux); //acha o nó do usuario na lista
                n->data.num_msg++;
                postarMensagem(n->data.mensagens, m);
			}


		}
		//2 = iniciar amizade
		else if(action==2){
			fscanf(file, "%d", &aux);
			fscanf(file, "%c", &trash);
			fscanf(file, "%d", &aux2);
			iniciarAmizade(l,aux, aux2);
		}
		//3 = cancelar amizade
		else if(action==3){
			fscanf(file, "%d", &aux);
			fscanf(file, "%c", &trash);
			fscanf(file, "%d", &aux2);
			cancelarAmizade(l, aux, aux2);
		}
		//4 = curtir mensagem
		else if(action==4){
			fscanf(file, "%d", &aux);
			fscanf(file, "%c", &trash);
			fscanf(file, "%d", &aux2);

            Node* nd;
            int index;

            for(i=0; i<num_user; i++){

                Node* n = atIndex(l, i); //acha o nó do usuario na lista

                aux = atCelula(n->data.mensagens, aux2); //acha o indice mensagem na pilha do usuario

                if(aux!=-1){
                    Celula *c = atIndexCel(n->data.mensagens, aux); //acha a celula da mensagem
                    index = atNode(l, c->msg.id_user); //acha o indice do nó do usuario que postou a mensagem
                    nd = atIndex(l, index); //acha o nó do usuario na lista
                    break; //sai do loop
                }
            }

            aux = curtirMensagem(nd->data.mensagens, aux2, nd->data.mensagens);

            if(nd->data.num_msg<aux){
                nd->data.num_msg++;

            }

            //pega todos os amigos do usuario que postou a mensagem e atualiza-as nas pilhas dos amigos
            for(i=0; i<nd->data.num_migos; i++){

                NodeMigos* nm = atIndexMigos(nd->data.migos, i); //acha o nó de cada amigo na lista de amigos

                index = atNode(l, nm->data_migo.id_migo); //acha o indice de cada amigo na lista
                Node* n = atIndex(l, index); //acha o nó do usuario na lista

                aux = curtirMensagem(n->data.mensagens, aux2, nd->data.mensagens);

                if(n->data.num_msg<=aux){
                    n->data.num_msg++;

                }
            }
		}
		//5 = exibir timeline
		else if(action==5){
			fscanf(file, "%d", &aux);

			int aux2 = atNode(l, aux); //acha o indice do usuario na lista
			Node *n = atIndex(l, aux2); //retorna o nó do usuario na lista
			exibirTimeline(n, argv[1]);
		}
	}

    fclose(file);
	return 0;
}
