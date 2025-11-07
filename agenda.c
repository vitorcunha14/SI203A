#include <stdio.h>
#include <string.h>
#include "agenda.h"

void exibeAgenda() {
    char nome[50];
    int telefone;
    char email[100];
    char endereco[150];

    printf("\n=== Agenda de Contatos ===\n");
    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF) {
        printf("Nome: %s | Telefone: %d | Email: %s | Endereco: %s\n", nome, telefone, email, endereco);
    }

    fclose(arq);
}

void escreveAgenda() {
    char nome[50];
    int telefone;
    char email[100];
    char endereco[150];

    printf("\n=== Cadastrar Contato ===\n");

    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Telefone: ");
    scanf("%d", &telefone);
    getchar(); 
    printf("Email: ");
    scanf(" %[^\n]", email);
    printf("Endereco: ");
    scanf(" %[^\n]", endereco);

    FILE *arq = fopen("agenda.txt", "a");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arq, "%s;%d;%s;%s\n", nome, telefone, email, endereco);
    fclose(arq);

    printf("Contato cadastrado com sucesso!\n");
}

void menuAtualiza() {
    printf("O que você quer atualizar?\n");
    printf("1 - Nome\n");
    printf("2 - Telefone\n");
    printf("3 - Email\n");
    printf("4 - Endereco\n");
    printf("0 - Sair\n");
}

void atualizaContato() {
    char nome[50], email[100], endereco[150];
    int telefone;
    int linha, contador = 1;

    char nomeNovo[50], emailNovo[100], enderecoNovo[150];
    int telefoneNovo;

    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar arquivo temporário.\n");
        fclose(arq);
        return;
    }

    printf("\n=== Atualizar Contato ===\n");

    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF) {
        printf("%d - Nome: %s | Telefone: %d | Email: %s | Endereco: %s\n",
               contador, nome, telefone, email, endereco);
        contador++;
    }

    printf("Escolha uma linha para atualizar: ");
    scanf("%d", &linha);
    getchar(); 

    rewind(arq);
    contador = 1;
    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF) {
        if (linha == contador) {
            strcpy(nomeNovo, nome);
            telefoneNovo = telefone;
            strcpy(emailNovo, email);
            strcpy(enderecoNovo, endereco);
        }
        contador++;
    }

    int opcao;
    while (1) {
        printf("\n=== Menu de Atualizacao ===\n");
        printf("1 - Atualizar nome\n");
        printf("2 - Atualizar telefone\n");
        printf("3 - Atualizar email\n");
        printf("4 - Atualizar endereco\n");
        printf("0 - Salvar e sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        if (opcao == 1) {
            printf("Novo nome: ");
            scanf("%[^\n]", nomeNovo);
            getchar();
        } else if (opcao == 2) {
            printf("Novo telefone: ");
            scanf("%d", &telefoneNovo);
            getchar();
        } else if (opcao == 3) {
            printf("Novo email: ");
            scanf("%[^\n]", emailNovo);
            getchar();
        } else if (opcao == 4) {
            printf("Novo endereco: ");
            scanf("%[^\n]", enderecoNovo);
            getchar();
        } else if (opcao == 0) {
            printf("Salvando as informacoes...\n");
            break;
        } else {
            printf("Opcao invalida.\n");
        }
    }

    rewind(arq);
    contador = 1;
    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF) {
        if (linha == contador)
            fprintf(temp, "%s;%d;%s;%s\n", nomeNovo, telefoneNovo, emailNovo, enderecoNovo);
        else
            fprintf(temp, "%s;%d;%s;%s\n", nome, telefone, email, endereco);
        contador++;
    }

    fclose(arq);
    fclose(temp);

    remove("agenda.txt");
    rename("temp.txt", "agenda.txt");

    printf("Linha %d atualizada com sucesso!\n", linha);
}

void removeContato() {
    char nome[50];
    printf("\n=== Remover Contato ===\n");
    printf("Digite o nome do contato: ");
    scanf(" %[^\n]", nome);

    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Erro ao criar arquivo temporario.\n");
        fclose(arq);
        return;
    }

    char nomeArq[50], emailArq[100], enderecoArq[150];
    int telefoneArq;
    int encontrado = 0;

    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nomeArq, &telefoneArq, emailArq, enderecoArq) != EOF) {
        if (strcmp(nomeArq, nome) != 0)
            fprintf(temp, "%s;%d;%s;%s\n", nomeArq, telefoneArq, emailArq, enderecoArq);
        else
            encontrado = 1;
    }

    fclose(arq);
    fclose(temp);

    if (encontrado) {
        remove("agenda.txt");
        rename("temp.txt", "agenda.txt");
        printf("Contato removido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Contato nao encontrado.\n");
    }
}

void buscaContato() {
    char nomeBusca[50], telefoneBusca[15], emailBusca[100], enderecoBusca[150];
    char nome[50], email[100], endereco[150];
    int telefone, encontrado = 0, opcao;

    printf("\n=== Buscar Contato ===\n");
    printf("1 - Nome\n2 - Telefone\n3 - Email\n4 - Endereco\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();

    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    if (opcao == 1) {
        printf("Nome: ");
        scanf(" %[^\n]", nomeBusca);
        while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF)
            if (strcmp(nome, nomeBusca) == 0)
                printf("Encontrado: %s | %d | %s | %s\n", nome, telefone, email, endereco), encontrado = 1;
    } else if (opcao == 2) {
        printf("Telefone: ");
        scanf(" %[^\n]", telefoneBusca);
        while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF) {
            char telStr[15];
            sprintf(telStr, "%d", telefone);
            if (strcmp(telStr, telefoneBusca) == 0)
                printf("Encontrado: %s | %d | %s | %s\n", nome, telefone, email, endereco), encontrado = 1;
        }
    } else if (opcao == 3) {
        printf("Email: ");
        scanf(" %[^\n]", emailBusca);
        while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF)
            if (strcmp(email, emailBusca) == 0)
                printf("Encontrado: %s | %d | %s | %s\n", nome, telefone, email, endereco), encontrado = 1;
    } else if (opcao == 4) {
        printf("Endereco: ");
        scanf(" %[^\n]", enderecoBusca);
        while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF)
            if (strcmp(endereco, enderecoBusca) == 0)
                printf("Encontrado: %s | %d | %s | %s\n", nome, telefone, email, endereco), encontrado = 1;
    }

    if (!encontrado)
        printf("Contato nao encontrado.\n");

    fclose(arq);
}

void contataContatos() {
    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    int count = 0;
    char nome[50], email[100], endereco[150];
    int telefone;

    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF)
        count++;

    fclose(arq);
    printf("\nTotal de contatos: %d\n", count);
}

void exibeMenu() {
    printf("\n=== Menu de Contatos ===\n");
    printf("1 - Cadastrar\n");
    printf("2 - Buscar\n");
    printf("3 - Atualizar\n");
    printf("4 - Remover\n");
    printf("5 - Listar todos\n");
    printf("6 - Total de contatos\n");
    printf("0 - Sair\n");
}