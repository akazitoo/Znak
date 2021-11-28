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

typedef struct no
{
        char product[56];
        float value;
        int quantity;
        struct no *next;
} no;

typedef struct pilha
{
        no *top;
        int tam;
} pilha;

struct dadosUsers *search(struct dadosUsers *head, char user[], int cond);
float saldoRemove(struct dadosUsers *node, float removeValue);

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

int saldoCheck(float price,  struct dadosUsers *node){
        int saldo = node -> saldo;
        if(saldo < price){
                printf("você não possui saldo suficiente para comprar esse produto\n");
                return 0;
        } else {
                return 1;
        }
}

float buy(struct dadosUsers *n)
{
        if (n != NULL)
        {
                char item[40], strpagamento[15], alergia;
                float price, p[100];
                char a[100][40];
                int i = 0, option, pagamento, what;
                FILE *ptrproducts;
                FILE *file;
                ptrproducts = fopen("inventario.txt", "r");
                printf("* - produto contém ingredientes aos quais você pode ser alergico\n");
                while (!(feof(ptrproducts)))
                {
                        fscanf(ptrproducts, "%s %f %d %c", item, &price, &what, &alergia);
                        strcpy(a[i], item);
                        p[i] = price;
                        i++;
                        if (alergia == 's'){
                                printf("%d - %s R$%.2f (*)\n", i, item, price);
                        }
                        else{
                                printf("%d - %s R$%.2f\n", i, item, price);
                        }
                }
                fclose(ptrproducts);
                printf("Digite o indice do produto desejado: ");
                scanf("%d", &option);

                printf("Indique a forma de pagamento:\n1-dinheiro\n2-crédito na loja\n3-cartão\n");
                scanf(" %d", &pagamento);

                int negativeSaldo = 0;

                if (pagamento == 2)
                {
                        if (saldoCheck(p[option - 1], n) == 1){
                                negativeSaldo = 1;
                        };
                        saldoRemove(n, p[option - 1]);
                        strcpy(strpagamento, "credito");
                }
                else if (pagamento == 1)
                        strcpy(strpagamento, "dinheiro");
                else if (pagamento == 3)
                        strcpy(strpagamento, "cartao");

                if(negativeSaldo == 0){
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
                                
                        file = fopen("entregas.txt","r");

                        int comanda; 
                        char line[50];

                        while(fgets(line, sizeof(line), file)){
                                comanda = atoi(&line[0]);
                        }
                        comanda = comanda + 1;

                        char escolha; 

                        file = fopen("entregas.txt","a");
                        printf("gostaria de agendar sua entrega para algum horario especifico? digite 's' para sim ou digite 'n' para não -  ");
                        scanf(" %c", &escolha);

                        char horarioEntrega[10]; 
                        if(escolha == 's'){
                                printf("informe qual horario gostaria de receber a entrega\n");
                                scanf("%s", horarioEntrega);
                                printf("horario de entrega é %s\n", horarioEntrega);
                                fprintf(file, "%d %s %.2f %s %s %s\n",comanda++, a[option-1], p[option-1], n->nome,strpagamento, horarioEntrega);
                                fclose(file);
                        } else {
                                fprintf(file, "%d %s %.2f %s %s\n",comanda++, a[option-1], p[option-1], n->nome,strpagamento);
                                fclose(file);
                        }
                

                        printf("produto comprado com sucesso\n");
                        return node->price;
                        }
                else {
                        return 0;
                }
        }
        else
                return 0;
}

float saldoRemove(struct dadosUsers *node, float removeValue)
{
        node->saldo = node->saldo - removeValue;
        printf("saldo atualizado: R$%.2f\n", node->saldo);
        return node->saldo;
}

void printhist(struct dadosUsers *node)
{       
        printf("HISTÓRICO\n");
        while (node->head != NULL)
        {
                printf("%s %.2f %s\n", node->head->time, node->head->price, node->head->item);
                node->head = node->head->next;
        }
        return;
}
void deleteentrega(){
        FILE *entregasFile = fopen("entregas.txt", "rt");
        int choice; 
        printf("qual comanda deseja apagar? ");
        scanf(" %d", &choice);
        
        char line[50];
        char tmp[100][50];
        int i;

        while(fgets(line, sizeof(line), entregasFile)){
                printf("%s", line);
                if(atoi(&line[0]) != choice){
                        strcpy(tmp[i], line);
                        i++;
                }
        }
        entregasFile = fopen("entregas.txt", "w");
        int j = 0;
        while(j <= i){
                fprintf(entregasFile, "%s", tmp[j]);
                j++;
        }
}

