/*
    @name: Banco Alves dos Reis
    @description: Porgrama de gestão bancária
    @authors: João Fernandes & Rodrigo Santos
    @last_modified: 2021-11-16
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    //declaração de variáveis
    int opcaoMenu;

    printf("BANCO ALVES DOS REIS\n");

    //menu do programa
    do{
        printf("1. Abrir uma conta\n");
        printf("2. Listar contas existentes\n");
        printf("3. Consultar detalhes de uma conta\n");
        printf("4. Depositar dinheiro numa conta\n");
        printf("5. Levantar dinheiro de uma conta\n");
        printf("6. Transferir dinheiro entre contas\n");
        printf("7. Editar a informacao de uma conta\n");
        printf("8. Eliminar uma conta\n");
        printf("9. Gravar listagem de contas para um ficheiro de texto\n\n");
        printf("10. Sair do programa\n");

        printf("Escolha uma opcao do menu: ");
        scanf("%d", &opcaoMenu);

        /*
        switch(opcaoMenu){

        }
        */

    }while(opcaoMenu != 10);

    return 0;
}
