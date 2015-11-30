#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <conio.h>
#include <string.h>

#define MAX 20

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

int opcao; //variavel para entrada de opcao nos menus
pfila minhaAutoPecas;
pestoque meuEstoque;
int op;

// Inicializa os elementos da fila
void inicializa(pfila *f) {
  f->inicio = 0;
  f->final= -1;
  f->qtd = 0;
}

// Verifica se a fila esta cheia
int cheia(pfila *f) {
  if (f->qtd ==  MAX) {
    return 1;
  }
  else {
    return 0;
  }
}

// Verifica se a fila esta vazia
int vazia (pfila *f) {
  if (f->qtd==0) {
    return 1;
  }
  else {
    return 0;
  }
}

// Adiciona um elemento na fila
int enqueue(pfila *f, pestoque t) {
  if (cheia(f)) {
    return 0;
  }
  else {
    f->final++;
    f->base_dados[f->final] = t;
    f->qtd++;
    return 1;
  }
}

// Remove um elemento da fila
int dequeue(pfila *f, pestoque *t) {
  if (vazia(f)) {
    return 0;
  }
  else {
    *t = f->base_dados[f->inicio];
    f->inicio++;
    f->qtd--;
    return 1;
  }
}

//################################################## MENUS ##################################################

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
  printf("   [4] -   Procurar por Marca    - [4]\n\n");    
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
  printf("   [2] -    Alterar o Nome    - [2]\n");
  printf("   [3] -   Alterar a Marca    - [3]\n");
  printf("   [4] - Alterar a Quantidade - [4]\n");
  printf("   [5] -   Alterar o Preco    - [5]\n\n");
  printf("   [0] -        Voltar        - [0]\n\n");
  printf("> ");
  scanf("%d", &opcao);
  return opcao;
}

// Adicionar uma nova peca ao estoque
void adicionar_peca() {
  
	printf("Digite o codigo da peca: ");
  fflush(stdin);
  gets(meuEstoque.codigo);
  gets(meuEstoque.nome);

  if (enqueue(&minhaAutoPecas, meuEstoque)) {
      printf("Peca %s incluida com sucesso. \n", meuEstoque.nome);
  }
  else {
    printf("Fila cheia. Nao ha espaco suficiente.");
  }
}

pestoque primeiro(pfila f) {
  if (f.final > -1) {
    return f.base_dados[f.inicio];
  }
}

void consulta_codigo(pfila f, char codigo []) {
  while (f.final >= f.inicio) {
    if (strcmp (codigo, f.base_dados[f.inicio].codigo) == 0) {
      printf("Codigo encontrado... %s \n", f.base_dados[f.inicio].codigo);
      printf("Posicao... %d \n", f.inicio + 1);
      
      break;
    }
    else {
      printf("Codigo nao existe.");
    }
    
    f.inicio++;
  }
}

// Remove uma nova peca ao estoque
void remove_peca() {

  if (dequeue(&minhaAutoPecas, &meuEstoque)) {
    printf("Peca %s removida do estoque. \n", meuEstoque.nome);
  }
  else {
    printf("Fila vazia. Nao existe nenhuma peca.");
  }
}

// Consultar uma peca do estoque
void consultar() {
  int op_cons;
  do {
    op_cons = menu_consultar();
    switch(op_cons) {
      case 1:
        printf("Procurar por codigo da peca: \n");
        char codigo [10];
        fflush(stdin);
        gets(codigo);
        consulta_codigo(minhaAutoPecas, codigo);
        break;
    }
    printf("\n");
  } while (op_cons != 0);
}

// Apresentacao do Trabalho
void apresentacao() {
	//system("cls");
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
  
  inicializa(&minhaAutoPecas);
  
  do {
      op = menu_principal();
      switch(op) {
          case 1: adicionar_peca(); break;
          case 2: consultar(); break;
          case 3: /*alterar();*/ break;
      }
      printf("\n");
      //system("PAUSE");
  } while (op != 0);
  apresentacao();
  return 0;
}
