#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabelaClassificacao.h"

Table* criaTable(int sizeT){
    Table *t = (Table*) malloc(sizeT*sizeof(Table)); //aloca espaço para tabela na memória
    int i;
    for(i=0; i<sizeT; i++){ //preenche a tabela com 0
        t[i].gols_pro = 0;
        t[i].num_vitorias = 0;
        t[i].pontos = 0;
        t[i].saldo_gols =0;
    }
    return t;
}

//insere dados na tabela
void insere2(Table* t, char* time1, char* time2, int p1, int p2, int ord, int size){
    int i=0;
    //procura o time 1 na tabela
    for(i=0;i<size;i++){
        if(strcmp(t[i].time, time1)==0){
            t[i].saldo_gols += (p1-p2);
            t[i].gols_pro += p1;
            if(p1>p2){ //caso o time tenha ganhado
                t[i].num_vitorias++;
                t[i].pontos +=3;
            }
            else if(p1==p2){ //caso tenha empate
                t[i].pontos +=1;
            }
        }
    }
    i=0;
    //procura o time 2 na tabela
    for(i=0;i<size;i++){
        if(strcmp(t[i].time, time2)==0){
            t[i].saldo_gols += (p2-p1);
            t[i].gols_pro += p2;
            if(p2>p1){ //caso que o time 2 ganhou
                t[i].num_vitorias++;
                t[i].pontos +=3;
            }
            else if(p1==p2){ //caso de empate
                t[i].pontos +=1;
            }
        }
    }


}

void imprimeTabela(Table* t, int sizeT, int rod){
    int i;
    FILE *file;
    file = fopen("saida.txt", "a");
    fprintf(file, "%d\n", rod);
    for(i=0; i<sizeT; i++){
        fprintf(file, "%s %d %d %d %d\n", t[i].time, t[i].pontos, t[i].num_vitorias, t[i].saldo_gols, t[i].gols_pro);
    }
    fclose(file);
}

//ordena por pontos utilizando o QuickSort
Table* ordenaQuickP(Table* t, int i, int j, int sizeT){
    int pivo, k;
    if(j>i){
        pivo = particionaQuickP(t, i, j); //calculo a posição do pivo
        ordenaQuickP(t, i, pivo-1, sizeT); //ordena elementos a esquerda do pivo
        ordenaQuickP(t, pivo+1, j, sizeT); //ordena elementos a direita do pivo
    }

    return t;
}

//ordena por pontos utilizando o QuickSort
int particionaQuickP(Table* t, int i, int j){
    int esq, dir, pivo;
    Table aux;
    esq = i;
    dir= j;
    pivo = t[i].pontos ; //pivo é o elemento inicial
    while(esq<dir && esq<=j && dir>=i){
        while(t[esq].pontos>=pivo && esq<=j){ //avança posição da esquerda
            esq++;
        }
        while(t[dir].pontos<pivo && dir>=i){ //recua posição da direita
            dir--;
        }
        if(esq < dir){ //faz as trocas
            aux = t[esq];
            t[esq] = t[dir];
            t[dir] = aux;
        }
    }
    aux = t[i];
    t[i] = t[dir]; //primeira posição recebe a posição da direita
    t[dir] = aux; //posição da direita se torna o valor do pivo
    return dir;
}

//ordena utilizando o QuickSort (ordena por nº de vitorias)
Table* ordenaQuickV(Table* t, int i, int j, int sizeT){
    int pivo,k;
    if(j>i){
        pivo = particionaQuickV(t, i, j); //calculo a posição do pivo
        ordenaQuickV(t, i, pivo-1, sizeT); //ordena elementos a esquerda do pivo
        ordenaQuickV(t, pivo+1, j, sizeT); //ordena elementos a direita do pivo
    }

    return t;
}

//ordena utilizando o QuickSort (ordena por nº de vitorias)
int particionaQuickV(Table* t, int i, int j){
    int esq, dir, pivo;
    Table aux;
    esq = i;
    dir= j;
    pivo = t[i].num_vitorias ; //pivo é o elemento inicial
    while(esq<dir && esq<=j && dir>=i){
        while(t[esq].num_vitorias>=pivo && esq<=j){ //avança posição da esquerda
            esq++;
        }
        while(t[dir].num_vitorias<pivo && dir>=i){ //recua posição da direita
            dir--;
        }
        if(esq < dir){ //faz as trocas
            aux = t[esq];
            t[esq] = t[dir];
            t[dir] = aux;
        }
    }
    aux = t[i];
    t[i] = t[dir]; //primeira posição recebe a posição da direita
    t[dir] = aux; //posição da direita se torna o valor do pivo
    return dir;
}

