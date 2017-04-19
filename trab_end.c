/*
######################################################################
########	Universidade de Brasilia
########	Instituto de Ciencias Exatas
########	Departamento de Ciencia da Computacao
########	Algoritmos e Programação de Computadores – 1/2016
########	Aluno(a): Leonardo Maffei da Silva
########	Matricula: 160033811
########	Turma: A
########	Versão do compilador: GCC 5.3.1
########	Descricao:/implementacao do jogo "EliminaLetras", jogo baseado no classico Bubble Breaker
#######################################################################
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>	/*Apenas para uso da funcao "toupper", que converte letra minuscula para maiuscula*/
#include <string.h>
#include <math.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
typedef struct {
char nick[21];
int score;
int antiguidade;
}Player;


FILE *fp;					/*Ponteiro para arquivo texto*/
FILE *fp2;					/*Ponteiro para arquivo bin.*/

char letras[11], matriz[10][10];;			 /* caracteres para preencher a matriz do jogo */
int linhas, colunas, elementos=0; 					/* dimensoes da matriz */
double base_pontos;						/* base para a pontuacao no jogo */
int pontuacao=0;
Player estrutura[12];
/*Acima estão as unicas variaveis globais do jogo*/

/*Logo abaixo estao as declarações previas dos procedimentos.*/
/*Motivo: não se preocupar com a ordem entre eles quando forem criados*/
void valida_nome();
void cria_ranking();
int checa_ranking();
void apaga();
int valida_confirma();
int valida_coluna();
int valida_linha();
void despedida();
void atualiza_score(int adicionar, int *elementos);
void restaura(char letra);
void mudabase();
void mudacolunas();
void mudaletras();
void mudalinhas();
void JOGAR();
void RANKING();
void welcome();
void Menuprincipal();
void settingsmenu();
void cria();
void checa();
void direita(int linha, int coluna, char letra);
void acima( int linha, int coluna, char letra);
void abaixo(int linha, int coluna, char letra);
void esquerda(int linha, int coluna, char letra);
void busca(int linha, int coluna, char letra);
void desce();
int translada();
void lematrizchar();
void imprimematrizoada();
void geramatrix();
int valida_linhas();
int valida_colunas();
int ordena_ranking(const void * generico1, const void * generico2);
int exixte();
/*Esta função faz  a busca 'primária': busca, basicamente, todos os elementos que tem fronteira com um elemento a[linha][coluna]*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////*/
/*Primeiro passo: veririficar se o arquivo "EliminaLetras_settings.txt" ja existe* e craia-lo ser preciso for.*/
int main() {

	checa_ranking();
	fp = fopen("EliminaLetras_settings.txt", "r+");
	if(fp == NULL)	/*Não existe arquivo settings*/
		cria();				
	else 
		checa();
	welcome();				/*Mostra a mensagem Inicial. Sai somente quando <ENTER> for teclado*/
	Menuprincipal();			/*Mostra o menu na tela*/	
	despedida();
	fclose(fp2);
	return 0;
}
/************************Abaixo estao os procedimentos************************8*/
/*#############################################################################*/
/*#############################################################################*/

void RANKING(){
	int i;
	system(CLEAR);
	fp2 = fopen("Eliminaletras_ranking.bin", "rb");
	if(fp2 != NULL )
		{
			fread(estrutura, sizeof(Player) ,12 , fp2);
			if(estrutura[0].score != 0)
			{
				printf("==========================================\n");
				printf("========== EliminaLetras RANKING =========\n");
				printf("==========================================\n");
				for(i=0; i<9 && estrutura[i].score != 0;i++)
					printf("   %d - %-20s%d\n", i+1, estrutura[i].nick, estrutura[i].score);		/*o '-' serve para alinhar em relacao a esquerda*/
				if(estrutura[i].score != 0)				
					printf("  llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll%d - %-20s%d\n", i+1, estrutura[i].nick, estrutura[i].score);		/*o '-' serve para alinhar em relacao a esquerda*/				
				printf("Remover o ranking atual? (S/N) ");
			if( valida_confirma()> 0)
				{
					system(CLEAR);
					cria_ranking();
					printf("O ranking esta vazio.\nVoce sera redirecionado para o MenuPrincipal.\n");
					while(getchar() != '\n');
				}	

			}
			else
				{
					printf("Ranking vazio. Seja o primeiro a jogar!!!\n");
					getchar();
				}
	}			
	else
		{
		printf("Nao existe ranking.\nTecle <ENTER> para continuar...");
		cria_ranking();	
	}

}				
void welcome(){
	system(CLEAR);
	printf("==================================\n");
	printf("=== Bem-Vindo a EliminaLetras! ===\n");
	printf("==================================\n");
	printf("Aperte <ENTER> para continuar...\n\n");
	getchar();
	system(CLEAR);
}

