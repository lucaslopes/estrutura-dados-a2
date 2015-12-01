// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <conio.h>
#include <string.h>

#define MAX 20 // Variavel Fixa

// Prototipos
int menu_principal();
int menu_consultar();
int menu_alterar();
void adicionar();
void consultar();
void alterar();
void apresentacao();

// Estrutura do estoque
typedef struct estoque {
	char codigo[10];
	char nome[40];
	char marca[30];
	int quantidade;
	float preco;
} pestoque;

// Estrutura da fila - Manipulando a infraestrutura de controle com fila
typedef struct fila {
	int inicio, final, qtd;
	pestoque base_dados[MAX];
} pfila;

// Variaveis Globais
pfila minhaAutoPecas;
pestoque meuEstoque;
int op;
int opcao; // Variavel para entrada de opcao nos menus

//########################################################## MENUS ###########################################################

//Menu Principal
int menu_principal() {
  //system("cls");
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
  //system("cls");
  printf("\n");
  printf("************* Menu de Opcoes *************\n\n");
  printf(" Menu Principal > Consultar\n\n");
  printf("   [1] -  Listar todo o estoque  - [1]\n");
  printf("   [2] -   Procurar por Codigo   - [2]\n");
  printf("   [3] -    Procurar por Nome    - [3]\n");
  printf("   [4] -    Procurar por Marca    - [4]\n");
  printf("   [0] -         Voltar          - [0]\n\n");
  printf("> ");
  scanf("%d", &opcao);
  return opcao;
}

//Menu de Alteracao
int menu_alterar() {
  //system("cls");
  printf("\n");
  printf("************* Menu de Opcoes *************\n\n");
  printf(" Menu Principal > Alterar\n\n");
  printf("   [1] -   Alterar o Codigo   - [1]\n");
  printf("   [2] -   Alterar o Nome   - [2]\n");
  printf("   [3] -   Alterar a Marca   - [3]\n");
  printf("   [4] -   Alterar a Quantidade   - [4]\n");
  printf("   [5] -   Alterar o Preco   - [5]\n");
  printf("   [0] -        Voltar        - [0]\n\n");
  printf("> ");
  scanf("%d", &opcao);
  return opcao;
}

//################################################## FUNCOES DE VERIFICACAO ##################################################

// Verifica se a fila esta cheia
int cheia(pfila *f) {
	if (f->qtd ==  MAX) {
		return 1;
	} else {
		return 0;
}}

// Verifica se a fila esta vazia
int vazia (pfila *f) {
	if (f->qtd==0) {
		return 1;
	} else {
		return 0;
}}

//################################################### MANIPULACOES NA FILA ###################################################

// Inicializa os elementos da fila
void inicializa(pfila *f) {
	f->inicio = 0;
	f->final= -1;
	f->qtd = 0;
}

// Adiciona um elemento na fila
int enqueue(pfila *f, pestoque t) {
	if (cheia(f)) {
		return 0;
	} else {
		f->final++;
		f->base_dados[f->final] = t;
		f->qtd++;
		return 1;
}}

// Remove um elemento da fila
int dequeue(pfila *f, pestoque *t) {
	if (vazia(f)) {
		return 0;
	} else {
		*t = f->base_dados[f->inicio];
		f->inicio++;
		f->qtd--;
		return 1;
  }
}

//##################################################### FUNCAO ADICIONAR #####################################################

// Adicionar uma nova peca ao estoque
void adicionar_peca() {
	char codigo [10];
	fflush(stdin);
	
	system("cls");
    printf("\n************* Adicionar Peca *************\n\n");
    printf(" Menu Principal > Adicionar\n\n");
    
	printf("Numero de serie ou codigo da peca: ");
  	//scanf ("%[^\n]%*c", meuEstoque.codigo);
	fflush(stdin);
	fgets(codigo, 10, stdin);
	strcpy(meuEstoque.codigo, codigo);
  
	printf("\nNome da peca: ");
	scanf("%s", meuEstoque.nome);
  
	printf("\nMarca do fabricante: ");
	scanf("%s", meuEstoque.marca);
 
	printf("\nQuantidade de pecas: ");
	scanf("%d", &meuEstoque.quantidade);

	printf("\nPreco unitario: ");
	scanf("%f", &meuEstoque.preco);
  
	if (enqueue(&minhaAutoPecas, meuEstoque)) {
		printf("Peca com codigo %s foi incluida com sucesso.\n", meuEstoque.codigo);
	} else {
		printf("Fila cheia. Nao ha espaco suficiente.");
  }
}

//##################################################### FUNCAO CONSULTAR #####################################################

