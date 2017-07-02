#include <stdio.h>
#include <stdlib.h>
#include "Jogador.h" 

#define MARKED 7; //constante que denota celula visitada
 
int main(int argc, char *argv[]) {
	
	FILE *file;
	file = fopen("entrada.txt", "r"); //lê o arquivo entrada
	
	int t_matriz, numJog, i, j, jog, aux, k, winner, win; //t_matriz = tamanho da matriz
	char t;
	
	fscanf(file,"%i", &t_matriz); //lê o tamanho da matriz
	
	int m[t_matriz][t_matriz]; //cria uma matriz quadrada
	
	for(i=0; i<t_matriz; i++){
		for(j=0; j<t_matriz; j++){
			fscanf(file, "%i", &m[i][j]); //preenche o mapa com os valores do arquivo		
		}
	}

	fscanf(file, "%i", &numJog); //lê numero de jogadores	
	
	Jogador player[numJog]; //cria um vetor de Jogadores
	
	//cada jogador terá uma copia do mapa
	for(k=0; k<numJog; k++){
		player[k].mapa = (int **) malloc(t_matriz*sizeof(sizeof(int *))); //alocação do vetor principal
		for(i=0;i<t_matriz;i++){
			player[k].mapa[i] =(int *) malloc(t_matriz*sizeof(int)); //alocação de cada vetor linha
		}
	}
	
	//faz a atribuição dos valores do mapa lidos anteriormente pra cada um dos mapas do TAD
	for(k=0; k<numJog; k++){
		for(i=0; i<t_matriz; i++){
			for(j=0; j<t_matriz; j++){
				player[k].mapa[i][j] = m[i][j]; //copia o mapa lido pro mapa do TAD Jogador 	
			}
		}
	}
	
	for(i=0; i<numJog; i++){
		
		fscanf(file, " %[^:]:", &player[i].nome); //lê o nome do jogador e armazena no TAD Jogador
		//printf("Jog: %s\n", player[i].nome);
		for(j=0; j<2; j++){
			fscanf(file, "%d", &player[i].posicao[j]); //lê a posição inicial do jogador e armazena num vetor 
					
			if(t!='0'){
				fscanf(file, "%c", &t); //pega o \n
				t='0';
			}			
		}
		t='1'; 
		printf("\n");
	}
		
	fclose(file); //fecha o arquivo entrada.txt 
	
	//faz todas as atribuições iniciais aos jogadores	
	for (i=0; i<numJog; i++){
		player[i].pokebolas= 3; //atribui 3 pokebolas a todos os jogadores
		player[i].poke=0; //poke=numero de pokemons capturados
		player[i].score=0; //todos os jogadores iniciam com score 0
		player[i].pokemons = (int *) malloc (1*sizeof(int)); //aloca espaço pro ponteiro de pokemons (1=numero aleatorio inicial)
		player[i].caminho = (int *) malloc (2*sizeof(int)); //aloca espaço pro ponteiro de caminho percorrido (2 pra armazenar a primeira posição x e y)
		player[i].caminho[0]= player[i].posicao[0];
		player[i].caminho[1]= player[i].posicao[1];
		
		//verifica se existe um pokemon, pokestop ou area de dano na posição inicial
		if(player[i].mapa[player[i].posicao[0]][player[i].posicao[1]] != 6){ //se não for pokestop
			
			if(player[i].mapa[player[i].posicao[0]][player[i].posicao[1]] >0){ //se for um pokemon
				player[i].poke=1; //se pegar um pokemon, poke=1
				player[i].pokemons[0] = player[i].mapa[player[i].posicao[0]][player[i].posicao[1]]; //pokemon recebe o cp do pokemon capturado
				player[i].pokebolas--; 	
			}
			
			player[i].score = player[i].mapa[player[i].posicao[0]][player[i].posicao[1]]; //atribui ao score o cp do pokemon capturado
			player[i].mapa[player[i].posicao[0]][player[i].posicao[1]] = MARKED; //marca a posição como visitada (marked vai servir como flag de visitada)
			
		}
		else{ //se for um pokestop, apenas marca a posição como visitada
			player[i].mapa[player[i].posicao[0]][player[i].posicao[1]] = MARKED;
		}	
	}
	
	//cria array com o nome dos pokemons (vazia não é um pokemon, apenas denota que a posição 0 corresponde ao cp 0(celula vazia))
	char pokedex[][10] = {"Vazia", "Dragonite", "Alakazan", "Magma", "Eevee", "Pikachu"};
		
	//cria um ponteiro int que recebe os vetores das funções
	int *exp;
	Jogador *c; 
	//função Explorar retorna tudo que está na vizinhança do jogador(8) e a melhor posição da vizinhança(2), portanto 10 números
	exp = (int *) malloc (10*sizeof(int));
	
	//executa as jogadas de cada jogador
	for(k=0; k<numJog; k++){
		player[k].tamanho_caminho=1; //atribui 1 ao tamanho do caminho percorrido pelo jogador (1 pq a posição inicial conta como caminho)	
	
		for(i=0; i<(t_matriz*3); i++){ //loop roda até 3N-1 onde N é o tamanho do mapa
			
			//chama função explorar para mostrar vizinhos e a melhor posição para andar 
			exp = explorar(t_matriz, &player, k); //tem como parametros o tamanho do mapa, o TAD jogador, e o numero do jogador da rodada
					
			aux=0; 
			//verifica se toda a vizinhança já foi visitada incrementando aux toda vez que o valor de uma célula for 7 (celula visitada ou borda)
			for(j=0; j<8; j++){ 
				if(exp[j]==7){  
					aux++; 
				}
			}
						
			if(aux==8){ //caso o aux seja igual a 8 sai do loop (caso em que o jogador não pode mais se mover)
				break; 
			}
			else{ //caso ainda tenha celulas pra visitar
				
				 andar(exp, &player, k); //função andar recebe o vetor retornado em explorar, TAD Jogador e numero do jogador da rodada
				
			}
			c = (Jogador *) malloc (player[k].tamanho_caminho*sizeof(Jogador)); 
			c = caminho_percorrido(&player, k); //retorna o caminho (não precisa ser executada obrigatoriamente)
			pokemons_capturados(pokedex, &player, k);
		}
			
	free(exp); //libera malloc
	}
	

	file = fopen("saida.txt", "w"); //cria um arquivo de saida
	for(i=0; i<numJog; i++){
		fprintf(file, "%s %d ", player[i].nome, player[i].score);
		for(j=0; j<(player[i].tamanho_caminho*2); j+=2){
			fprintf(file, "%d,%d ", player[i].caminho[j], player[i].caminho[j+1]);
		}
		fprintf(file, "\n");	
	}
	
	t=0;
	winner= player[0].score;
	win= 0;
	int help[numJog], aux2, help2[numJog];
	
	for(i=1; i<numJog; i++){
		if(winner<player[i].score){ //verifica qual jogador possui o maior score
			winner=player[i].score; //winner recebe o maior score
			help[0] = i; //help na posição 0 recebe o indice do jogador com maior score
		}
	}
	
	//verifica se tem algum score igual ao vencedor
	for(i=0; i<numJog; i++){
		if(winner==player[i].score){
			help[t]= i; //recebe os indices dos jogadores empatados (caso haja)
			t++;//caso tenha algum score igual ao vencedor, incrementa t (caso t for incrementado + de duas vezes, os scores são iguais)			
		}		
	}
	
	if(t>1){ //caso de empate de score, verifica os pokemons de maior cp de cada jogador
		int poke_maior[t-1];
			
		for(aux=5; aux>0; aux--){

			for(i=0;i<t; i++){
				poke_maior[i]=0; //preenche todas as posiçoes com 0;	
			}
			
			for(i=0; i<t; i++){
				for(j=0; j<player[help[i]].poke; j++){
					if(player[help[i]].pokemons[j]==aux){ //verifica quantos pokemons de score 5, 4, 3, 2, 1 cada jogador tem
						poke_maior[i]++;
					}
				}
			}
			
			winner=poke_maior[0];
			for(i=1; i<t; i++){
				if(winner<poke_maior[i]){
					winner=poke_maior[i]; //compara qual jogador tem o maior numero de pokemons daquele score
					help2[0]=i;
				}
			}
			
			aux2=t;
			t=0;
			for(i=0; i<aux2; i++){
				if(winner==poke_maior[i]){
					help2[t] = help[i]; //recebe os indices dos jogadores empatados (caso haja)
					t++; //t>1 se houver empates
				}
			}
			
			if(t==1){
				break; //se não houver empates, sai do loop
			}
	
		}
	}	
	
	if(t>1){//caso ainda haja empate de pokemons de maior CP, verifica o menor caminho
		winner= player[help2[0]].tamanho_caminho;
	
		for(i=1;i<t; i++){
			if(winner>player[help2[i]].tamanho_caminho){
				winner=	player[help2[i]].tamanho_caminho; //encontra o menor caminho
			}
		}
		
		aux2=t;
		t=0;
		for(i=0;i<aux2; i++){
			if(winner==player[help2[i]].tamanho_caminho){
				help2[t]= player[help2[i]].tamanho_caminho;
				t++; //caso tenha algum caminho do mesmo tamanho do menor caminho, t será incrementado mais de uma vez, caso não tenha, t=1;
			}
		}
		
		//imprime o(s) vencedor(es)
		fprintf(file, "VENCEDOR: %s", player[help[0]].nome); //imprime o nome do vencedor no arquivo
		for(i=1; i<t; i++){
			fprintf(file, " %s", player[help[i]].nome); //caso haja mais de um vencedor, imprime todos
		}
	}
	
	else{
		fprintf(file, "VENCEDOR: %s", player[help[0]].nome); //imprime o nome do vencedor no arquivo
		for(i=1; i<t; i++){
			fprintf(file, " %s", player[help[i]].nome); //caso haja mais de um vencedor, imprime todos
		}
			
	}
	
	fclose(file);
	free(c);
	return 0;
}
