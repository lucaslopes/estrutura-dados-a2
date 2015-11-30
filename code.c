#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

//Prototipos
int menu_principal();
int menu_consultar();
int menu_alterar();
void adicionar_peca();
void consultar();
void alterar();
void apresentacao();

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
int opcao; //variavel para entrada de opcao nos menus

//################################################## MENUS ##################################################

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
    scanf("%d", &opcao);
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
    scanf("%d", &opcao);
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
    scanf("%d", &opcao);
    return opcao;
}

//################################################## FUNCOES DE VERIFICACAO ##################################################

//Verificar se já existe o codigo de uma peca, retornando 1
int verifica_cod(char codigo[]) {
	while (fread(&peca, sizeof(estoque), 1, arq))
		if (!strcmp(peca.codigo, codigo))
			return 1;
return 0;
}

//Verificar se já existe o nome de uma peca, retornando 1
int verifica_nome(char nome[]) {
    while (fread(&peca, sizeof(estoque), 1, arq))
	    if (!strcmp(peca.nome, nome))
    		return 1;
return 0;
}

//Verificar se já existe a marca de uma peca, retornando 1
int verifica_marca(char marca[]) {
    while (fread(&peca, sizeof(estoque), 1, arq))
	    if (!strcmp(peca.marca, marca))
    		return 1;
return 0;
}

//################################################## FUNCAO ADICIONAR ##################################################