//ordena por saldo de gols utilizando o QuickSort
Table* ordenaQuickS(Table* t, int i, int j, int sizeT){
    int pivo,k;
    if(j>i){
        pivo = particionaQuickS(t, i, j); //calculo a posição do pivo
        ordenaQuickS(t, i, pivo-1, sizeT); //ordena elementos a esquerda do pivo
        ordenaQuickS(t, pivo+1, j, sizeT); //ordena elementos a direita do pivo
    }

    return t;
}

//ordena por saldo de gols utilizando o QuickSort
int particionaQuickS(Table* t, int i, int j){
    int esq, dir, pivo;
    Table aux;
    esq = i;
    dir= j;
    pivo = t[i].saldo_gols ; //pivo é o elemento inicial
    while(esq<dir && esq<=j && dir>=i){
        while(t[esq].saldo_gols>=pivo && esq<=j){ //avança posição da esquerda
            esq++;
        }
        while(t[dir].saldo_gols<pivo && dir>=i){ //recua posição da direita
            dir--;
        }
        if(esq < dir){ //faz as trocas
            aux = t[esq];
            t[esq] = t[dir];
            t[dir] = aux;
        }
    }
    aux = t[i];
    t[i] = t[dir]; //primeira posição recebe a posição da direita
    t[dir] = aux; //posição da direita se torna o valor do pivo
    return dir;
}

//ordena por gols pró utilizando o QuickSort
Table* ordenaQuickGP(Table* t, int i, int j, int sizeT){
    int pivo,k;
    if(j>i){
        pivo = particionaQuickGP(t, i, j); //calculo a posição do pivo
        ordenaQuickGP(t, i, pivo-1, sizeT); //ordena elementos a esquerda do pivo
        ordenaQuickGP(t, pivo+1, j, sizeT); //ordena elementos a direita do pivo
    }

    return t;
}

//ordena por gols pró utilizando o QuickSort
int particionaQuickGP(Table* t, int i, int j){
    int esq, dir, pivo;
    Table aux;
    esq = i;
    dir= j;
    pivo = t[i].gols_pro ; //pivo é o elemento inicial
    while(esq<dir && esq<=j && dir>=i){
        while(t[esq].gols_pro>=pivo && esq<=j){ //avança posição da esquerda
            esq++;
        }
        while(t[dir].gols_pro<pivo && dir>=i){ //recua posição da direita
            dir--;
        }
        if(esq < dir){ //faz as trocas
            aux = t[esq];
            t[esq] = t[dir];
            t[dir] = aux;
        }
    }
    aux = t[i];
    t[i] = t[dir]; //primeira posição recebe a posição da direita
    t[dir] = aux; //posição da direita se torna o valor do pivo
    return dir;
}

//ordena por ordem alfabetica utilizando o QuickSort
Table* ordenaQuickA(Table* t, int i, int j, int sizeT, int c){
    int pivo,k;
    if(j>i){
        pivo = particionaQuickA(t, i, j, c); //calculo a posição do pivo
        t=ordenaQuickA(t, i, pivo-1, sizeT, c); //ordena elementos a esquerda do pivo
        t=ordenaQuickA(t, pivo+1, j, sizeT, c); //ordena elementos a direita do pivo
    }

    return t;
}

//ordena por ordem alfabetica utilizando o QuickSort
int particionaQuickA(Table* t, int i, int j, int c){
    int esq, dir, pivo;
    Table aux;
    esq = i;
    dir= j;
    pivo = t[i].time[c] ; //pivo é o elemento inicial
    while(esq<dir && esq<=j && dir>=i){
        while(t[esq].time[c]<=pivo && esq<=j){ //avança posição da esquerda
            esq++;
        }
        while(t[dir].time[c]>pivo && dir>=i){ //recua posição da direita
            dir--;
        }
        if(esq < dir){ //faz as trocas
            aux = t[esq];
            t[esq] = t[dir];
            t[dir] = aux;
        }
    }

    aux = t[i];
    t[i] = t[dir]; //primeira posição recebe a posição da direita
    t[dir] = aux; //posição da direita se torna o valor do pivo
    return dir;
}

