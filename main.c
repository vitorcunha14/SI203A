#include <stdio.h>
#include <string.h>

// typedef struct{
//     char nome[50];
//     int telefone;
//     char email[100];
//     char endereco[150];
// } Contato;

void exibeAgenda(){
    char nome[50];
    int telefone;
    char email[100];
    char endereco[150];

    printf("\n=== Agenda de Contatos ===\n");
    FILE *arq = fopen("agenda.txt", "r");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo.\n");
        return;
    }
    while(fscanf(arq, "%s %d %s %s", nome, &telefone, email, endereco) != EOF){
        printf("Nome: %s | Telefone: %d | Email: %s | Endereco: %s\n", nome, telefone, email, endereco);
    }
    fclose(arq);

}


void escreveAgenda(){
    char nome[50];
    int telefone;
    char email[100];
    char endereco[150];

    printf("\n=== Cadastrar Contato ===\n");
    printf("Nome: ");
    scanf("%s", nome);
    printf("Telefone: ");
    scanf("%d", &telefone);
    printf("Email: ");
    scanf("%s", email);
    printf("Endereco: ");
    scanf("%s", endereco);

    FILE *arq = fopen("agenda.txt", "a");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arq, "\n");
    fprintf(arq, "%s %d %s %s\n", nome, telefone, email, endereco);
    fclose(arq);
    printf("Contato cadastrado com sucesso!\n");
}

void removeContato(){
    char nome[50];
    printf("\n=== Remover Contato ===\n");
    printf("Digite o nome do contato que deseja remover: ");
    scanf("%s", nome);

    FILE *arq = fopen("agenda.txt", "r");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temporario = fopen("temp.txt", "w");
    if(temporario == NULL){
        perror("Erro ao criar arquivo temporario.\n");
        fclose(arq);
        return;
    }

    char nomeArq[50];
    int telefoneArq;
    char emailArq[100];
    char enderecoArq[150];
    int encontrado = 0;

    while(fscanf(arq, "%s %d %s %s", nomeArq, &telefoneArq, emailArq, enderecoArq) != EOF){
        if(strcmp(nomeArq, nome) != 0){
            fprintf(temporario, "%s %d %s %s\n", nomeArq, telefoneArq, emailArq, enderecoArq);
        } else {
            encontrado = 1;
        }
    }

    fclose(arq);
    fclose(temporario);

    if(encontrado){
        remove("agenda.txt");
        rename("temp.txt", "agenda.txt");
        printf("Contato removido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Contato nao encontrado.\n");
    }
}

void buscaContato(){
    char nomeBusca[50];
    char telefoneBusca[15];
    char emailBusca[100];
    char enderecoBusca[150];
    
    char nome[50];
    int telefone;
    char email[100];
    char endereco[150];
    int encontrado = 0;

    int opcao;


    printf("\n=== Buscar Contato ===\n");
    printf("Escolha uma opcao: \n");
    printf("1 - Buscar por nome\n");
    printf("2 - Buscar por telefone\n");
    printf("3 - Buscar por email\n");
    printf("4 - Buscar por endereco\n");

    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    FILE *arq = fopen("agenda.txt", "r");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo.\n");
        return;
    }

    if(opcao == 1){
        printf("Digite o nome do contato: ");
        scanf("%s", nomeBusca);
        while(fscanf(arq, "%s %d %s %s", nome, &telefone, email, endereco) != EOF){
            if(strcmp(nome, nomeBusca) == 0){
                printf("Contato encontrado: Nome: %s | Telefone: %d | Email: %s | Endereco: %s\n", nome, telefone, email, endereco);
                encontrado = 1;
            }
        }
    } else if(opcao == 2){
        printf("Digite o telefone do contato: ");
        scanf("%s", telefoneBusca);
        while(fscanf(arq, "%s %d %s %s", nome, &telefone, email, endereco) != EOF){
            char telefoneStr[15];
            sprintf(telefoneStr, "%d", telefone);
            if(strcmp(telefoneStr, telefoneBusca) == 0){
                printf("Contato encontrado: Nome: %s | Telefone: %d | Email: %s | Endereco: %s\n", nome, telefone, email, endereco);
                encontrado = 1;
            }
        }
    } else if(opcao == 3){
        printf("Digite o email do contato: ");
        scanf("%s", emailBusca);
        while(fscanf(arq, "%s %d %s %s", nome, &telefone, email, endereco) != EOF){
            if(strcmp(email, emailBusca) == 0){
                printf("Contato encontrado: Nome: %s | Telefone: %d | Email: %s | Endereco: %s\n", nome, telefone, email, endereco);
                encontrado = 1;
            }
        }
    } else if(opcao == 4){
        printf("Digite o endereco do contato: ");
        scanf("%s", enderecoBusca);
        while(fscanf(arq, "%s %d %s %s", nome, &telefone, email, endereco) != EOF){
            if(strcmp(endereco, enderecoBusca) == 0){
                printf("Contato encontrado: Nome: %s | Telefone: %d | Email: %s | Endereco: %s\n", nome, telefone, email, endereco);
                encontrado = 1;
            }
        }
    } else {
        printf("Opcao invalida.\n");
    }

    if(!encontrado){
        printf("Contato nao encontrado.\n");
    }
    fclose(arq);
}

void contataContatos(){
    FILE *arq = fopen("agenda.txt", "r");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo.\n");
        return;
    }
    int count = 0;
    char nome[50];
    int telefone;
    char email[100];
    char endereco[150];
    while(fscanf(arq, "%s %d %s %s", nome, &telefone, email, endereco) != EOF){
        count++;
    }
    fclose(arq);
    
    printf("\n=== Consultar Total de Contatos ===\n");
    printf("Total de contatos na agenda: %d\n", count);
}


void exibeMenu(){
    printf("=== Menu de Contatos ===\n");
    printf("1 - Cadastrar contato\n");
    printf("2 - Buscar contatos\n");
    printf("3 - Atualizar contato\n");
    printf("4 - Deletar contato\n");
    printf("5 - Listar todos os contatos\n");
    printf("6 - Consultar total de contatos\n");
    printf("0 - Sair\n");
}

int main() {
    
    while(1){
        exibeMenu();
        int opcao;
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Cadastrar contato selecionado.\n");
                escreveAgenda();
                break;
            case 2:
                printf("Buscar contatos selecionado.\n");
                buscaContato();
                break;
            case 3:
                printf("Atualizar contato selecionado.\n");
                break;
            case 4:
                printf("Deletar contato selecionado.\n");
                removeContato();
                break;
            case 5:
                printf("\nListar todos os contatos selecionado.\n");
                exibeAgenda();
                break;
            case 6:
                printf("Consultar total de contatos selecionado.\n");
                contataContatos();
                break;
            case 0:
                printf("Saindo do programa.\n");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        printf("\n");
    }

    return 0;
}