#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

//Estrutura do estoque
typedef struct estoque {
    char nome[20];
    int codigo;
} estoque;

//Variaveis globais
FILE *arq;
estoque peca;

//Retornar alguma opcao do menu
char menu() {
    system("cls");
    printf("\n");
    printf("************* Menu de Opcoes *************\n\n");
    printf("   [1] - Adicionar uma nova peca - [1]\n");
    printf("   [2] -   Consultar o Estoque   - [2]\n");
    printf("   [3] -   Procurar alguma peca  - [3]\n");
    printf("   [4] -   Alterar alguma peca   - [4]\n");
    printf("   [5] -    Remover uma peca     - [5]\n");
    printf("\n");
    printf("   [0] -          Sair           - [0]\n");
    printf("\n> ");
    return (toupper(getche()));
}

//Verificar se já existe uma peca, retornando 1
    int verifica (char nome[]) {
    while (fread(&peca, sizeof(estoque), 1, arq))
    if (!strcmp(peca.nome, nome))
    return 1;
    return 0;
    }

//Verificar se já existe o codigo de uma peca, retornando 1
int verifica_cod(int num) {
    fread(&peca,sizeof(estoque),1,arq);
    while(!feof(arq))     {
        if (peca.codigo == num)         {
            fseek(arq,-sizeof(estoque),SEEK_CUR);
            return 1;
        }
        fread(&peca,sizeof(estoque),1,arq);
    }
    return 0;
}

//Adicionar uma nova peca ao estoque
void adicionar_peca() {
	
}

//Modificar uma peca do estoque
void alterar_peca() {
	
}

//Remover uma peca do estoque
void remover_peca() {
	
}

//Procurar uma peca no estoque
void procura_peca() {
	
}

//Mostrar o estoque
void consultar_estoque() {
	
}

//Funcao principal
int main() {
    char op;
    do {
        op = menu();
        switch(op) {
            case '1': adicionar_peca(); break;
            case '2': consultar_estoque(); break;
            case '3': procura_peca(); break;
            case '4': alterar_peca(); break;
            case '5': remover_peca(); break;
        }
        printf("\n");
        system("PAUSE");
    } while (op != '0');
    return 0;
}