void lista_pecas(pfila f) {
  if (f.final > -1) {
    system("cls");
    printf("\n************* Consultar Peca *************\n\n");
    printf(" Menu Principal > Consultar > Toda a lista\n\n");
    
    while (f.final >= f.inicio) {
      printf("Posicao: %d\n", f.inicio + 1);
      printf("Codigo: %s\n", f.base_dados[f.inicio].codigo);
      printf("Nome: %s\n", f.base_dados[f.inicio].nome);
      printf("Marca: %s\n", f.base_dados[f.inicio].marca);
      printf("Quantidade: %d\n", f.base_dados[f.inicio].quantidade);
      printf("Preco: %f\n", f.base_dados[f.inicio].preco);
      f.inicio++;
    }
  } else {
    printf("Nao existe nenhum dado no estoque. Fila vazia.");
  }
}

void consulta_codigo(pfila f, char codigo []) {
  system("cls");
  printf("\n************* Consultar Peca *************\n\n");
  printf(" Menu Principal > Consultar > Codigo\n\n");
  
  while (f.final >= f.inicio) {
    if (strcmp (codigo, f.base_dados[f.inicio].codigo) == 0) {
      printf("Posicao: %d\n", f.inicio + 1);
      printf("Codigo: %s\n", f.base_dados[f.inicio].codigo);
      printf("Nome: %s\n", f.base_dados[f.inicio].nome);
      printf("Marca: %s\n", f.base_dados[f.inicio].marca);
      printf("Quantidade: %d\n", f.base_dados[f.inicio].quantidade);
      printf("Preco: %f\n", f.base_dados[f.inicio].preco);
      break;
    } else {
      printf("Codigo nao existe.");
    } f.inicio++;
  }
}

void consulta_nome(pfila f, char nome []) {
  system("cls");
  printf("\n************* Consultar Peca *************\n\n");
  printf(" Menu Principal > Consultar > Nome\n\n");
  
  while (f.final >= f.inicio) {
    if (strcmp (nome, f.base_dados[f.inicio].nome) == 0) {
      printf("Posicao: %d\n", f.inicio + 1);
      printf("Codigo: %s\n", f.base_dados[f.inicio].codigo);
      printf("Nome: %s\n", f.base_dados[f.inicio].nome);
      printf("Marca: %s\n", f.base_dados[f.inicio].marca);
      printf("Quantidade: %d\n", f.base_dados[f.inicio].quantidade);
      printf("Preco: %f\n", f.base_dados[f.inicio].preco);
      break;
    } else {
      printf("Nome da peca nao existe.");
    } f.inicio++;
  }
}

void consulta_marca(pfila f, char marca []) {
  system("cls");
  printf("\n************* Consultar Peca *************\n\n");
  printf(" Menu Principal > Consultar > Nome\n\n");
  
  while (f.final >= f.inicio) {
    if (strcmp (marca, f.base_dados[f.inicio].marca) == 0) {
      printf("Posicao: %d\n", f.inicio + 1);
      printf("Codigo: %s\n", f.base_dados[f.inicio].codigo);
      printf("Nome: %s\n", f.base_dados[f.inicio].nome);
      printf("Marca: %s\n", f.base_dados[f.inicio].marca);
      printf("Quantidade: %d\n", f.base_dados[f.inicio].quantidade);
      printf("Preco: %f\n", f.base_dados[f.inicio].preco);
      break;
    } else {
      printf("Nome da peca nao existe.");
    } f.inicio++;
  }
}

// Consultar uma peca do estoque
void consultar() {
  int op_cons;
  do {
    op_cons = menu_consultar();
    switch(op_cons) {
      case 1:
        lista_pecas(minhaAutoPecas);
        break;
      
      case 2:
        printf("Procurar por codigo da peca: \n");
        char codigo [10];
        fflush(stdin);
        fgets(codigo, 10, stdin);
        consulta_codigo(minhaAutoPecas, codigo);
        break;
        
      case 3:
        printf("Procurar por nome da peca: \n");
        char nome [20];
        fflush(stdin);
        fgets(nome, 20, stdin);
        consulta_nome(minhaAutoPecas, nome);
        break;
        
      case 4:
        printf("Procurar por marca da peca: \n");
        char marca [20];
        fflush(stdin);
        fgets(marca, 20, stdin);
        consulta_marca(minhaAutoPecas, marca);
        break;
    }
    printf("\n");
  } while (op_cons != 0);
}

//###################################################### FUNCAO ALTERAR ######################################################


void alterar_codigo(pfila f, char codigo []) {
  while (f.final >= f.inicio) {
    if (strcmp (codigo, f.base_dados[f.inicio].codigo) == 0) {
      
      char novo_codigo [10];
      fflush(stdin);
      printf("Digite o novo codigo da peca: \n");
      //scanf ("%[^\n]%*c", meuEstoque.codigo);
      fflush(stdin);
      fgets(novo_codigo, 10, stdin);
      strcpy(f.base_dados[f.inicio].codigo, novo_codigo);
      printf("Codigo alterado com sucesso.");
      break;
    }
    else {
      printf("Peca nao foi encontrado.");
    }
    
    f.inicio++;
  }
}