void Menuprincipal(){
	char opcao[1000];
	int tamanho;
	while(opcao[0] != '4'){	
		opcao[0] = '0';
		system(CLEAR);
		printf("=====================================\n");
		printf("=== EliminaLetras MENU PRINCIPAL ===\n");
		printf("=====================================\n\n");
		printf("1 - Jogar\n");
		printf("2 - Ranking\n");
		printf("3 - Configuracoes\n");
		printf("4 - Sair\n");
		printf("Escolha uma opcao:");
		scanf("%[^\n]",opcao);
		getchar();
		tamanho = strlen(opcao);
		if(tamanho == 1)
			
			{
				if(opcao[0] == '1')
						JOGAR();
				else if (opcao[0] == '2')
						RANKING();
				else if (opcao[0] == '3')
						settingsmenu();				
				else if(opcao[0] != '4')
				{
					printf("Opcao invalida\nTecle <ENTER> para continuar...\n");
					getchar();
				}	
			}
			else
				{
					printf("Opcao invalida\nTecle <ENTER> para continuar...\n");
					getchar();
				}
			if(opcao[0] != '4')
				opcao[0] = '0';			/*Garante que */			
	  }
}
void settingsmenu(){
	int tamanho;
	char flag;
	char opcao[1000];
	printf("\n");
do{	
	system(CLEAR);
	printf("==========================================\n");
	printf("=== EliminaLetras MENU DE CONFIGURACOES ===\n");
	printf("==========================================\n\n");
	printf("1 - Mudar caracteres: %s\n2 - Mudar linhas: %d\n3 - Mudar colunas: %d\n4 - Mudar pontuacao base: %.4f\n", letras, linhas, colunas, base_pontos);
	printf("5 - Menu principal\nDigite uma opcao VALIDA: ");
	scanf("%[^\n]", opcao);
	getchar();
	tamanho = strlen(opcao);						/*O tamanho da string lida deve ser igual a '1'.*/
	if(tamanho == 1)
		{
			checa();
				if(opcao[0] == '1')
					mudaletras();
				else if (opcao[0] == '2')
					mudalinhas();
				else if (opcao[0] == '3')
					mudacolunas();
				else if (opcao[0] == '4')
					mudabase();
				else if(opcao[0] == '5')
					flag = '0';
				else
					{
						printf("Opcao invalida\nTecle <ENTER> para continuar...\n");
						getchar();
					}
		
		}
	else
		{
			printf("Opcao invalida\nTecle <ENTER> para continuar...\n");
			getchar();
		}		
	}while(flag != '0');
}

int checa_ranking(){
	fp2 = fopen("Eliminaletras_ranking.bin", "rb");
	if(fp2 == NULL)
			cria_ranking();
	else	
	{	
		fread(estrutura, sizeof(Player) ,12 , fp2);	
		qsort(estrutura,12, sizeof(Player), ordena_ranking);
		fp2 = fopen("Eliminaletras_ranking.bin", "wb");
		fwrite(estrutura, sizeof(Player) ,10 , fp2);
		fclose(fp2);
	}	
	return 1;
		
}
void cria_ranking(){
	int i;
	fp2 = fopen("Eliminaletras_ranking.bin", "wb");
	for(i=0; i < 10; i++)
	{
		strcpy(estrutura[i].nick,"\0");
		estrutura[i].score = 0;
		estrutura[i].antiguidade = 999 - i;
	}
	rewind(fp2);
	fwrite(estrutura, sizeof(Player), 12, fp2);


}

int ordena_ranking(const void * generico1, const void * generico2){

	Player *esquerda = (Player *)generico1;
	Player *direita = (Player *)generico2;

	if(esquerda->score > direita->score)	/*Vai trocar as posições APENAS se o da esquerda for menor*/
    	return -1;
  	
  	if(esquerda->score < direita->score)
    	return 1;

	if(esquerda->antiguidade > direita->antiguidade)
		return -1; 
	else
		return 1;
}

void cria(){
	fp = fopen("EliminaLetras_settings.txt", "w+");								/*Abre/Cria arquivo para leitura E gravacao*/	letras[0] = 'O';
	strcpy(letras, "OZXM");
	linhas = 6;
	colunas = 9;
	base_pontos = 1.5;
	fprintf(fp,"%s\n%d\n%d\n%f", letras, linhas, colunas, base_pontos);
	fclose(fp);
}

