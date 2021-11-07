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

struct dadosUsers search(struct dadosUsers* head, char user[])
{
    // Base case
    if (head == NULL){
      printf("Usuário não existe");
    }
     
    // If key is present in current node, return true
    if (strcmp(head->nome, user) != 0)
        return *head;
 
    // Recur for remaining list
    return search(head->next, user);
}

void buy(struct dadosUsers head){

  char item[40], comma;
  float price, p[100];
  const char *a[100];
  int i=0, option;
  time_t t;
  FILE *ptrproducts;
  ptrproducts = fopen("produtos.txt", "r"); 
  while(!(feof(ptrproducts))){
    fscanf(ptrproducts,"%s %c %f", item, &comma, &price);
    a[i] = item;
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

  struct hist* node = (struct hist*)malloc(sizeof(struct hist));
  strcpy(node->item, a[option-1]);
  node->price = p[option-1];
  strcpy(node->time, ctime(&t));
  node->next = NULL;
  
  printf("produto comprado com sucesso");

}

int main(void) {

  char nome[30];
  char senha[30];
  char usuario[30];
  char comma;
  

  struct dadosUsers* head = NULL;


  FILE *ptruser;

  ptruser = fopen("users.txt", "r");
  while(!(feof(ptruser))){
    fscanf(ptruser,"%s %c %s", nome, &comma, senha);
    append(&head, nome, senha);
  }

  printf("Olá, digite o seu nome de usuário: ");
  scanf("%s", usuario);
  buy(search(head, usuario));


  fclose(ptruser);
  return 0;
}