int* verificaEmpatesP(Table* t, int i, int j, int sizeT){
    int k, x=i, aux, *aux2, l=1;
    aux2 = (int*) malloc(sizeT*sizeof(int));
    for(k=0; k<sizeT; k++){
        aux2[k] = -1; //enche o vetor com -1
    }
    //verifica se possui empate por pontos
    while(x<j){
        l=1;
        aux = t[x].pontos;
        aux2[0] = x;
        for(k=x+1; k<j+1; k++){
            if(aux == t[k].pontos){
                aux2[l] = k; //guarda posições que estão empatadas
                l++;
            }
        }
        if(aux2[1]!=-1){
             return aux2;
        }
        x++;
    }
    aux2[0]= -1; //caso nao haja empates
     return aux2;
}

int* verificaEmpatesV(Table* t, int i, int j, int sizeT){
    int k, x=i, aux, *aux2, l=1;
    aux2 = (int*) malloc(sizeT*sizeof(int));
    for(k=0; k<sizeT; k++){
        aux2[k] = -1; //enche o vetor com -1
    }
    //verifica se possui empate por pontos
    while(x<j){
        l=1;
        aux = t[x].num_vitorias;
        aux2[0] = x;
        aux2[1] = -1;
        for(k=x+1; k<j+1; k++){
            if(aux == t[k].num_vitorias){
                aux2[l] = k; //guarda posições que estão empatadas
                l++;
            }
        }
        if(aux2[1]!=-1){
             return aux2;
        }

        x++;
    }
    aux2[0]= -1; //caso nao haja empates
     return aux2;
}

int* verificaEmpatesS(Table* t, int i, int j, int sizeT){
    int k, x=i, aux, *aux2, l=1;
     aux2 = (int*) malloc(sizeT*sizeof(int));
    for(k=0; k<sizeT; k++){
        aux2[k] = -1; //enche o vetor com -1
    }
    //verifica se possui empate por pontos
    while(x<j){
        aux = t[x].saldo_gols;
        aux2[0] = x;
        for(k=x+1; k<j+1; k++){
            if(aux == t[k].saldo_gols){
                aux2[l] = k; //guarda posições que estão empatadas
                l++;
            }
        }
        if(aux2[1]!=-1){
             return aux2;

        }

        x++;
    }
    aux2[0]= -1; //caso nao haja empates
     return aux2;
}

int* verificaEmpatesGP(Table* t, int i, int j, int sizeT){
    int k, x=i, aux, *aux2, l=1;
    aux2 = (int*) malloc(sizeT*sizeof(int));
    for(k=0; k<sizeT; k++){
        aux2[k] = -1; //enche o vetor com -1
    }
    //verifica se possui empate por pontos
    while(x<j){
        aux = t[x].gols_pro;
        aux2[0] = x;
        for(k=x+1; k<j+1; k++){ //n sizeT
            if(aux == t[k].gols_pro){
                aux2[l] = k; //guarda posições que estão empatadas
                l++;
            }
        }
        if(aux2[1]!=-1){
            return aux2;

        }
        x++;
    }
    aux2[0]= -1; //caso nao haja empates
    return aux2;
}

int* verificaEmpatesA(Table* t, int i, int j, int sizeT, int c){
    int k, x=i, aux, *aux2, l=1, q;
    aux2 = (int*) malloc(sizeT*sizeof(int));
    for(k=0; k<sizeT; k++){
        aux2[k] = -1; //enche o vetor com -1
    }
    //verifica se possui empate por pontos
    while(x<j){
        l=1;
        aux = (int) t[x].time[c];
        aux2[0] = x;
        for(k=x+1; k<j+1; k++){
            q = (int) t[k].time[c];
            if(aux == q){
                aux2[l] = k; //guarda posições que estão empatadas
                l++;
            }
        }
        if(aux2[1]!=-1){
            return aux2;
        }
        x++;;
    }
    aux2[0]= -1; //caso nao haja empates
    return aux2;
}