void checa(){
	fp = fopen("EliminaLetras_settings.txt", "r+");
	if(	fp == NULL)
		cria();
	else													/*Checa se os dados das configuracoes estao 'corretos'*/
	{
		fscanf(fp, "%s%d%d%lf", letras, &linhas, &colunas, &base_pontos);	
		rewind(fp);
		if(strlen(letras) > 9 || strlen(letras) < 3)
			strcpy(letras,"OZMX");
		if(linhas > 9 || linhas < 3)
			linhas = 6;
		if(colunas>9 || colunas < 3)
			colunas = 9;
		if(base_pontos > 2 || base_pontos < 1)
			base_pontos= 1.5;
		fprintf(fp, "%s\n%d\n%d\n%f", letras, linhas, colunas, base_pontos);
		fclose(fp);
	}
}

void mudaletras(){
	char temp_letras[11], tamanho;
	printf("Insira os novos caracteres (min.3, max 10):___");
	scanf("%s", temp_letras);
	getchar();
	tamanho = strlen(temp_letras);
	if (tamanho<3 || tamanho > 10)
	{
	printf("Opcao invalida. Tecle <ENTER> PARA CONTINUAR...\n");
	getchar();
	}
	else
	{	
		printf("Confirmar acao?\nTecle qualquer coisa diferente de 's'\n para 'Nao' e 's' para sim\n");
					
		if (valida_confirma() > 0)
		{
		fp = fopen("EliminaLetras_settings.txt", "r+");
		strcpy(letras, temp_letras);
		fprintf(fp,"%s\n%d\n%d\n%.4f", letras, linhas, colunas, base_pontos);
		fclose(fp);
		}	
	}
}

void mudalinhas(){
	int temp_linhas;
	printf("Insira a quantidade de linhas para a matriz (min.3, max 9):___");
	scanf("%d", &temp_linhas);
	getchar();
	if (temp_linhas < 3 || temp_linhas > 9)
	{
		printf("Opcao invalida. Tecle <ENTER> PARA CONTINUAR...\n");
		getchar();
				
	}
	else
	{	
		printf("Confirmar acao?\nTecle 's' para sim e qualquer outra coisa para nao.\n");
		if(valida_confirma() > 0)
		{	
		linhas = temp_linhas;
		fp = fopen("EliminaLetras_settings.txt", "r+");
		fprintf(fp,"%s\n%d\n%d\n%.4f", letras, linhas, colunas, base_pontos);
		fclose(fp);						
		}
	}
}

void mudacolunas(){
	int temp_colunas;
	printf("Insira a quantidade de colunas para a matriz (min.3, max 9):___");
	scanf("%d", &temp_colunas);
	getchar();
	if (temp_colunas < 3 || temp_colunas > 9)
	{
		printf("Opcao invalida. Tecle <ENTER> PARA CONTINUAR...\n");
		getchar();
	}
	else
	{	
		printf("Confirmar acao?");
		if(valida_confirma() > 0)
		{
			colunas = temp_colunas;
			fp = fopen("EliminaLetras_settings.txt", "r+");
			fprintf(fp,"%s\n%d\n%d\n%.4f", letras, linhas, colunas, base_pontos);
			fclose(fp);
		}	
	}
}

void mudabase(){
	int aux;
	double temp_base_pontos;
	printf("Digite a nova pontuação base (min.1, max 2):___");
	scanf("%lf", &temp_base_pontos);
	getchar();
	if (temp_base_pontos <= 1.000000 || temp_base_pontos > 2)
	{
		printf("\nOpcao invalida. Tecle <ENTER> PARA CONTINUAR...\n");
		getchar();
	}
	else
	{	
	printf("Confirmar acao?\nTecle 's' para sim ou qualquer outra coisa\npara nao.\n ");
	aux = valida_confirma();
	if(aux > 0)
		{	
		base_pontos = temp_base_pontos;
		fp = fopen("EliminaLetras_settings.txt", "r+");										/*Reposiciona o ponteiro no inicio do arquivo*/
		fprintf(fp,"%s\n%d\n%d\n%f", letras, linhas, colunas, base_pontos);
		fclose(fp);		
		}
	
	else
		{
			if(aux == -2)
			{
				printf("Opcao invalida.\nTecle <ENTER> para continuar...\n");
				getchar();
				system(CLEAR);
			}
			else
				system(CLEAR);
			
		}
	}
}

