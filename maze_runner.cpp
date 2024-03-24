#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

// Matriz de char representnado o labirinto
char** maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento: 

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos: 
//    valid_positions.size();
// 
// Retornar o elemento no topo: 
//  valid_positions.top(); 
// 
// Remover o primeiro elemento do vetor: 
//    valid_positions.pop();


// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	// Abre o arquivo para leitura (fopen)
	FILE *map_file = fopen(file_name,"r");

	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols
	fscanf(map_file, "%d %d", &num_rows, &num_cols);

	
	// Aloca a matriz maze (malloc)
	maze = (char **)malloc(num_rows * sizeof(char *));

	// Aloca cada linha da matriz
	for (int i = 0; i < num_rows; ++i)
		maze[i] = (char *)malloc(num_cols * sizeof(char));
	
	char temp;
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			do{
				temp = fgetc(map_file);
			}while(temp != 'x' && temp != '#' && temp != 'e' && temp != EOF);
			maze[i][j] = temp;

			// Se o valor for 'e' salvar o valor em initial_pos
			if (maze[i][j] == 'e')
				initial_pos = {i,j};
		}
	}
	return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}


// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {
	pos_t current = pos;
	pos_t evaluating = {0,0};
	
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
	while(1){

		maze[current.i][current.j] = '.'; 
		// Marcar a posição atual com o símbolo '.'
		for (int i = 0; i < num_rows; ++i) {
			for (int j = 0; j < num_cols; ++j) {
				if (maze)
				maze[i][j] = '.';
			}
		}
		// Limpa a tela
		system("clear");
		// Imprime o labirinto
		void print_maze();
		
		/* Dado a posição atual, verifica quais sao as próximas posições válidas
			Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		 	e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		 	cada uma delas no vetor valid_positions
		 		- pos.i, pos.j+1
		 		- pos.i, pos.j-1
		 		- pos.i+1, pos.j
		 		- pos.i-1, pos.j
		 	Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
	 	*/

		if (pos.j+1 < num_cols){
			evaluating = {pos.i, pos.j + 1};
			valid_positions.push(evaluating);
		}
		if (pos.j-1 > 0){
			evaluating = {pos.i, pos.j - 1};
			valid_positions.push(evaluating);
		}
		if (pos.i+1 < num_rows){
			evaluating = {pos.i + 1, pos.j};
			valid_positions.push(evaluating);
		}

		if (pos.i-1 > 0){
			evaluating = {pos.i - 1, pos.j};
			valid_positions.push(evaluating);
		}



		
	
		// Verifica se a pilha de posições esta vazia 
		if (valid_positions.size() == 0){
			// Caso afirmativo, retornar falso
			return false;
		}else{
			//Caso esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
		
			current = valid_positions.top();
			valid_positions.pop();
			walk(current);
		}

	}
	return false;
}

int main(int argc, char* argv[]) {
	printf("start\n\n");

	// carregar o labirinto com o nome do arquivo recebido como argumento
	//pos_t initial_pos = load_maze(argv[1]);
	pos_t initial_pos = load_maze("../data/maze2.txt");
	

	print_maze();

	// chamar a função de navegação
	bool exit_found = walk(initial_pos);
	
	// Tratar o retorno (imprimir mensagem)
	if (exit_found){
		printf("Tem saida!\n");
	}else{
		printf("Deu ruim...\n");
	}
	
	return 0;
}
