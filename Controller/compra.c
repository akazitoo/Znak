#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct hist
{       
        char username[20];
        char time[50];
        char item[40];
        float price;
        struct hist *next;
};

struct dadosUsers
{
        char nome[30];
        char senha[30];
        float saldo;
        struct hist *head;
        struct dadosUsers *next;
};

struct dadosCantina
{
        char nome[30];
        char senha[30];
        struct dadosCantina *next;
};

struct dadosUsers *search(struct dadosUsers *head, char user[], int cond);

void append(struct dadosUsers **head_ref, char new_nome[], char new_senha[])
{
        struct dadosUsers *new_node = (struct dadosUsers *)malloc(sizeof(struct dadosUsers));
        struct dadosUsers *last = *head_ref;

        strcpy(new_node->nome, new_nome);
        strcpy(new_node->senha, new_senha);
        new_node->next = NULL;

        if (*head_ref == NULL)
        {
                *head_ref = new_node;
                return;
        }

        while (last->next != NULL)
                last = last->next;

        last->next = new_node;
        return;
}

void appendcantina(struct dadosCantina **head_ref, char new_nome[], char new_senha[])
{
        struct dadosCantina *new_node = (struct dadosCantina *)malloc(sizeof(struct dadosCantina));
        struct dadosCantina *last = *head_ref;

        strcpy(new_node->nome, new_nome);
        strcpy(new_node->senha, new_senha);
        new_node->next = NULL;

        if (*head_ref == NULL)
        {
                *head_ref = new_node;
                return;
        }

        while (last->next != NULL)
                last = last->next;

        last->next = new_node;
        return;
}

float saldo(struct dadosUsers *node)
{
        float value;
        float last;
        if (value == 0)
        {
                printf("quanto você gostaria de depositar? ");
                scanf("%f", &value);
                node->saldo = value;
                printf("R$%.2f depositado na conta\n", value);
                last = value;
        }
        else
        {
                printf("quanto você gostaria de depositar? ");
                scanf("%f", &value);
                node->saldo = last + value;
                last = last + value;
                printf("R$%.2f depositado na conta\n", value);
        }
        return node->saldo;
}

struct dadosUsers *search(struct dadosUsers *head, char user[], int cond)
{
        if (head == NULL)
        {
                if (cond == 1)
                        printf("Usuário não existe");
                return head;
        }

        if (strcmp(head->nome, user) == 0)
                return head;

        return search(head->next, user, cond);
}

float buy(struct dadosUsers *n)
{
        if (n != NULL)
        {
                char item[40], strpagamento[15];
                float price, p[100];
                char a[100][40];
                int i = 0, option, pagamento, what;
                FILE *ptrproducts;
                FILE *file;
                ptrproducts = fopen("inventario.txt", "r");
                while (!(feof(ptrproducts)))
                {
                        fscanf(ptrproducts, "%s %f %d", item, &price, &what);
                        strcpy(a[i], item);
                        p[i] = price;
                        i++;
                        printf("%d - %s R$%.2f\n", i, item, price);
                }
                fclose(ptrproducts);
                printf("Digite o indice do produto desejado: ");
                scanf("%d", &option);
                printf("Indique a forma de pagamento:\n1-dinheiro\n2-crédito na loja\n3-cartão\n");
                scanf(" %d", &pagamento);
                if (pagamento == 2)
                {
                        saldoRemove(n, p[option - 1]);
                        strcpy(strpagamento, "credito");
                        
                }
                else if (pagamento == 1)
                        strcpy(strpagamento, "dinheiro");
                else if (pagamento == 3)
                        strcpy(strpagamento, "cartao");
                struct tm *ptrs;
                time_t t;
                t = time(NULL);
                ptrs = localtime(&t);
                FILE *ptrhist;

                ptrhist = fopen("histgeral.txt", "a");
                fprintf(ptrhist, "%s R$%.2f %s %s\n", a[option - 1], p[option - 1], n->nome, asctime(ptrs));
                fclose(ptrhist);

                struct hist *node = (struct hist *)malloc(sizeof(struct hist));
                strcpy(node->item, a[option - 1]);
                node->price = p[option - 1];
                strcpy(node->time, asctime(ptrs));
                node->next = NULL;
                struct hist *tmp = n->head;
                n->head = node;
                node->next = tmp;
                        
                int comanda; 
                
                file = fopen("entregas.txt","a");
        
                fprintf(file, "%d %s %.2f %s %s\n",comanda++, a[option-1], p[option-1], n->nome,strpagamento);
                fclose(file);

                printf("produto comprado com sucesso\n");
                return node->price;
        }
        else
                return 0;
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
  buy(search(head, usuario, 0));


  fclose(ptruser);
  return 0;
}
