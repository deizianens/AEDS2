#include <stdio.h>
#include <stdlib.h>
#include "Jogador.h" 

int* explorar (int t, Jogador jog[], int numJ){
	int *v; 
	v = (int*) malloc (10*sizeof(int)); //aloca 10 posiçoes de int na memoria 
	int i, p[2], h[8][2], aux; 
	
	p[0] = jog[numJ].posicao[0]; //p[0] recebe a coordenada x do jogador
	p[1] = jog[numJ].posicao[1]; //p[1] recebe a coordenada y do jogados		

	if(p[0]-1>=0 && p[1]-1>=0){ //verifica se a área da vizinhança é uma célula ou uma borda
		v[0] = jog[numJ].mapa[p[0]-1][p[1]-1];
		h[0][0]= p[0]-1;
		h[0][1]= p[1]-1;

	}
	else{ //se for uma borda, essa coordenada recebe valor 7 (denota bordas)
		v[0] = 7;	
	}
	
	if(p[0]-1>=0){  //verifica se a área da vizinhança é uma célula ou uma borda
		v[1] = jog[numJ].mapa[p[0]-1][p[1]];
		h[1][0]= p[0]-1;
		h[1][1]= p[1];

	}
	else{
		v[1] = 7;	
	}
	
	if(p[0]-1>=0 && p[1]+1<t){  //verifica se a área da vizinhança é uma célula ou uma borda
		v[2] = jog[numJ].mapa[p[0]-1][p[1]+1];
		h[2][0]= p[0]-1;
		h[2][1]= p[1]+1;
	}
	else{
		v[2] = 7;	
	}
	
	if(p[1]-1>=0){  //verifica se a área da vizinhança é uma célula ou uma borda
		v[3] = jog[numJ].mapa[p[0]][p[1]-1];
		h[3][0]= p[0];
		h[3][1]= p[1]-1;
	}
	else{
		v[3] = 7;
	}
	
	if(p[1]+1<t){  //verifica se a área da vizinhança é uma célula ou uma borda
		v[4] = jog[numJ].mapa[p[0]][p[1]+1];
		h[4][0]= p[0];
		h[4][1]= p[1]+1;
	}
	else{
		v[4]= 7;
	}
	
	if(p[0]+1<t && p[1]-1>=0){  //verifica se a área da vizinhança é uma célula ou uma borda
		v[5] = jog[numJ].mapa[p[0]+1][p[1]-1];
		h[5][0]= p[0]+1;
		h[5][1]= p[1]-1;
	}
	else{
		v[5] = 7;	
	}
	
	if(p[0]+1<t){  //verifica se a área da vizinhança é uma célula ou uma borda
		v[6] = jog[numJ].mapa[p[0]+1][p[1]];
		h[6][0]= p[0]+1;
		h[6][1]= p[1];
	}
	else{
		v[6] = 7;
	}
	
	if(p[0]+1<t && p[1]+1<t){ //verifica se a área da vizinhança é uma célula ou uma borda
		v[7] = jog[numJ].mapa[p[0]+1][p[1]+1];
		h[7][0]= p[0]+1;
		h[7][1]= p[1]+1;
	}
	else{
		v[7] = 7;
	}
	
	//coloca o aux (pivô) numa primeira posição diferente de 7 (7 é marcado como casa visitada ou borda)
	for(i=0; i<8; i++){ 
		if(v[i]!=7){
			aux=v[i];
			v[8]= h[i][0];
			v[9]= h[i][1];
			break;
		}
	}
	
	//verifica qual posição é a melhor para o jogador visitar
	for(i=1; i<8; i++){
		if(aux<v[i] && v[i]<7){
			aux = v[i];
			v[8]= h[i][0];
			v[9]= h[i][1];					
		}	
	}	
	
	return v;
}

void andar(int* exp, Jogador j[],  int numJ){	
	int i,k;

	//caso em que o jogador visita uma área com pokemons
	if(j[numJ].mapa[exp[8]][exp[9]]>0 && j[numJ].mapa[exp[8]][exp[9]]<6){ 
		if(j[numJ].pokebolas>0){ //caso em que o jogador tem pokebolas
			j[numJ].score+=j[numJ].mapa[exp[8]][exp[9]];
			j[numJ].poke++;
			j[numJ].pokemons = (int *) realloc (j[numJ].pokemons, j[numJ].poke*sizeof(int));
			j[numJ].pokemons[(j[numJ].poke)-1] = j[numJ].mapa[exp[8]][exp[9]];
			j[numJ].posicao[0] = exp[8];
			j[numJ].posicao[1] = exp[9];
			j[numJ].mapa[j[numJ].posicao[0]][j[numJ].posicao[1]] = 7;
			j[numJ].pokebolas--;
		} 
		else{//caso em que o jogador não tem pokebolas 
			j[numJ].posicao[0] = exp[8];
			j[numJ].posicao[1] = exp[9];
			j[numJ].mapa[j[numJ].posicao[0]][j[numJ].posicao[1]] = 7;
			
		}
	} //caso em que o jogador visita uma área com danos ou celula vazia
	else if(j[numJ].mapa[exp[8]][exp[9]]<=0){
		j[numJ].score+=j[numJ].mapa[exp[8]][exp[9]];
		j[numJ].posicao[0] = exp[8];
		j[numJ].posicao[1] = exp[9];
		j[numJ].mapa[j[numJ].posicao[0]][j[numJ].posicao[1]] = 7;

	}
	//caso em que o jogador visita um pokestop e não tem pokebolas
	else if(j[numJ].mapa[exp[8]][exp[9]]==6 && j[numJ].pokebolas==0){
		j[numJ].pokebolas++;
		j[numJ].posicao[0] = exp[8];
		j[numJ].posicao[1] = exp[9];
		j[numJ].mapa[j[numJ].posicao[0]][j[numJ].posicao[1]] = 7;
		
	}
	else{ //caso em que o jogador visita um pokestop mas ainda tem pokebolas
		j[numJ].posicao[0] = exp[8];
		j[numJ].posicao[1] = exp[9];
		j[numJ].mapa[j[numJ].posicao[0]][j[numJ].posicao[1]] = 7;
		
	}
	
	j[numJ].tamanho_caminho++; //aumenta o número de vezes que o jogador andou
		
	j[numJ].caminho = (int *) realloc (j[numJ].caminho, (j[numJ].tamanho_caminho*2)*sizeof(int)); //realoca o vetor caminho de acordo com 
	j[numJ].caminho[(j[numJ].tamanho_caminho*2)-2] =exp[8];									  // o numero de vezes que o jogador andou
	j[numJ].caminho[(j[numJ].tamanho_caminho*2)-1] =exp[9];	
	
}

Jogador* caminho_percorrido(Jogador j[], int numJ){
	int i;
	return j[numJ].caminho; //retorna o caminho percorrido
}

void pokemons_capturados(char pokelista[][10], Jogador j[], int numJ){
	int i,k;
	
	printf("\nJOGADOR: %s\n",j[numJ].nome);
	for(i=0; i<j[numJ].poke; i++){
		k= j[numJ].pokemons[i];
		printf("%s\n", pokelista[k]);  //imprime o nome dos pokemons capturados
	}
	
}
