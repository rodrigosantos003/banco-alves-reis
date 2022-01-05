/*
    @name: Banco Alves dos Reis
    @description: Porgrama de gestão bancária
    @authors: João Fernandes & Rodrigo Santos
    @last_modified: 2021-01-05
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "conta.h"

#define MAX_CONTAS 100

void mostrarMenu(void);
void operacoesMenu(int opcao, TipoConta contas[], int numAtualContas);

int main()
{
    setlocale(LC_ALL, "");

    //declaração de variáveis
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
    char listagem, sair;
    int contaOrigem, contaDestino;

    contaOrigem = contaDestino = 0;

    //leitura da opção do menu
    printf("Escolha uma opcão do menu: ");
    scanf("%d", &opcao);
    fflush(stdin);

    //verificação da opção e execução das respetivas operações
    switch(opcao){
        case 1: /*abertura de conta*/
            if(numAtualContas < MAX_CONTAS){
                abrirConta(&contas[numAtualContas], numAtualContas);
                numAtualContas++;
            }
            else
                printf("\nERRO: Não é possível abrir mais contas!\n");

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 2: /*listagem de todas as contas*/
            printf("Listar todas as contas registadas (T) ou contas de um determinado cliente (C)? ");
            scanf("%c", &listagem);

            if(listagem == 'T' || listagem == 't')
                listarTodasContas(contas, numAtualContas);
            else if(listagem == 'C' || listagem == 'c')
                listarContasCliente(contas, numAtualContas);
            else
                printf("ERRO: Opção inválida!");

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 3: /*consulta dos detalhes de uma conta*/
            do{
                contaOrigem = lerNumConta(contas, numAtualContas);
            }while(contaOrigem == -1);

            imprimirConta(contas[2-1]);

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 4: /*depósito de dinheiro*/
            do{
                contaOrigem = lerNumConta(contas, numAtualContas);
            }while(contaOrigem == -1);

            depositarDinheiro(&contas[contaOrigem]);

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 5: /*levantamento de dinheiro*/
            do{
                contaOrigem = lerNumConta(contas, numAtualContas);
            }while(contaOrigem == -1);

            levantarDinheiro(&contas[contaOrigem]);

            mostrarMenu();
            operacoesMenu(opcao, contas, numAtualContas);
            break;
        case 6: /*transferência de dinheiro*/
            do{
                contaOrigem = lerNumConta(contas, numAtualContas);
                contaDestino = lerNumConta(contas, numAtualContas);
            }while(contaOrigem == -1 || contaDestino == -1);

            transferirDinheiro(&contas[contaOrigem], &contas[contaDestino]);

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
                printf("\nERRO: Resposta inválida!\n");
                mostrarMenu();
                operacoesMenu(opcao, contas, numAtualContas);
            }
            break;
        default: /*opção do menu não existente*/
            printf("\nERRO: A opção escolhida não existe!\n");
            operacoesMenu(opcao, contas, numAtualContas);
    }
}
