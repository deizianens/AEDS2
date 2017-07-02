#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabelaHash.h"
#include "ArvoreSBB.h"

HashTable *criaHash(int hash_size){
    HashTable* h = (HashTable*) malloc(sizeof(HashTable));
    int i;
    if(h != NULL){
        h->hash_size = hash_size; //recebe o tamanho da tabela hash
        h->itens = (Jogos**) malloc(hash_size*sizeof(Jogos*));
    }
     if(h->itens==NULL){ //caso dê erro na alocação
        free(h);
        return NULL;
    }
    h ->qtd_itens = 0;

    for (i=0; i<h->hash_size; i++){
        h->itens[i] = NULL; //coloca null em todas as posições
    }
    return h;
}

int funcaoHash(int chave, int hash_size){
    return (chave & 0x7FFFFFFF) % hash_size; //0x7FFFFF evita numeros negativos
}

//faz a soma de todos os valores ascii da string
int transformaChave(char *str){
    int i, valor = 7;
    int tam = strlen(str);
    for(i=0; i<tam; i++){
        valor = 31 * valor + (int) str[i];

    }
    return valor;
}

void insereHash(HashTable* h, Jogos s, SBBTree *raiz){
    if(h == NULL || h->qtd_itens == h->hash_size){ //verifica se a tabela foi criada ou esta cheia
        return 0;
    }
    int chave =transformaChave(s.date); //pega a chave transformada em int
    int i, pos, newPos;
    pos = funcaoHash(chave, h->hash_size);
    if(h->itens[pos]==NULL){ //se a posição na tabela está vazia
        Jogos* j;
        j = (Jogos*) malloc(sizeof(Jogos));
        if (j == NULL){ //verifica se houve falha na alocação
            //printf("Falha na alocação!");
            return;
        }
        *j = s;
        h->itens[pos] = j; //coloca na tabela
        h->qtd_itens++; //aumenta o tamanho da tabela
    }
    else{ //caso a posição da tabela ja esteja ocupada
        //printf("Posição ocupada, insere em arvore %d\n", pos);
        Dados d;
        d.chave = s.chave;
        strcpy(d.date, s.date);
        d.p1 = s.p1;
        d.p2 = s.p2;
        d.rodada = s.rodada;
        strcpy(d.time1, s.time1);
        strcpy(d.time2, s.time2);
        insere(d, raiz);
    }
}

void buscaHash (HashTable* h, int chave, SBBTree *raiz, char* data){
    if (h == NULL){ //verifica se tabela existe
        //printf("You shall not pass!");
        return;
    }
    int pos = funcaoHash(chave, h->hash_size);
    if(h->itens[pos] == NULL){ //verifica se o item existe
        //printf("Item não existe!");
        return;
    }
    else{
        FILE *file;
        file = fopen("saida.txt", "a+");
        Jogos j;
        j = *(h->itens[pos]); //copia o conteudo pro ponteiro
        if(strcmp(j.date, data)==0){
            fprintf(file, "%s;%s;%d;%s;%d\n", j.date, j.time1, j.p1, j.time2, j.p2); //escreve informações em arquivo
        }
        fclose(file);
        if(*raiz != NULL){ //verifica se arvore não está vazia
            pesquisaTree(raiz, chave, data);
        }
    }

}
