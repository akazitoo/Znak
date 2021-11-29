#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

/*
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
*/

int entrada(char option)
{       
        // printf("Olá você já possui uma conta? digite 's' para sim ou digite 'n' para não - \n");
        // ! ANTIGO SCANF scanf(" %c", &option); ONDE OPTION VAI ENTRAR NA VARIAVEL
        if (option == 's'){
                // login(head, root, p1);
                return 1;
        }
        else if (option == 'n'){
                // registration(head, root, p1);
                return 0;
        } else {
                return 0;
        }
        
}