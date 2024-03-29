#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "conta.h"
#include "gestao.h"
#include "movimentacoes.h"

//fun��o para leitura do n�mero de conta e verifica��o da sua exist�ncia
int lerNumConta(TipoConta contas[], int numAtualContas)
{
    int numConta = 0;
    int encontrado, direita, esquerda, meio;

    //leitura do n�mero de conta
    printf("Introduza o n�mero de conta: ");
    scanf("%d", &numConta);
    fflush(stdin);

    encontrado = 0;
    esquerda = 0;
    direita = numAtualContas - 1;

    //pesquisa bin�ria do n�mero introduzido no array de contas
    while(esquerda <= direita && !encontrado)
    {
        meio = (direita + esquerda) / 2;

        if(contas[meio].numero == numConta)
            encontrado = 1;
        else if(numConta < contas[meio].numero)
            direita = meio - 1;
        else
            esquerda = meio + 1;
    }

    //se a conta existir � retornada a sua posi��o no array
    if(encontrado)
        return meio;

    //sen�o � escrito no ecr� que a conta n�o existe e � retornado o valor de "erro" (i.e -1)
    printf("\nERRO: A conta n�o existe!\n");
    return -1;
}

//fun��o para abertura de conta
void abrirConta(TipoConta *conta, int numAtualContas)
{
    int quantidadeDigitos;

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t); /*retorna os valores da data local*/

    printf("INTRODUZA OS DADOS DA CONTA:\n\n");

    //atribui��o do n�mero de conta
    conta->numero = numAtualContas + 1;

    //leitura do n�mero de titulares
    do
    {
        printf("N� de titulares > ");
        scanf("%d", &conta->totalTitulares);
        fflush(stdin);

        if(conta->totalTitulares > 5)
            printf("\nERRO: A conta deve ter at� 5 titulares!\n");
        else if(conta->totalTitulares <= 0)
            printf("\nERRO: O n�mero de titulares deve ser maior que 0!\n");
    }
    while(conta->totalTitulares > 5 || conta->totalTitulares <= 0);

    //leitura dos dados dos titulares
    for(int i = 0; i < conta->totalTitulares; i++)
    {
        printf("TITULAR %d\n", i+1);

        do
        {
            printf("NIF > ");
            scanf("%d", &conta->titulares[i].nif);
            fflush(stdin);

            if(conta->titulares[i].nif < 100000000 || conta->titulares[i].nif > 999999999)
                printf("\nERRO: NIF inv�lido!\n");

        }
        while(conta->titulares[i].nif < 100000000 || conta->titulares[i].nif > 999999999);

        do
        {
            printf("Nome > ");
            gets(conta->titulares[i].nome);
            fflush(stdin);

            if(strcmp(conta->titulares[i].nome, "") == 0)
                printf("\nERRO: O nome deve estar preenchido!\n");

            quantidadeDigitos = 0;
            for(int j = 0; j < strlen(conta->titulares[i].nome); j++)
            {
                if(isdigit(conta->titulares[i].nome[j]))
                    quantidadeDigitos++;
            }

            if(quantidadeDigitos != 0)
                printf("\nERRO: O nome n�o deve conter d�gitos!\n");
        }
        while(strcmp(conta->titulares[i].nome, "") == 0 || quantidadeDigitos != 0);
    }

    //leitura da modalidade
    do
    {
        printf("Modalidade da Conta (Normal:0 / Isenta:1) > ");
        scanf("%u", &conta->modalidade);
        fflush(stdin);

        if(conta->modalidade < 0 || conta->modalidade > 1)
            printf("\nERRO: A modalidade deve ser 0 ou 1, Normal ou Isenta respetivamente!\n");
    }
    while(conta->modalidade < 0 || conta->modalidade > 1);


    //leitura do saldo inicial
    do
    {
        printf("Saldo > ");
        scanf("%f", &conta->saldo);
        fflush(stdin);

        if(conta->saldo < 150)
            printf("\nERRO: O saldo inicial deve ser igual ou superior a 150 EUR!\n");
    }
    while(conta->saldo < 150);


    //atribui��o da data de abertura (atrav�s da data local)
    conta->data.dia = tm.tm_mday;
    conta->data.mes = tm.tm_mon+1;
    conta->data.ano = tm.tm_year+1900;
}

