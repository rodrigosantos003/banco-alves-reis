/*
    @name: Banco Alves dos Reis
    @description: Porgrama de gestão bancária
    @authors: João Fernandes & Rodrigo Santos
    @last_modified: 2021-01-03
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "conta.h"

#define MAX_CONTAS 100

void mostrarMenu(void);
void operacoesMenu(int opcao, TipoConta contas[], int numAtualContas);
void gravarListagemContas();

int main()
{
    setlocale(LC_ALL, "");

    //declaração e variáveis
    TipoConta contas[MAX_CONTAS];
    int numAtualContas, opcaoMenu;

    //inicialização das variáveis inteiras a zero
    opcaoMenu = numAtualContas = 0;

    //chamada das funções mostrarMenu() e operacoesMenu()
    mostrarMenu();
    operacoesMenu(opcaoMenu, contas, numAtualContas);

    return 0;
}

//função que apresenta o menu
void mostrarMenu()
{
    printf("BANCO ALVES DOS REIS\n");

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
}

//função que executa as operações do menu (dada a respetiva opção)
void operacoesMenu(int opcao, TipoConta contas[], int numAtualContas){
    char sair;

    printf("Escolha uma opcão do menu: ");
    scanf("%d", &opcao);
    fflush(stdin);

    switch(opcao){
        case 1: /*abertura de conta*/
            abrirConta(&contas[numAtualContas]);
            numAtualContas++;
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 2: /*listagem de todas as contas*/
            for(int i = 0; i < numAtualContas; i++){
                imprimirConta(contas[i]);
                printf("\n");
            }

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 3: /*consulta dos detalhes de uma conta*/
            consultarDetalhesConta(contas, numAtualContas);
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 4: /*depósito de dinheiro*/
            depositarDinheiro(&contas[0]);
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 5: /*levantamento de dinheiro*/
            levantarDinheiro(&contas[0]);
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 6: /*transferência de dinheiro*/
            transferirDinheiro(&contas[0], &contas[1]);
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 7: /*edição de informações de conta*/
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 8: /*eliminação de conta*/
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 9: /*eliminação de conta*/
            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 10: /*saída do programa*/
            printf("Deseja sair do programa (S/N)? ");
            scanf("%c", &sair);

            if(sair == 's' || sair == 'S')
                exit(0);
            else if(sair == 'n' || sair == 'N'){
                mostrarMenu();
                operacoesMenu(opcao, contas, numAtualContas);
            }
            else{
                printf("ERRO: Resposta inválida!");
                mostrarMenu();
                operacoesMenu(opcao, contas, numAtualContas);
            }
            break;
        default: /*opção do menu não existente*/
            printf("ERRO: A opção escolhida não existe! Tente novamente\n");
            operacoesMenu(opcao, contas, numAtualContas);
    }
}
