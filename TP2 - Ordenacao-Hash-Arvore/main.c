/*  TRABALHO PRATICO 2
    DEIZIANE NATANI DA SILVA
    TA1 - 2015121980
*/

#include <stdio.h>
#include <stdlib.h>
#include "TabelaHash.h"
#include "TabelaClassificacao.h"
#include "ArvoreSBB.h"

int main(int argc, char *argv[]){

    FILE *file;
    file = fopen("entrada7.txt", "r");
    if (file == NULL) {
       printf ("Houve um erro ao abrir o arquivo.\n");
       return 1;
    }

    int i, k, cnt, y, hash_size, ord, num_times, num_rod, num_jog, chave, aux;
    char trash, trash2[10];

    fscanf(file, "%d", &hash_size);  //tamanho da tabela hash
    fscanf(file, "%c", &trash); //lê ;
    fscanf(file, "%d", &ord); //tipo de ordenação
    fscanf(file, "%d", &num_times);
    fscanf(file, "%c", &trash); //lê ;
    fscanf(file, "%d", &num_rod);
    fscanf(file, "%c", &trash); //lê ;
    fscanf(file, "%d", &num_jog);
    fscanf(file, "%c", &trash);

    HashTable* ht = criaHash(hash_size); //cria a tabela hash de tamanho hash_size
    Jogos j;
    Table* t = criaTable(num_times); //cria a tabela de classificação
    SBBTree *raiz; //ponteiro pra raiz da árvore
    raiz = inicializa(raiz);

    int vetor[num_times]; //vetor auxiliar usado na ordenação
    char timeaux[50];

    for(i=0; i<num_times;i++){
        if (fgets(timeaux, 49, file) != NULL) {
            size_t len = strlen(timeaux);
            if (len > 0 && timeaux[len-1] == '\n') { //retira quebra de linhas
                timeaux[--len] = '\0';
            }
            strcpy(t[i].time, timeaux); //coloca nome na tabela
        }
    }

    for(i=0; i<num_rod; i++){
        fscanf(file, "%[^\n]", &trash2);
        j.rodada = i+1;

        for(k=0; k<num_jog; k++){
            fscanf(file, "%c", &trash); //pega quebra de linha -_-
            fscanf(file, "%[^;]s", &j.date);
            fscanf(file, "%c", &trash); //lê ;
            fscanf(file, "%[^;];", &j.time1);
            fscanf(file, "%d", &j.p1);
            fscanf(file, "%c", &trash); //lê ;
            fscanf(file, "%[^;];", &j.time2);
            fscanf(file, "%d", &j.p2);


            insere2(t, j.time1, j.time2, j.p1, j.p2, ord, num_times); //insere itens na tabela de classificação
            chave = transformaChave(j.date); //transforma a data em uma chave numérica
            j.chave = chave; //adiciona chave
            insereHash(ht, j, raiz); //insere na tabela hash
        }

        t=auxiliarP(t, 0, num_times-1, num_times,  ord); //ordena tabela
        imprimeTabela(t, num_times, j.rodada); //imprime a tabela de classificação
        fscanf(file, "%c", &trash); //pega quebra de linha -_-
    }

    char **pesquisa;
    pesquisa = (char**) malloc(1*sizeof(char*));
    if(!pesquisa) {
        exit(EXIT_FAILURE);
    }
    for(i=0; i<1; i++){
       pesquisa[i] = (char*) malloc(11*sizeof(char));
    }


    i=0;
    while(!feof(file)){ //lê as pesquisas
        fscanf(file, "%s", pesquisa[i]);
        i++;
        pesquisa = (char**) realloc(pesquisa, (i+1)*sizeof(char*));
        pesquisa[i] = (char*)malloc(11*sizeof(char));

    }

    fclose(file);

    for(y=0; y<i; y++){
        chave = transformaChave(pesquisa[y]); //transforma data na chave da tabela hash
        buscaHash(ht, chave, raiz, pesquisa[y]); //busca posição na tabela
    }

    return 0;
}