//Adicionar uma nova peca ao estoque
void adicionar_peca() {
	char cod[10];

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
    gets(cod);

    if (verifica_cod(cod) == 1) {
        printf("\nEsta peca ja foi registrada.\n");
    } else {
        strcpy(peca.codigo,cod);
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

//################################################## FUNCAO CONSULTAR ##################################################

//Uma das opcoes do menu Consultar, mostra todos
void consultar_tudo() {
	system("cls");
    printf("\n************* Consultar Peca *************\n\n");
    printf(" Menu Principal > Consultar > Toda a lista\n\n\n");
    
    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    
    printf("----------------------------------------\n");
    
    fread(&peca,sizeof(estoque),1,arq);
    while (!feof(arq)) {    
    	printf("Codigo: %s\n",peca.codigo);
    	printf("Nome: %s\n",peca.nome);
    	printf("Marca: %s\n",peca.marca);
    	printf("Quantidade: %d\n",peca.quantidade);
    	printf("Preco: %f\n",peca.preco);
    
		fread(&peca,sizeof(estoque),1,arq);
    }
    
    printf("----------------------------------------\n");
    fclose(arq);
}

//Uma das opcoes do menu Consultar, busca por codigo
void consultar_codigo() {
	char cod[10];
	
	system("cls");
    printf("\n************* Consultar Peca *************\n\n");
    printf(" Menu Principal > Consultar > Por codigo\n\n\n");
    
    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite o codigo: ");
    fflush(stdin);
    gets(cod);

    if (verifica_cod(cod) == 1) {
    	printf("Codigo: %s\n",peca.codigo);
    	printf("Nome: %s\n",peca.nome);
    	printf("Marca: %s\n",peca.marca);
    	printf("Quantidade: %d\n",peca.quantidade);
    	printf("Preco: %f\n",peca.preco);
    } else {
        printf("\nEsta peca nao existe.\n");
    } fclose(arq);
}

//Uma das opcoes do menu Consultar, busca por nome
void consultar_nome() {
	char nome[40];
	
	system("cls");
    printf("\n************* Consultar Peca *************\n\n");
    printf(" Menu Principal > Consultar > Por nome\n\n\n");
    
    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite o nome: ");
    fflush(stdin);
    gets(nome);

    if (verifica_nome(nome) == 1) {
    	printf("Codigo: %s\n",peca.codigo);
    	printf("Nome: %s\n",peca.nome);
    	printf("Marca: %s\n",peca.marca);
    	printf("Quantidade: %d\n",peca.quantidade);
    	printf("Preco: %f\n",peca.preco);
    } else {
        printf("\nEsta peca nao existe.\n");
    } fclose(arq);
}

//Uma das opcoes do menu Consultar, busca por marca
void consultar_marca() {
	char marca[30];
	
	system("cls");
    printf("\n************* Consultar Peca *************\n\n");
    printf(" Menu Principal > Consultar > Por marca\n\n\n");
    
    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite a marca: ");
    fflush(stdin);
    gets(marca);

    if (verifica_marca(marca) == 1) {
    	printf("Codigo: %s\n",peca.codigo);
    	printf("Nome: %s\n",peca.nome);
    	printf("Marca: %s\n",peca.marca);
    	printf("Quantidade: %d\n",peca.quantidade);
    	printf("Preco: %f\n",peca.preco);
    } else {
        printf("\nEsta peca nao existe.\n");
    } fclose(arq);	
}

//Modificar uma peca do estoque
void consultar() {
	int op_cons;
    do {
        op_cons = menu_consultar();
        switch(op_cons) {
            case 1: consultar_tudo(); break;
            case 2: consultar_codigo(); break;
            case 3: consultar_nome(); break;
	    	case 4: consultar_marca(); break;
        }
        printf("\n");
        system("PAUSE");
    } while (op_cons != '0');
}

//################################################## FUNCAO ALTERAR ##################################################

//Uma das opcoes do menu Alterar, muda o codigo
void alterar_codigo(char muda_cod[]) {
	system("cls");
    printf("\n************* Alterar Peca *************\n\n");
    printf(" Menu Principal > Alterar > Codigo\n\n\n");
    
    char codigo[10];

    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    
    if (verifica_cod(muda_cod) == 1) {
    	printf("\nCodigo atual: %s", peca.codigo);
    	printf("\nDigite o novo codigo: ");
    	fflush(stdin);
    	gets(codigo);
    	strcpy(peca.codigo,codigo);
    	fwrite(&peca,sizeof(estoque),1,arq);
    } fclose(arq);
}

//Uma das opcoes do menu Alterar, muda o nome
void alterar_nome(char muda_cod[]) {
	system("cls");
    printf("\n************* Alterar Peca *************\n\n");
    printf(" Menu Principal > Alterar > Codigo\n\n\n");
    
    char nome[20];

    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    
    if (verifica_cod(muda_cod) == 1) {
    	printf("\nNome atual: %s", peca.nome);
    	printf("\nDigite o novo nome: ");
    	fflush(stdin);
    	gets(nome);
    	strcpy(peca.nome,nome);
    	fwrite(&peca,sizeof(estoque),1,arq);
    } fclose(arq);
}

//Uma das opcoes do menu Alterar, muda a marca
void alterar_marca(char muda_cod[]) {
	system("cls");
    printf("\n************* Alterar Peca *************\n\n");
    printf(" Menu Principal > Alterar > Codigo\n\n\n");
    
    char marca[30];

    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    
    if (verifica_cod(muda_cod) == 1) {
    	printf("\nMarca atual: %s", peca.marca);
    	printf("\nDigite a nova marca: ");
    	fflush(stdin);
    	gets(marca);
    	strcpy(peca.marca,marca);
    	fwrite(&peca,sizeof(estoque),1,arq);
    } fclose(arq);
}

//Uma das opcoes do menu Alterar, muda a quantidade
void alterar_quantidade(char muda_cod[]) {
	system("cls");
    printf("\n************* Alterar Peca *************\n\n");
    printf(" Menu Principal > Alterar > Codigo\n\n\n");

    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    
    if (verifica_cod(muda_cod) == 1) {
    	printf("\nQuantidade atual: %d", peca.quantidade);
    	printf("\nDigite a nova quantidade: ");
        scanf("%d", &peca.quantidade);
    	fwrite(&peca,sizeof(estoque),1,arq);
    } fclose(arq);
}

//Uma das opcoes do menu Alterar, muda o preco
void alterar_preco(char muda_cod[]) {
	system("cls");
    printf("\n************* Alterar Peca *************\n\n");
    printf(" Menu Principal > Alterar > Codigo\n\n\n");

    arq = fopen("banco.bin","r+b");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    
    if (verifica_cod(muda_cod) == 1) {
    	printf("\nPreco atual: %f", peca.preco);
    	printf("\nDigite o novo preco: ");
        scanf("%f", &peca.preco);
    	fwrite(&peca,sizeof(estoque),1,arq);
    } fclose(arq);
}

//Alterar uma peca do estoque
void alterar() {
	int op_alt;
	char muda_cod[10];
	
	system("cls");
    printf("\n************* Alterar Peca *************\n\n");
    printf(" Menu Principal > Alterar\n\n\n");	
	
	printf("Digite o codigo da peca que deseja alterar: ");
	fflush(stdin);
    gets(muda_cod);
    
    
    if (verifica_cod(muda_cod) == 1) {
    	do {
        	op_alt = menu_alterar();
        	switch(op_alt) {
            	case 1: alterar_codigo(muda_cod); break;
            	case 2: alterar_nome(muda_cod); break;
            	case 3: alterar_marca(muda_cod); break;
				case 4: alterar_quantidade(muda_cod); break;
				case 5: alterar_preco(muda_cod); break;
        	}
			printf("\n");
			system("PAUSE");
    	} while (op_alt != '0');
    } else {
        printf("\nEsta peca nao existe.\n");
	}
}

//################################################## OUTRAS INFORMACOES ##################################################

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

//################################################## FUNCAO PRINCIPAL ##################################################

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