//fun��o para escrever os detalhes de uma conta
void imprimirConta(TipoConta conta)
{
    printf("\n----------------\n");

    printf("N�mero: %d\n\n", conta.numero);

    printf("TITULARES:\n");
    for(int i = 0; i < conta.totalTitulares; i++)
    {
        printf("\t%d ", i+1);
        printf("| Nome: %-26s", conta.titulares[i].nome);
        printf(" | NIF: %d\n", conta.titulares[i].nif);
    }

    if(conta.modalidade == normal)
        printf("\nModalidade: Normal\n");
    else
        printf("\nModalidade: Isenta\n");

    printf("\nSaldo:\t%.2f EUR \n", conta.saldo);

    printf("\nHIST�RICO (�ltimos 3 movimentos):\n");
    for(int i = 0; i < 3; i++)
    {
        printf("\tDescri��o: %-25s | ", conta.historico[i].descricao);
        printf("Valor: %.2f\n", conta.historico[i].valor);
    }

    printf("\nData de abertura: %02d/%02d/%4d\n", conta.data.dia, conta.data.mes, conta.data.ano);

    printf("----------------\n");
}


//fun��o para edi��o dos detalhes da conta
void editarDetalhesConta(TipoConta *conta)
{
    char resposta;
    int numTitulares, quantidadeDigitos;

    printf("Pretende alterar o tipo de conta? (S/N) ");
    scanf("%c", &resposta);
    fflush(stdin);

    if(resposta == 'S' || resposta == 's')
    {
        do
        {
            //leitura do novo tipo de conta
            printf("Novo tipo de conta (Normal:0 / Isenta:1) > ");
            scanf("%u", &conta->modalidade);
            fflush(stdin);

            if(conta->modalidade < 0 || conta->modalidade > 1)
                printf("\nERRO: A modalidade deve ser 0 ou 1, Normal ou Isenta respetivamente!\n");
        }
        while(conta->modalidade < 0 || conta->modalidade > 1);
    }
    else if(resposta != 'n' || resposta != 'N')
        printf("\nERRO: Resposta inv�lida!\n");

    printf("Pretende adicionar titulares? (S/N) ");
    scanf("%c", &resposta);
    fflush(stdin);

    if(resposta == 'S' || resposta == 's')
    {
        printf("N� de titulares a adicionar > ");
        scanf("%d", &numTitulares);
        fflush(stdin);

        if(conta->totalTitulares + numTitulares <= 5)
        {
            //leitura dos novos titulares
            for(int i = conta->totalTitulares; i < conta->totalTitulares + numTitulares; i++)
            {
                printf("TITULAR %d\n", i+1);

                do
                {
                    printf("NIF > ");
                    scanf("%d", &conta->titulares[i].nif);
                    fflush(stdin);

                    if(conta->titulares[i].nif < 100000000 || conta->titulares[i].nif > 999999999)
                        printf("\nERRO: NIF inv�lido!\n");

                }
                while(conta->titulares[i].nif < 100000000 || conta->titulares[i].nif > 999999999);

                do
                {
                    printf("Nome > ");
                    gets(conta->titulares[i].nome);
                    fflush(stdin);

                    if(strcmp(conta->titulares[i].nome, "") == 0)
                        printf("\nERRO: O nome deve estar preenchido!\n");

                    quantidadeDigitos = 0;
                    for(int j = 0; j < strlen(conta->titulares[i].nome); j++)
                    {
                        if(isdigit(conta->titulares[i].nome[j]))
                            quantidadeDigitos++;
                    }

                    if(quantidadeDigitos != 0)
                        printf("\nERRO: O nome n�o deve conter d�gitos!\n");
                }
                while(strcmp(conta->titulares[i].nome, "") == 0 || quantidadeDigitos != 0);
            }

            conta->totalTitulares += numTitulares;
        }
        else
            printf("\nERRO: O n�mero de titulares ultrapassa o limite!\n");
    }
    else if(resposta != 'n' || resposta != 'N')
        printf("\nERRO: Resposta inv�lida!\n");
}

//fun��o para eliminar uma conta
void eliminarConta(TipoConta contas[], int numAtualContas, int indiceApagar)
{
    for(int i = indiceApagar; i < numAtualContas; i++)
    {
        contas[i] = contas[i+1];
    }

    printf("\nConta eliminada com sucesso!\n");
}