void users(struct dadosUsers *node)
{
        int i = 1, option;
        char option2;
        float valorSaldo, remove;
        while (i)
        {
                printf("1 - COMPRAR\n2 - VER HISTÓRICO\n3 - DEPOSITAR DINHEIRO\n4 - CONSULTAR SALDO\n");
                printf("Digite o número da operação que você deseja realizar: ");
                scanf("%d", &option);
                if (option == 1)
                {
                        buy(node);
                }
                else if (option == 2)
                {
                        printhist(node);
                }
                else if (option == 3)
                {
                        valorSaldo = saldo(node);
                }
                else if (option == 4)
                {
                        printf("seu saldo é: R$%.2f\n", node->saldo);
                }
                printf("\nDeseja realizar outra operação? digite 's' para sim ou digite 'n' para não - ");
                scanf(" %c", &option2);
                if (option2 == 'n')
                {
                        i = 0;
                }
        }
}

int build_inventory(pilha *p){
        no *ptr = (no *)malloc(sizeof(no));
        float value;
        int quantity;

        FILE *file;
        file = fopen("inventario.txt", "r");

        while (!(feof(file)))
        {
                fscanf(file, "%s", ptr->product);
                fscanf(file, "%f", &ptr->value);
                fscanf(file, "%d", &ptr->quantity);
                ptr->next = p->top;
                p->top = ptr;
                p->tam++;
                no *backup = (no *)malloc(sizeof(no));
                ptr = backup;
        }
        fclose(file);
        return 0;
}

int inventario(pilha *p)
{       
  
        no *ptr = p->top;

        printf("Nome     Valor     Quantidade\n\n");
        while (ptr != NULL)
        {
                printf("%s  %.2f  %d \n", ptr->product, ptr->value, ptr->quantity);
                ptr = ptr->next;
        }
        return 0;
}

