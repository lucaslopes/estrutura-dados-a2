#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

//Protótipos
void apresentacao();
char menu_principal();
char menu_consultar();
char menu_alterar();
void adicionar_peca();
void consultar();
void alterar();

//Estrutura do estoque
typedef struct estoque {
    char codigo[10];
	char nome[40];
	char marca[30];
	int quantidade;
    float preco;    
} estoque;

//Varivaies globais
FILE *arq;
estoque peca;
int opcao; //variável para entrada de opção nos menus.

//Apresentacao do Trabalho
void apresentacao() {
	system("cls");
    printf("\n");
    printf("************* Trabalho da A2 *************\n\n");
    
    printf("Materia\n\n");
    printf("   Estrutura de Dados\n\n");
    
    printf("Professor\n\n");
    printf("   Alfredo Boente\n\n");
    
    printf("Integrantes\n\n");
    printf("   Amarildo Lucas\n");
    printf("   Bruno Lopes de Mello\n");
    printf("   Lucas Lopes Felipe\n\n");    
}

//Menu Principal
int menu_principal() {
    system("cls");
    printf("\n");
    printf("************* Menu de Opcoes *************\n\n");
    printf(" Menu Principal >\n\n");
    printf("   [1] - Adicionar uma nova peca - [1]\n");
    printf("   [2] -    Fazer uma consulta   - [2]\n");
    printf("   [3] -   Alterar alguma peca   - [3]\n\n");
    printf("   [0] -          Sair           - [0]\n\n");
    printf("> ");
    scanf("%d", opcao);
    return opcao;
}

//Menu de Consulta
int menu_consultar() {
    system("cls");
    printf("\n");
    printf("************* Menu de Opcoes *************\n\n");
    printf(" Menu Principal > Consultar\n\n");
    printf("   [1] -  Listar todo o estoque  - [1]\n");
    printf("   [2] -   Procurar por Codigo   - [2]\n");
    printf("   [3] -    Procurar por Nome    - [3]\n");
    printf("   [4] -   Procurar por Marca    - [4]\n\n");    
    printf("   [0] -         Voltar          - [0]\n\n");
    printf("> ");
    scanf("%d", opcao);
    return opcao;
}

//Menu de Alteracao
int menu_alterar() {
    system("cls");
    printf("\n");
    printf("************* Menu de Opcoes *************\n\n");
    printf(" Menu Principal > Alterar\n\n");
    printf("   [1] -   Alterar o Codigo   - [1]\n");
    printf("   [2] -    Alterar o Nome    - [2]\n");
    printf("   [3] -   Alterar a Marca    - [3]\n");
    printf("   [4] - Alterar a Quantidade - [4]\n");
    printf("   [5] -   Alterar o Preco    - [5]\n\n");
    printf("   [0] -        Voltar        - [0]\n\n");
    printf("> ");
    scanf("%d", opcao);
    return opcao;
}

//Verificar se já existe o codigo de uma peca, retornando 1
    int verifica(char codigo[]) {
    while (fread(&peca, sizeof(estoque), 1, arq))
    if (!strcmp(peca.codigo, codigo))
    	return 1;
    return 0;
    }

//Verificar se já existe o codigo de uma peca, retornando 1
int verifica_num(int num) {
    fread(&peca,sizeof(estoque),1,arq);
    while(!feof(arq)) {
        if (peca.quantidade == num) {
            fseek(arq,-sizeof(estoque),SEEK_CUR);
            return 1;
        } fread(&peca,sizeof(estoque),1,arq);
    } return 0;
}

//Adicionar uma nova peca ao estoque
void adicionar_peca() {
	char codigo[10];

    arq = fopen("banco.bin","a+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    system("cls");
    printf("\n************* Adicionar Peca *************\n\n");
    printf(" Menu Principal > Adicionar\n\n\n");
	
	printf("Digite o codigo da peca: ");
    fflush(stdin);
    gets(codigo);

    if (verifica(codigo) == 1) {
        printf("\nEsta peca ja foi registrada.\n");
    } else {
        strcpy(peca.codigo,codigo);
        printf("Nome da peca: ");
        scanf("%c", &peca.nome);
        fwrite(&peca,sizeof(estoque),1,arq);        
        
        printf("Marca do fabricante: ");
        scanf("%c", &peca.marca);
        fwrite(&peca,sizeof(estoque),1,arq);        
        
        printf("Quantidade de pecas: ");
        scanf("%d", &peca.quantidade);
        fwrite(&peca,sizeof(estoque),1,arq);
        
        printf("Preco unitario: ");
        scanf("%f", &peca.preco);
        fwrite(&peca,sizeof(estoque),1,arq);
    } fclose(arq);
}

//Modificar uma peca do estoque
void consultar() {
	
}

//Remover uma peca do estoque
void alterar() {
	
}

//Funcao principal
int main() {
    int op;
    do {
        op = menu_principal();
        switch(op) {
            case 1: adicionar_peca(); break;
            case 2: consultar(); break;
            case 3: alterar(); break;
        }
        printf("\n");
        system("PAUSE");
    } while (op != '0');
    apresentacao();
    return 0;
}