Table* auxiliarP(Table* t, int i, int j, int sizeT, int ord){
    int k;
    int *_result;
    static int h1, h2;
    _result = (int*) malloc(sizeT*sizeof(int));

    if(ord==1){ //ordenação quicksort
        t=ordenaQuickP(t, i, j, sizeT); //ordena por pontos
        _result = verificaEmpatesP(t, i, j, sizeT); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){ //enquanto há empates
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){  //caso haja empates por numero de pontos
                    k=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    h1= _result[0]; h2= _result[k-1];
                    t=auxiliarV(t, _result[0], _result[k-1], sizeT, ord);//ordena novamente por nº de vitorias
                    _result[1] = -1; //só para entra no prox if
                }
                 if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    _result[0] = h2+1; //inicio da ordenação será a partir do prox item
                    _result = verificaEmpatesP(t, _result[0], j, sizeT); //verifica se também há empate
                }
            }
        }

    }
    else{ //ordenação shellsort
        int hp=0, cnt;
        t=ordenaShellP(t, sizeT); //ordena por pontos
        _result = verificaEmpatesP(t, i, j, sizeT); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){ //enquanto há empates
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){  //caso haja empates por numero de pontos
                    k=0;
                    hp=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    Table *taux = (Table*) malloc(k*sizeof(Table)); //cria uma table auxiliar
                    h1= _result[0]; h2= _result[k-1];
                    for(cnt=h1; cnt<=h2; cnt++){ //preenche table auxiliar
                        taux[hp] = t[cnt]; //tabela auxiliar recebe os elementos empatados da tabela
                        hp++;
                    }
                    taux=auxiliarV(taux, 0, hp-1, hp, ord);//ordena novamente por nº de vitorias
                    hp=0;
                    for(cnt=h1; cnt<=h2; cnt++){ //recebe itens já ordenados da taux
                        t[cnt] = taux[hp]; //tabela recebe os elementos da tabela auxiliar
                        hp++;
                    }
                    free(taux);
                    _result[1] = -1; //só para entrar no prox if
                }
                 if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    _result[0] = h2+1; //inicio da ordenação será a partir do prox item
                    _result = verificaEmpatesP(t, _result[0], j, sizeT); //verifica se também há empate
                }
            }
        }

    }
     free(_result);
    return t;
}

Table* auxiliarV(Table* t, int i, int j, int sizeT, int ord){
    int k;
    int *_result;
    static int h1, h2;
    _result = (int*) malloc(sizeT*sizeof(int));

    if(ord==1){ //ordena quicksort
        t=ordenaQuickV(t, i, j, sizeT); //ordena por numero de vitorias
        _result = verificaEmpatesV(t, i, j, sizeT); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){
                    k=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    h1= _result[0]; h2= _result[k-1];
                    t=auxiliarS(t, _result[0], _result[k-1], sizeT, ord);//ordena novamente por saldo de gols
                    _result[1] = -1; //só para entra no prox if
                }
                //se result[1] == -1 quer dizer que não há mais empates
                if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    _result[0] = h2+1; //inicio da ordenação será a partir do prox item
                    _result = verificaEmpatesV(t, _result[0], j, sizeT); //verifica se também há empate no restante
                }
            }
        }

    }
    else{ //ordena shellsort
        int hp=0, cnt;
        t=ordenaShellV(t, sizeT); //ordena por pontos
        _result = verificaEmpatesV(t, i, j, sizeT); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){ //enquanto há empates
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){  //caso haja empates por numero de pontos
                    k=0;
                    hp=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    Table *taux = (Table*) malloc(k*sizeof(Table)); //cria uma table auxiliar
                    h1= _result[0]; h2= _result[k-1];
                    for(cnt=h1; cnt<=h2; cnt++){ //preenche table auxiliar
                        taux[hp] = t[cnt]; //tabela auxiliar recebe os elementos empatados da tabela
                        hp++;
                    }
                    taux=auxiliarS(taux, 0, hp-1, hp, ord);//ordena novamente por saldo de gols
                    hp=0;
                    for(cnt=h1; cnt<=h2; cnt++){ //recebe itens já ordenados da taux
                        t[cnt] = taux[hp]; //tabela recebe os elementos da tabela auxiliar
                        hp++;
                    }
                    free(taux);
                    _result[1] = -1; //só para entrar no prox if
                }
                 if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    _result[0] = h2+1; //inicio da ordenação será a partir do prox item
                    _result = verificaEmpatesV(t, _result[0], j, sizeT); //verifica se também há empate
                }
            }
        }

    }
    free(_result);
    return t;
}