void cantina(pilha *p)
{      
        int i = 1, option;
        char option2;
        char user[30], item[40], pay[15], time[50];
        float price;

        build_inventory(p);
        
        while (i)
        {
                printf("1 - VER PRODUTOS A SEREM ENTREGUES\n2 - VER HISTÓRICO\n3 - VER INVENTÁRIO\n4 - EDITAR ENTREGAS\n");
                printf("Digite o número da operação que você deseja realizar: ");
                scanf("%d", &option);
                if (option == 1)
                {
                        printf("COMANDA  |  ITEM  |  PREÇO  |  USUARIO  |  PAGAMENTO  |  HORÁRIO\n");
                        FILE *ptrentregas;
                        ptrentregas = fopen("entregas.txt", "r");

                        char line[50];
                        while(fgets(line, sizeof(line), ptrentregas)){
                                printf("%s", line);
                        }
                        fclose(ptrentregas);
                }
                else if (option == 2)
                {
                        printf("ITEM  |  PREÇO  |  USUARIO  |  DATA\n");
                        FILE *ptrhist;
                        ptrhist = fopen("histgeral.txt", "r");
                        
                        char line[50];
                        while (fgets(line, sizeof(line), ptrhist))
                        {
                                printf("%s", line);
                        }
                        fclose(ptrhist);
                }
                else if (option == 3)
                {
                        inventario(p);
                }
                else if (option == 4)
                {
                        deleteentrega();
                } 
                printf("\nDeseja realizar outra operação? digite 's' para sim ou digite 'n' para não - ");
                scanf(" %c", &option2);
                if (option2 == 'n')
                        i = 0;
        }
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

struct dadosCantina *searchcantina(struct dadosCantina *head, char user[], int cond)
{
        if (head == NULL)
        {
                if (cond == 1)
                        printf("Usuário não existe");
                return head;
        }

        if (strcmp(head->nome, user) == 0)
                return head;

        return searchcantina(head->next, user, cond);
}

void passwordCheck(struct dadosUsers *head, struct dadosCantina *root, char option, pilha *p){
        char password[20];
        printf("\nInforme sua senha: ");
        scanf(" %s", password);
        if (option == 's'){
                if (strcmp(root -> senha, password) == 0){
                        printf("LOGIN REALIZADO COM SUCESSO\n");
                        cantina(p);
                        return;
                } else {
                        printf("senha errada tente novamente!");
                        return passwordCheck(head, root,option, p);
                }        
        } else {
                if (strcmp(head -> senha, password) == 0){
                        printf("LOGIN REALIZADO COM SUCESSO\n");
                        users(head);
                        return;
                } else {
                        printf("senha errada tente novamente!");
                        return passwordCheck(head, root,option, p);
                } 
        }
}

void login(struct dadosUsers *head, struct dadosCantina *root, pilha *p)
{
        char user[40], pass[20], option;
        printf("Informe o seu nome de usuário: ");
        scanf(" %s", user);

        printf("Você é funcionário da cantina? digite 's' para sim ou digite 'n' para não - \n");
        scanf(" %c", &option);
        if (option == 's')
        {
                struct dadosCantina *node = searchcantina(root, user, 1);
                if (node != NULL)
                {
                  passwordCheck(head, node,  option, p);
                }
        }
        else if (option == 'n')
        {
                struct dadosUsers *node = search(head, user, 1);

                if (node != NULL)
                {
                  passwordCheck(node, root,  option, p);
                }
        }
}

void registration(struct dadosUsers *head, struct dadosCantina *root,  pilha *p)
{
        int type;
        char user[30], senha[30], option;
        FILE *ptruser;

        ptruser = fopen("users.txt", "a");

        printf("Você é:\n1-FUNCIONÁRIO DA CANTINA\n2-ALUNO\n3-RESPONSÁVEL\nDigite o número: ");

        scanf(" %d", &type);

        if (type == 1)
                fprintf(ptruser, "cantina ");
        else if (type == 2)
                fprintf(ptruser, "aluno ");
        else if (type == 3)
                fprintf(ptruser, "pai ");
        else
        {
                printf("OPÇÃO NÃO VÁLIDA");
                return;
        }

        printf("Digite o seu nome de usuário: ");
        scanf("%s", user);

        if (type == 1)
        {
                if (searchcantina(root, user, 0) == NULL)
                {
                        fprintf(ptruser, "%s ", user);
                        printf("Digite sua senha: ");
                        scanf("%s", senha);
                        fprintf(ptruser, "%s\n", senha);
                        appendcantina(&root, user, senha);
                }
                else
                {
                        printf("Usuário já existe");
                        return;
                }
        }
        else
        {
                if (search(head, user, 0) == NULL)
                {
                        fprintf(ptruser, "%s ", user);
                        printf("Digite sua senha: ");
                        scanf("%s", senha);
                        fprintf(ptruser, "%s\n", senha);
                        append(&head, user, senha);
                }
                else
                {
                        printf("Usuário já existe");
                        return;
                }
        }
        fclose(ptruser);
        printf("CADASTRO REALIZADO COM SUCESSO!\nDeseja fazer o login digite 's' para sim ou digite 'n' para não - \n");
        scanf(" %c", &option);
        if (option == 's')
                login(head, root, p);
        else if (option == 'n')
                return;
}

int main(void)
{
        char option;
        char nome[30], senha[30], type[10];
        char user[30], item[40], pagamento[15];
        float price;

        pilha *p1 = (pilha *)malloc(sizeof(pilha));
        struct dadosUsers *head = NULL;
        struct dadosCantina *root = NULL;
        FILE *ptruser;

        ptruser = fopen("users.txt", "r");
        while (!(feof(ptruser)))
        {
                fscanf(ptruser, "%s %s %s", type, nome, senha);
                if (strcmp(type, "pai") == 0 || strcmp(type, "aluno") == 0)
                        append(&head, nome, senha);
                else
                        appendcantina(&root, nome, senha);
        }
        fclose(ptruser);
        FILE *ptrentregas;
        ptrentregas = fopen("entregas.txt", "r");
        while (!(feof(ptrentregas)))
        {
                fscanf(ptruser, "%s %f %s %s", item, &price, user, pagamento);

        }
        fclose(ptrentregas);

        int tmp; 
        while(tmp == 0){
                printf("Olá você já possui uma conta? digite 's' para sim ou digite 'n' para não - \n");
                scanf(" %c", &option);
                if (option == 's'){
                        login(head, root, p1);
                        tmp = 1;
                }
                else if (option == 'n'){
                        registration(head, root, p1);
                        tmp = 1;
                } else {
                        tmp = 0;
                }
        }
        return 0;
}