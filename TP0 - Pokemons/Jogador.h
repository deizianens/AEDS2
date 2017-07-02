// definição do tipo
typedef struct jogador {
 	char nome[3];
 	int score;
 	int *pokemons;
 	int poke; //marca quantos pokemons foram capturados
 	int posicao[2];
 	int pokebolas;
 	int *caminho;
 	int **mapa;
 	int tamanho_caminho;
} Jogador;

// cabeçalho das funções
int* explorar (int, Jogador[], int);
void andar(int*, Jogador[],  int);
Jogador* caminho_percorrido(Jogador[], int);
void pokemons_capturados(char [][10], Jogador[], int);