Table* auxiliarS(Table* t, int i, int j, int sizeT, int ord){
    int k;
    int *_result; //variavel global
    static int h1, h2;
    _result = (int*) malloc(sizeT*sizeof(int));
    if(ord==1){ //ordena quicksort
        t=ordenaQuickS(t, i, j, sizeT); //caso haja empate, ordena por saldo de gols
        _result = verificaEmpatesS(t, i, j, sizeT); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){
                    k=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    h1= _result[0]; h2= _result[k-1];
                    t=auxiliarGP(t, _result[0], _result[k-1], sizeT, ord);//ordena novamente por gols pro
                    _result[1] = -1; //só para entra no prox if
                }
                //se result[1] == -1 quer dizer que não há mais empates
                if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    _result[0] = h2+1; //inicio da ordenação será a partir do prox item
                    _result = verificaEmpatesS(t, _result[0], j, sizeT); //verifica se também há empate
                }
            }
        }

    }
    else{//ordena shellsort
        int hp=0, cnt;
        t=ordenaShellS(t, sizeT); //ordena por pontos
        _result = verificaEmpatesS(t, i, j, sizeT); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){ //enquanto há empates
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){  //caso haja empates por numero de pontos
                    k=0;
                    hp=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    Table *taux = (Table*) malloc(k*sizeof(Table)); //cria uma table auxiliar
                    h1= _result[0]; h2= _result[k-1];
                    for(cnt=h1; cnt<=h2; cnt++){ //preenche table auxiliar
                        taux[hp] = t[cnt]; //tabela auxiliar recebe os elementos empatados da tabela
                        hp++;
                    }
                    taux=auxiliarGP(taux, 0, hp-1, hp, ord);//ordena novamente por gols pro
                    hp=0;
                    for(cnt=h1; cnt<=h2; cnt++){ //recebe itens já ordenados da taux
                        t[cnt] = taux[hp]; //tabela recebe os elementos da tabela auxiliar
                        hp++;
                    }
                    free(taux);
                    _result[1] = -1; //só para entrar no prox if
                }
                 if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    _result[0] = h2+1; //inicio da ordenação será a partir do prox item
                    _result = verificaEmpatesS(t, _result[0], j, sizeT); //verifica se também há empate
                }
            }
        }
    }
    free(_result);
    return t;
}

Table* auxiliarGP(Table* t, int i, int j, int sizeT, int ord){
    int k;
    int *_result; //variavel global
    static int h1, h2;
    _result = (int*) malloc(sizeT*sizeof(int));
    if(ord==1){//ordena quicksort
        t=ordenaQuickGP(t, i, j, sizeT); //caso haja empate, ordena por gol pró
        _result = verificaEmpatesGP(t, i, j, sizeT); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){
                    k=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    h1= _result[0]; h2= _result[k-1];
                    t=auxiliarA(t, _result[0], _result[k-1], sizeT, 0, ord);//ordena novamente pelo prox caractere
                    _result[1] = -1; //só para entra no prox if
                }
                //se result[1] == -1 quer dizer que não há mais empates
                if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    _result[0] = h2+1; //inicio da ordenação será a partir da prox palavra
                    _result = verificaEmpatesGP(t, _result[0], j, sizeT); //verifica se também há empate pelo prox caractere
                }
            }
        }

    }
    else{ //ordena shellsort
        int hp=0 , cnt;
        t=ordenaShellGP(t, sizeT); //ordena por pontos
        _result = verificaEmpatesGP(t, i, j, sizeT); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){ //enquanto há empates
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){  //caso haja empates por numero de pontos
                    k=0;
                    hp=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    Table *taux = (Table*) malloc(k*sizeof(Table)); //cria uma table auxiliar
                    h1= _result[0]; h2= _result[k-1];
                    for(cnt=h1; cnt<=h2; cnt++){ //preenche table auxiliar
                        taux[hp] = t[cnt]; //tabela auxiliar recebe os elementos empatados da tabela
                        hp++;
                    }
                    taux=auxiliarA(taux, 0, hp-1, hp, 0, ord);//ordena novamente por saldo de gols
                    hp=0;
                    for(cnt=h1; cnt<=h2; cnt++){ //recebe itens já ordenados da taux
                        t[cnt] = taux[hp]; //tabela recebe os elementos da tabela auxiliar
                        hp++;
                    }
                    free(taux);
                    _result[1] = -1; //só para entrar no prox if
                }
                 if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    _result[0] = h2+1; //inicio da ordenação será a partir do prox item
                    _result = verificaEmpatesGP(t, _result[0], j, sizeT); //verifica se também há empate
                }
            }
        }

    }
    free(_result);
    return t;
}

