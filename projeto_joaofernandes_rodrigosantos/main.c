/*
    @name: Banco Alves dos Reis
    @description: Porgrama de gestão bancária
    @authors: João Fernandes & Rodrigo Santos
    @last_modified: 2021-12-12
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void menu(void);

int main()
{
    setlocale(LC_ALL, "");

    printf("BANCO ALVES DOS REIS\n");
    menu();

    return 0;
}

void menu() {
    int opcaoMenu;

    printf("1. Abrir uma conta\n");
    printf("2. Listar contas existentes\n");
    printf("3. Consultar detalhes de uma conta\n");
    printf("4. Depositar dinheiro numa conta\n");
    printf("5. Levantar dinheiro de uma conta\n");
    printf("6. Transferir dinheiro entre contas\n");
    printf("7. Editar a informação de uma conta\n");
    printf("8. Eliminar uma conta\n");
    printf("9. Gravar listagem de contas para um ficheiro de texto\n\n");
    printf("10. Sair do programa\n");

    printf("Escolha uma opcão do menu: ");
    scanf("%d", &opcaoMenu);

    fflush(stdin);

    switch(opcaoMenu){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            exit(0);
            break;
    }
}
