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
        perror("erro ao abrir arquivo\n");
        return;
    }

    // le cada contato do arquivo e exibe
    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF) {
        printf("nome: %s | telefone: %d | email: %s | endereco: %s\n", nome, telefone, email, endereco);
    }

    fclose(arq);
}

void escreveAgenda() {
    char nome[50];
    int telefone;
    char email[100];
    char endereco[150];

    printf("\n=== cadastrar contato ===\n");

    printf("nome: ");
    scanf(" %[^\n]", nome);
    printf("telefone: ");
    scanf("%d", &telefone);
    getchar(); // limpa buffer
    printf("email: ");
    scanf(" %[^\n]", email);
    printf("endereco: ");
    scanf(" %[^\n]", endereco);

    FILE *arq = fopen("agenda.txt", "a");
    if (arq == NULL) {
        perror("erro ao abrir arquivo\n");
        return;
    }

    // escreve contato no arquivo
    fprintf(arq, "%s;%d;%s;%s\n", nome, telefone, email, endereco);
    fclose(arq);

    printf("contato cadastrado com sucesso\n");
}

void atualizaContato() {
    char nome[50], email[100], endereco[150];
    int telefone;
    int linha, contador = 1;

    char nomeNovo[50], emailNovo[100], enderecoNovo[150];
    int telefoneNovo;

    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("erro ao abrir arquivo\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("erro ao criar arquivo temporario\n");
        fclose(arq);
        return;
    }

    printf("\n=== atualizar contato ===\n");

    // lista contatos para usuario escolher
    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF) {
        printf("%d - nome: %s | telefone: %d | email: %s | endereco: %s\n",
               contador, nome, telefone, email, endereco);
        contador++;
    }

    printf("escolha linha para atualizar: ");
    scanf("%d", &linha);
    getchar(); // limpa buffer

    // encontra contato selecionado
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
        printf("\n=== menu atualizacao ===\n");
        printf("1 - atualizar nome\n");
        printf("2 - atualizar telefone\n");
        printf("3 - atualizar email\n");
        printf("4 - atualizar endereco\n");
        printf("0 - salvar e sair\n");
        printf("escolha opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        if (opcao == 1) {
            printf("novo nome: ");
            scanf("%[^\n]", nomeNovo);
            getchar();
        } else if (opcao == 2) {
            printf("novo telefone: ");
            scanf("%d", &telefoneNovo);
            getchar();
        } else if (opcao == 3) {
            printf("novo email: ");
            scanf("%[^\n]", emailNovo);
            getchar();
        } else if (opcao == 4) {
            printf("novo endereco: ");
            scanf("%[^\n]", enderecoNovo);
            getchar();
        } else if (opcao == 0) {
            printf("salvando informacoes...\n");
            break;
        } else {
            printf("opcao invalida\n");
        }
    }

    // reescreve arquivo com contato atualizado
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

    printf("linha %d atualizada com sucesso\n", linha);
}

void removeContato() {
    char nome[50];
    printf("\n=== remover contato ===\n");
    printf("digite nome do contato: ");
    scanf(" %[^\n]", nome);

    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("erro ao abrir arquivo\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("erro ao criar arquivo temporario\n");
        fclose(arq);
        return;
    }

    char nomeArq[50], emailArq[100], enderecoArq[150];
    int telefoneArq;
    int encontrado = 0;

    // copia todos contatos exceto o removido
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
        printf("contato removido com sucesso\n");
    } else {
        remove("temp.txt");
        printf("contato nao encontrado\n");
    }
}

void buscaContato() {
    char nomeBusca[50], telefoneBusca[15], emailBusca[100], enderecoBusca[150];
    char nome[50], email[100], endereco[150];
    int telefone, encontrado = 0, opcao;

    printf("\n=== buscar contato ===\n");
    printf("1 - nome\n2 - telefone\n3 - email\n4 - endereco\n");
    printf("escolha: ");
    scanf("%d", &opcao);
    getchar();

    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("erro ao abrir arquivo\n");
        return;
    }

    // busca por criterio escolhido
    if (opcao == 1) {
        printf("nome: ");
        scanf(" %[^\n]", nomeBusca);
        while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF)
            if (strcmp(nome, nomeBusca) == 0)
                printf("encontrado: %s | %d | %s | %s\n", nome, telefone, email, endereco), encontrado = 1;
    } else if (opcao == 2) {
        printf("telefone: ");
        scanf(" %[^\n]", telefoneBusca);
        while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF) {
            char telStr[15];
            sprintf(telStr, "%d", telefone);
            if (strcmp(telStr, telefoneBusca) == 0)
                printf("encontrado: %s | %d | %s | %s\n", nome, telefone, email, endereco), encontrado = 1;
        }
    } else if (opcao == 3) {
        printf("email: ");
        scanf(" %[^\n]", emailBusca);
        while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF)
            if (strcmp(email, emailBusca) == 0)
                printf("encontrado: %s | %d | %s | %s\n", nome, telefone, email, endereco), encontrado = 1;
    } else if (opcao == 4) {
        printf("endereco: ");
        scanf(" %[^\n]", enderecoBusca);
        while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF)
            if (strcmp(endereco, enderecoBusca) == 0)
                printf("encontrado: %s | %d | %s | %s\n", nome, telefone, email, endereco), encontrado = 1;
    }

    if (!encontrado)
        printf("contato nao encontrado\n");

    fclose(arq);
}

void contataContatos() {
    FILE *arq = fopen("agenda.txt", "r");
    if (arq == NULL) {
        perror("erro ao abrir arquivo\n");
        return;
    }

    int count = 0;
    char nome[50], email[100], endereco[150];
    int telefone;

    // conta total de contatos
    while (fscanf(arq, "%49[^;];%d;%99[^;];%149[^\n]\n", nome, &telefone, email, endereco) != EOF)
        count++;

    fclose(arq);
    printf("\ntotal de contatos: %d\n", count);
}

void exibeMenu() {
    printf("\n=== menu de contatos ===\n");
    printf("1 - cadastrar\n");
    printf("2 - buscar\n");
    printf("3 - atualizar\n");
    printf("4 - remover\n");
    printf("5 - listar todos\n");
    printf("6 - total de contatos\n");
    printf("0 - sair\n");
}