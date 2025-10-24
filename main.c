#include <stdio.h>
#include "agenda.h"

int main() {
    int opcao;
    while (1) {
        exibeMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: escreveAgenda(); break;
            case 2: buscaContato(); break;
            case 3: atualizaContato(); break;
            case 4: removeContato(); break;
            case 5: exibeAgenda(); break;
            case 6: contataContatos(); break;
            case 0: printf("Saindo...\n"); return 0;
            default: printf("Opcao invalida.\n");
        }
    }
}