Table* auxiliarA(Table* t, int i, int j, int sizeT, int c, int ord){
    int k;
    int *_result;
    static int h1, h2;
    _result = (int*) malloc(sizeT*sizeof(int));

    if(ord==1){//ordena quicksort
        t=ordenaQuickA(t, i, j, sizeT, 0); //caso haja empate, ordena pela ordem alfabetica
        _result = verificaEmpatesA(t, i, j, sizeT, 0); //verifica se há empates (duas ou mais letras iguais)
        while(_result[0]<sizeT-1 && _result[0]!=-1){
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){
                    c++; //pega proxima letra da string
                    k=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    h1= _result[0]; h2= _result[k-1];
                    t=ordenaQuickA(t, _result[0], _result[k-1], sizeT, c);//ordena novamente pelo prox caractere
                }
                _result = verificaEmpatesA(t, h1, h2, sizeT, c); //verifica se também há empate pelo prox caractere
                //se result[1] == -1 quer dizer que não há mais empates
                if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    c=0; //começa novamente analisando primeiro caractere
                    _result[0] = h2+1; //inicio da ordenação será a partir da prox palavra
                    _result = verificaEmpatesA(t, _result[0], j, sizeT, c); //verifica se também há empate pelo prox caractere
                }
            }
        }
    }
    else{//ordena shellsort
        int hp=0, cnt;
        t=ordenaShellA(t, sizeT, 0); //ordena por pontos
        (*_result) = verificaEmpatesA(t, i, j, sizeT, 0); //verifica se há empates
        while(_result[0]<sizeT-1 && _result[0]!=-1){ //enquanto há empates
            while(_result[1] != -1){ //enquanto há empates
                if(_result[1]!= -1){  //caso haja empates por numero de pontos
                    c++; //pega prox caractere
                    k=0;
                    hp=0;
                    while(_result[k]!=-1 && k<sizeT){
                        k++; //verifica tamanho do vetor
                    }
                    Table *taux = (Table*) malloc(k*sizeof(Table)); //cria uma table auxiliar
                    h1= _result[0]; h2= _result[k-1];
                    for(cnt=h1; cnt<=h2; cnt++){ //preenche table auxiliar
                        taux[hp] = t[cnt]; //tabela auxiliar recebe os elementos empatados da tabela
                        hp++;
                    }
                    taux=ordenaShellA(taux, hp, c);//ordena novamente por saldo de gols
                    hp=0;
                    for(cnt=h1; cnt<=h2; cnt++){ //recebe itens já ordenados da taux
                        t[cnt] = taux[hp]; //tabela recebe os elementos da tabela auxiliar
                        hp++;
                    }
                    free(taux);
                     _result = verificaEmpatesA(t, h1, h2, hp, c);
                }
                 if(_result[1]== -1 && h2<=j){ //se não há empates nessa parte vai pro restante
                    c=0;
                    _result[0] = h2+1; //inicio da ordenação será a partir do prox item
                    _result = verificaEmpatesA(t, _result[0], j, sizeT, c); //verifica se também há empate
                }
            }
        }

    }

    free(_result);
    return t;
}