void JOGAR(){

	int adicionar;
	int linha, coluna, aux, flag=1000;
	char  letra, flag_master = '1';
	system(CLEAR);
	geramatrix();
	valida_nome();										/*Pede pra inserir o nome*/
	imprimematrizoada();
    do{	
    	aux = 100;
    	if(matriz[linhas -1][colunas-1] == ' ')
    		{
    			flag_master = '0';
    			system(CLEAR);
    			printf("Sua pontuacao neste jogo foi: %d pontos.\n", pontuacao);							/*O elemento mais inferior para a direita ser zero significa que o programa acabou*/
    			estrutura[11].score = pontuacao;
    			pontuacao = 0;
    			checa_ranking();																			/*Salva o valor no ranking, se houver espaco*/
    			printf("Tecle <ENTER> para continuar...\n");
    			while(getchar() != '\n');
			}
		else
		{
				system(CLEAR);
				system(CLEAR);
				imprimematrizoada();
				printf("\n                       Sua pontuacao ATUAL eh: %d\n", pontuacao);
				printf("Digite o nummero da linha (min.1, max %d): ", linhas);
				printf("\n");
				if((linha = valida_linha()) >= 0)
					{	linha--;
						printf("Digite o nummero da coluna (min.1, max %d): ", colunas);					
						if((coluna = valida_coluna()) >= 0)
							{	coluna--;
								if(matriz[linha][coluna] != ' ')
									{	
										system(CLEAR);
										system(CLEAR);
										letra = matriz[linha][coluna];
										busca(linha, coluna, letra);
										imprimematrizoada();
										adicionar = (int)ceil(pow(base_pontos, elementos));
										printf("Letra selecionada: %c\n", letra);
										printf("Sua pontuacao com esta jogada eh: %.d\n", adicionar);
										elementos=0;
										printf("Confirme sua jogada.(S/N) ");
										if(valida_confirma() > 0)
										{	
											apaga();
											atualiza_score(adicionar, &elementos);
											desce();
											while( aux != 0)
												aux = translada();
											
										}
										else
											restaura(letra);
									}
								else
									flag = 3;	
							}
					}

				if(flag == 3)
				{
					printf("Espaco vazio!\nSelecione uma opcao valida.\n"); 
					printf("Tecle <ENTER> para continuar...\n");
					getchar();
					
				}
				flag = 22;

		}
	}while(flag_master != '0');
}

/*void lematrizchar(){				Funcao usada para testar o codigo antes de se usar a funcao rand

	printf("Digite a matriz, caractere a caractere, seguido de enter a cada entrada.\n");
	int a,b;
	for(a=0; a < linhas; a++)
	{
		for(b=0; b < colunas; b++)
		{
			scanf(" %c", &matriz[a][b]);
			getchar();
			printf("%c\n", matriz[a][b]);
		}
	}
}*/

void imprimematrizoada(){		/*Vai printar amatriz com os indices indicando linhas e colunas*/
	int a,b;
	printf("   ");
	for(a=0; a < colunas;a++)
		printf("%d", a+1);
	printf("\n");

	printf("   ");
	for(a=0; a < colunas;a++)
		printf("|");
	printf("\n");

	for (a=0; a < linhas; a++)
	{	printf("%d -", a+1);
		for(b=0; b < colunas-1; b++)
		{	printf("%c", matriz[a][b]);
		}
		printf("%c- %d\n", matriz[a][b], a+1);
	}

	printf("   ");
	for(a=0; a < colunas;a++)
		printf("|");
	printf("\n");

	printf("   ");
	for(a=0; a < colunas;a++)
		printf("%d", a+1);
	printf("\n");

}

void acima( int linha, int coluna, char letra){
	if(letra == matriz[linha-1][coluna])		/*Compara com o de cima*/
		matriz[linha-1][coluna] = '*';		
	
}
void abaixo( int linha, int coluna, char letra){
	if(letra == matriz[linha+1][coluna])		/*Compara com o de baixo*/
		matriz[linha+1][coluna] = '*';
}	

void direita( int linha, int coluna, char letra){
	if(letra == matriz[linha][coluna+1])		/*Compara com o da direita*/
		matriz[linha][coluna+1] = '*';
}

void esquerda( int linha, int coluna, char letra){

	if(letra == matriz[linha][coluna-1])		/*Compara com o da esquerda*/
		matriz[linha][coluna-1] = '*';
	
}
	
