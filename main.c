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

    printf("=== Agenda de Contatos ===\n");
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

    printf("=== Cadastrar Contato ===\n");
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

void buscaContato(){
    char nomeBusca[50];
    char nome[50];
    int telefone;
    char email[100];
    char endereco[150];
    int encontrado = 0;

    printf("=== Buscar Contato ===\n");
    printf("Digite o nome do contato que deseja buscar: ");
    scanf("%s", nomeBusca);

    FILE *arq = fopen("agenda.txt", "r");
    if(arq == NULL){
        perror("Erro ao abrir o arquivo.\n");
        return;
    }
    while(fscanf(arq, "%s %d %s %s", nome, &telefone, email, endereco) != EOF){
        if(strcmp(nome, nomeBusca) == 0){
            printf("Contato encontrado:\n");
            printf("Nome: %s | Telefone: %d | Email: %s | Endereco: %s\n", nome, telefone, email, endereco);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado){
        printf("Contato nao encontrado.\n");
    }
    fclose(arq);
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
                break;
            case 5:
                printf("\nListar todos os contatos selecionado.\n");
                exibeAgenda();
                break;
            case 6:
                printf("Consultar total de contatos selecionado.\n");
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