//algoritmo retirado do wikipedia ShellSort
Table* ordenaShellP(Table* tb, int sizeT){
    int i , j , value;
    Table aux;
    int h = 1;
    while(h < sizeT) {
        h = 3*h+1; //calcula valor de h
    }
    while ( h > 1) { //enquanto o intervalo é maior que 1
        h /= 3; //divide h
        for(i = h; i < sizeT; i++) { //ordena
            value = tb[i].pontos; //vai receber o h-ésimo elemento do vetor
            aux = tb[i];
            j = i - h; //j vai ser o índice do elemento que será comparado com value
            while (j >= 0 && value > tb[j].pontos) { //aqui é feita a troca de lugares entre os elementos
                tb [j + h] = tb[j]; //troca um elemento de lugar
                j -= h; //troca sinal de j para sair do while
            }
            tb [j + h] = aux; //troca o outro elemento de lugar
        }
    }
    return tb;
}


Table* ordenaShellV(Table* tb, int sizeT){
    int i , j , value;
    Table aux;
    int h = 1;
    while(h < sizeT) {
        h = 3*h+1; //calcula valor de h
    }
    while ( h > 1) { //enquanto o intervalo é maior que 1
        h /= 3; //divide h
        for(i = h; i < sizeT; i++) { //ordena
            value = tb[i].num_vitorias; //vai receber o h-ésimo elemento do vetor
            aux = tb[i];
            j = i - h; //j vai ser o índice do elemento que será comparado com value
            while (j >= 0 && value > tb[j].num_vitorias) { //aqui é feita a troca de lugares entre os elementos
                tb [j + h] = tb[j]; //troca um elemento de lugar
                j -= h; //troca sinal de j para sair do while
            }
            tb [j + h] = aux; //troca o outro elemento de lugar
        }
    }
    return tb;
}

Table* ordenaShellS(Table* tb, int sizeT){
     int i , j , value;
    Table aux;
    int h = 1;
    while(h < sizeT) {
        h = 3*h+1; //calcula valor de h
    }
    while ( h > 1) { //enquanto o intervalo é maior que 1
        h /= 3; //divide h
        for(i = h; i < sizeT; i++) { //ordena
            value = tb[i].saldo_gols; //vai receber o h-ésimo elemento do vetor
            aux = tb[i];
            j = i - h; //j vai ser o índice do elemento que será comparado com value
            while (j >= 0 && value > tb[j].saldo_gols) { //aqui é feita a troca de lugares entre os elementos
                tb [j + h] = tb[j]; //troca um elemento de lugar
                j -= h; //troca sinal de j para sair do while
            }
            tb [j + h] = aux; //troca o outro elemento de lugar
        }
    }
    return tb;
}

Table* ordenaShellGP(Table* tb, int sizeT){
     int i , j , value;
    Table aux;
    int h = 1;
    while(h < sizeT) {
        h = 3*h+1; //calcula valor de h
    }
    while ( h > 1) { //enquanto o intervalo é maior que 1
        h /= 3; //divide h
        for(i = h; i < sizeT; i++) { //ordena
            value = tb[i].gols_pro; //vai receber o h-ésimo elemento do vetor
            aux = tb[i];
            j = i - h; //j vai ser o índice do elemento que será comparado com value
            while (j >= 0 && value > tb[j].gols_pro) { //aqui é feita a troca de lugares entre os elementos
                tb [j + h] = tb[j]; //troca um elemento de lugar
                j -= h; //troca sinal de j para sair do while
            }
            tb [j + h] = aux; //troca o outro elemento de lugar
        }
    }
    return tb;
}

Table* ordenaShellA(Table* tb, int sizeT, int c){
     int i , j , value;
    Table aux;
    int h = 1;
    while(h < sizeT) {
        h = 3*h+1; //calcula valor de h
    }
    while ( h > 1) { //enquanto o intervalo é maior que 1
        h /= 3; //divide h
        for(i = h; i < sizeT; i++) { //ordena
            value = tb[i].time[c]; //vai receber o h-ésimo elemento do vetor
            aux = tb[i];
            j = i - h; //j vai ser o índice do elemento que será comparado com value
            while (j >= 0 && value < tb[j].time[c]) { //aqui é feita a troca de lugares entre os elementos
                tb [j + h] = tb[j]; //troca um elemento de lugar
                j -= h; //troca sinal de j para sair do while
            }
            tb [j + h] = aux; //troca o outro elemento de lugar
        }
    }
    return tb;
}