void busca( int linha, int coluna, char letra){
	elementos++;
	matriz[linha][coluna] = '*';
	if(letra == matriz[linha-1][coluna])		/*Compara com o de cima*/
		busca(linha-1, coluna, letra);
	if (letra == matriz[linha][coluna-1])		/*Compara com o da esquerda*/
		busca(linha, coluna-1, letra);
	if(letra == matriz[linha+1][coluna])
		busca(linha+1, coluna, letra);
	if(letra == matriz[linha][coluna+1])
		busca(linha, coluna+1, letra);				
}

void apaga(){			
	int i, j;
	for(i=0; i<linhas;i++)
			for(j=0; j<colunas;j++)
					if(matriz[i][j] == '*')
						matriz[i][j] = ' ';											
}

void desce(){									/*Desce os elementos de uma coluna*/
	int i, j, flag=1,cont=1;
	while(flag == 1)							/*Flag indicativa: houve ou nao troca?*/
		{	flag = 0;
			for(i=linhas -1; i >0;i--)					
				for(j=0; j < colunas; j++)
					if(matriz[i][j] == ' ' && matriz[i-1][j] != ' ')
					{	cont++;
						matriz[i][j] = matriz[i-1][j];
						matriz[i-1][j] = ' ';
						flag = 1;
					}		
		}		
}
int translada(){
	int cont, aux;
	
	for(cont=colunas-1; cont > 0; cont--)
	{	
		if(matriz[linhas-1][cont] == ' ' && matriz[linhas-1][cont-1] == ' ')
			while(matriz[linhas-1][cont] == ' ' && matriz[linhas-1][cont-1] == ' ' && cont > 1)	/*Essa condicao 'cont' eh essencial pois, sem ela, a matriz*/
					cont--;
		if(matriz[linhas-1][cont] == ' ' && matriz[linhas-1][cont-1] != ' ')
		{	
			for(aux=0; aux < linhas; aux++)
			{
				matriz[aux][cont] = matriz[aux][cont-1];
				matriz[aux][cont-1] = ' ';
			}
			return cont;
		}	
	}
	return 0;			
}
void geramatrix(){
	int i, j, tamanho;
	srand(time(NULL));
	tamanho = strlen(letras);
	for(i=0; i < linhas; i++)
		for(j=0; j< colunas; j++)
			matriz[i][j] = letras[rand()%tamanho];
}

void atualiza_score(int adicionar, int *elementos){
	elementos = 0;
	pontuacao = pontuacao + adicionar;
}

void restaura(char letra){
	int i, j;
	for(i=0; i<linhas;i++)
			for(j=0; j<colunas;j++)
					if(matriz[i][j] == '*')
							matriz[i][j] = letra;		
}

void despedida(){
	system(CLEAR);
	printf("==================================\n");
	printf("=Obrigado por jogar EliminaLetras=\n");
	printf("==================================\n");
	printf("Aperte <ENTER> para continuar...\n");
	getchar();	
	system(CLEAR);
}

int valida_linha(){
	int linha;
	char entrada[100];
	entrada[0] = 'z';
	scanf("%[^\n]", entrada);
	getchar();
	linha = entrada[0] - 48;			/*Conversao para 'int'*/
	if(linha > linhas || strlen(entrada) != 1)
		return -1;
	else
		return linha;
}

int valida_coluna(){
	int coluna;
	char entrada[100];
	entrada[0] = 'z';
	scanf("%[^\n]", entrada);
	getchar();
	coluna = entrada[0] - 48;			/*Conversao para 'int'*/
	if(coluna > colunas || strlen(entrada) != 1)
		return -1;
	else
		return coluna;
}
int valida_confirma(){

	char confirma[100];
	scanf("%[^\n]", confirma);
	getchar();
	confirma[0] = toupper(confirma[0]);				/*Transforma a entrada do usuario em maiuscula*/								
	if(strlen(confirma) == 1 && confirma[0] == 'S')
		return 1;
	else if(strlen(confirma) == 1 && confirma[0] == 'N')
		return -2;
	else
		return -1;
}	

void valida_nome(){

	char nome[200];
	int tam=1000;
	while(tam < 3 || tam > 20)
	{	
		printf("Digite seu nome(min.3, max.20): ");
		scanf("%[^\n]", nome);
		getchar();
		tam = strlen(nome);
		system(CLEAR);
	}
	strcpy(estrutura[11].nick, nome);				/*Grava o nome do sujeito na estrutura*/
	estrutura[11].score = -1;				/**/

}