void alterar_nome(pfila f, char codigo []) {
  while (f.final >= f.inicio) {
    if (strcmp (codigo, f.base_dados[f.inicio].codigo) == 0) {
      
      char novo_nome [20];
      fflush(stdin);
      printf("Digite o novo nome da peca: \n");
      //scanf ("%[^\n]%*c", meuEstoque.codigo);
      fflush(stdin);
      fgets(novo_nome, 20, stdin);
      strcpy(f.base_dados[f.inicio].nome, novo_nome);
      printf("Nome alterado com sucesso.");
      break;
    }
    else {
      printf("Peca nao foi encontrado.");
    }
    
    f.inicio++;
  }
}

void alterar_marca(pfila f, char codigo []) {
  while (f.final >= f.inicio) {
    if (strcmp (codigo, f.base_dados[f.inicio].codigo) == 0) {
      
      char nova_marca [20];
      fflush(stdin);
      printf("Digite a nova marca da peca: \n");
      //scanf ("%[^\n]%*c", meuEstoque.codigo);
      fflush(stdin);
      fgets(nova_marca, 20, stdin);
      strcpy(f.base_dados[f.inicio].marca, nova_marca);
      printf("Marca alterada com sucesso.");
      break;
    }
    else {
      printf("Peca nao foi encontrada.");
    }
    
    f.inicio++;
  }
}

void alterar_quantidade(pfila f, char codigo []) {
  while (f.final >= f.inicio) {
    if (strcmp (codigo, f.base_dados[f.inicio].codigo) == 0) {
      
      int nova_qtd;
      fflush(stdin);
      printf("Digite a nova quantidade de pecas: \n");
      scanf ("%d", &meuEstoque.quantidade);
      fflush(stdin);
      f.base_dados[f.inicio].quantidade = nova_qtd;
      printf("Quantidade alterada com sucesso.");
      break;
    }
    else {
      printf("Peca nao foi encontrada.");
    }
    
    f.inicio++;
  }
}

void alterar_preco(pfila f, char codigo []) {
  while (f.final >= f.inicio) {
    if (strcmp (codigo, f.base_dados[f.inicio].codigo) == 0) {
      
      float novo_preco;
      fflush(stdin);
      printf("Digite o novo preco para a peca: \n");
      scanf ("%f", &meuEstoque.preco);
      fflush(stdin);
      f.base_dados[f.inicio].preco = novo_preco;
      printf("Preco alterado com sucesso.");
      break;
    }
    else {
      printf("Peca nao foi encontrada.");
    }
    
    f.inicio++;
  }
}

// Alterar uma peca do estoque
void alterar() {
  system("cls");
  printf("\n************* Alterar Peca *************\n\n");
  printf(" Menu Principal > Alterar\n\n");
  
  int op_alt;
  char codigo [10];
  do {
    op_alt = menu_alterar();
    switch(op_alt) {
      case 1:
        printf("Procurar por codigo da peca: \n");
        fflush(stdin);
        fgets(codigo, 10, stdin);
        alterar_codigo(minhaAutoPecas, codigo);
        break;
        
      case 2:
        printf("Procurar por codigo da peca: \n");
        fflush(stdin);
        fgets(codigo, 10, stdin);
        alterar_nome(minhaAutoPecas, codigo);
        break;
        
      case 3:
        printf("Procurar por codigo da peca: \n");
        fflush(stdin);
        fgets(codigo, 10, stdin);
        alterar_marca(minhaAutoPecas, codigo);
        break;
        
      case 4:
        printf("Procurar por codigo da peca: \n");
        fflush(stdin);
        fgets(codigo, 10, stdin);
        alterar_quantidade(minhaAutoPecas, codigo);
        break;
        
      case 5:
        printf("Procurar por codigo da peca: \n");
        fflush(stdin);
        fgets(codigo, 10, stdin);
        alterar_preco(minhaAutoPecas, codigo);
        break;
        
    }
    printf("\n");
  } while (op_alt != 0);
}

//###################################################### FUNCAO REMOVER #####################################################

// Remove uma nova peca ao estoque
void remove_peca() {
	if (dequeue(&minhaAutoPecas, &meuEstoque)) {
		printf("Peca %s removida do estoque. \n", meuEstoque.nome);
	} else {
		printf("Fila vazia. Nao existe nenhuma peca.");
}}

//#################################################### OUTRAS INFORMACOES ####################################################

// Apresentacao do Trabalho
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

//##################################################### FUNCAO PRINCIPAL #####################################################

//Funcao principal
int main() {  
	inicializa(&minhaAutoPecas);  
	do {
		op = menu_principal();
		switch(op) {
			case 1: adicionar_peca(); break;
			case 2: consultar(); break;
          	case 3: alterar(); break;
      	}
		printf("\n");
      	system("PAUSE");
  	} while (op != 0);
  	apresentacao();
  	return 0;
}
