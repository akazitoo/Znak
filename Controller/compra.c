#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>

struct hist {
  char time[50];
  char item[40];
  float price;
  struct hist* next;
};
struct purchase {
  char item[40];
  float price;
  struct purchase* next;
};
struct dadosUsers {
  char nome[30];
  char senha[30];
  struct hist* head;
  struct purchase* root;
  struct dadosUsers* next;
};

void append(struct dadosUsers** head_ref, char new_nome[], char new_senha[]) {
  struct dadosUsers* new_node = (struct dadosUsers*)malloc(sizeof(struct dadosUsers));
  struct dadosUsers* last = *head_ref;

  strcpy(new_node->nome, new_nome);
  strcpy(new_node->senha, new_senha);
  new_node->next = NULL;

  if (*head_ref == NULL) {
  *head_ref = new_node;
  return;
  }

  while (last->next != NULL) last = last->next;

  last->next = new_node;
  return;
}

struct dadosUsers* search(struct dadosUsers* head, char user[])
{
    if (head == NULL){
      printf("Usuário não existe");
      return head;
    }
     
    if (strcmp(head->nome, user) == 0)
        return head;
 
    return search(head->next, user);
}

void buy(struct dadosUsers* n){
  if(n != NULL){
    char item[40], comma;
    float price, p[100];
    char a[100][40];
    int i=0, option;
    time_t t;
    FILE *ptrproducts;
    ptrproducts = fopen("produtos.txt", "r"); 
    while(!(feof(ptrproducts))){
      fscanf(ptrproducts,"%s %c %f", item, &comma, &price);
      strcpy(a[i], item);
      p[i] = price;
      i++;
      printf("%d - %s %f\n", i, item, price);
    }
    fclose(ptrproducts);
    printf("Digite o indice do produto desejado: ");
    scanf("%d", &option);

    struct purchase* new_node = (struct purchase*)malloc(sizeof(struct purchase));
    strcpy(new_node->item, a[option-1]);
    new_node->price = p[option-1];
    new_node->next = NULL;
    struct purchase* tmpo = n->root;
    n->root = new_node;
    new_node->next = tmpo;

    struct hist* node = (struct hist*)malloc(sizeof(struct hist));
    strcpy(node->item, a[option-1]);
    node->price = p[option-1];
    strcpy(node->time, ctime(&t));
    node->next = NULL;

    struct hist* tmp = n->head;
    n->head = node;
    node->next = tmp;
    
    printf("produto comprado com sucesso\n");
    return;
  }
  else return;

}

void printhist(struct dadosUsers* node){
  printf("HISTÓRICO\n");
  while(node->head != NULL){
    printf("%s %s %f\n", node->head->time, node->head->item, node->head->price);
    node->head = node->head->next;
  }
}

int main(void) {

  char nome[30], option2;
  char senha[30];
  char usuario[30];
  char comma;
  int option, i = 1;
  

  struct dadosUsers* head = NULL;


  FILE *ptruser;

  ptruser = fopen("users.txt", "r");
  while(!(feof(ptruser))){
    fscanf(ptruser,"%s %c %s", nome, &comma, senha);
    append(&head, nome, senha);
  }

  printf("Olá, digite o seu nome de usuário: ");
  scanf("%s", usuario);
  while(i){
    printf("1 - COMPRAR\n2 - VER HISTÓRICO\n");
    printf("Digite o número da operação que você deseja realizar: ");
    scanf("%d", &option);
    if (option == 1) buy(search(head, usuario));
    else if (option == 2) printhist(search(head, usuario));
    printf("Deseja realizar outra operação? s|n ");
    scanf(" %c", &option2);
    if (option2 == 'n') i = 0;

  }
 


  fclose(ptruser);
  return 0;
}
