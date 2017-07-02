#ifndef FUTEBOL_TABELACLASSIFICACAO_H
#define FUTEBOL_TABELACLASSIFICACAO_H

typedef struct table {
    char time[50];
    int pontos;
    int num_vitorias;
    int saldo_gols;
    int gols_pro;

}Table;

Table* criaTable(int sizeT);
void insere2(Table* t, char* time1, char* time2, int p1, int p2, int ord, int size);
void imprimeTabela(Table* t, int sizeT, int rod);
Table* ordenaQuickP(Table* t, int i, int j, int sizeT);
int particionaQuickP(Table* t, int i, int j);
Table* ordenaQuickV(Table* t, int i, int j, int sizeT);
int particionaQuickV(Table* t, int i, int j);
Table* ordenaQuickS(Table* t, int i, int j, int sizeT);
int particionaQuickS(Table* t, int i, int j);
Table* ordenaQuickGP(Table* t, int i, int j, int sizeT);
int particionaQuickGP(Table* t, int i, int j);
Table* ordenaQuickA(Table* t, int i, int j, int sizeT, int c);
int particionaQuickA(Table* t, int i, int j, int c);
Table* auxiliarP(Table* t, int i, int j, int sizeT, int ord);
Table* auxiliarV(Table* t, int i, int j, int sizeT, int ord);
Table* auxiliarS(Table* t, int i, int j, int sizeT, int ord);
Table* auxiliarGP(Table* t, int i, int j, int sizeT, int ord);
Table* auxiliarA(Table* t, int i, int j, int sizeT, int c, int ord);
int* verificaEmpatesP(Table* t, int i, int j, int sizeT);
int* verificaEmpatesV(Table* t, int i, int j, int sizeT);
int* verificaEmpatesS(Table* t, int i, int j, int sizeT);
int* verificaEmpatesGP(Table* t, int i, int j, int sizeT);
int* verificaEmpatesA(Table* t, int i, int j, int sizeT, int c);
Table* ordenaShellP(Table* tb, int sizeT);
Table* ordenaShellV(Table* tb, int sizeT);
Table* ordenaShellS(Table* tb, int sizeT);
Table* ordenaShellGP(Table* tb, int sizeT);
Table* ordenaShellA(Table* tb, int sizeT, int c);


#endif //FUTEBOL_TABELACLASSIFICACAO_H
