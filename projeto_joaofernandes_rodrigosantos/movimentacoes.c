#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "conta.h"
#include "gestao.h"
#include "movimentacoes.h"

//função para verificação de saldo suficiente
int verificarSaldoConta(TipoConta *conta, float montante)
{
    //se o saldo for superior ao montante recebido é retornado 1 (i.e verdadeiro)
    if(conta->saldo >= montante)
        return 1;
    //senão é retornado 0 (i.e falso)
    return 0;
}

//função para depósito de dinheiro numa conta
void depositarDinheiro(TipoConta *conta)
{
    float montante = 0.0F;

    //leitura do montante a depositar
    do
    {
        printf("Montante a depositar > ");
        scanf("%f", &montante);
        fflush(stdin);

        if(montante <= 0)
            printf("\nERRO: O montante deve ser superior a 0!\n");
    }
    while(montante <= 0);

    //introdução do montante no saldo da conta
    conta->saldo += montante;
    printf("\nMontante depositado com sucesso (%.2f EUR)!\n", montante);

    //chamada da função atualizarHistorico() para atualização do histórico de movimentos
    atualizarHistorico(conta, montante, "Depósito");
}

//função para levantamento de dinheiro de uma conta
void levantarDinheiro(TipoConta *conta)
{
    float montante = 0.0F;
    int saldoSuficiente = 0;
    int aprovacao;

    //leitura do montante a levantar
    do
    {
        printf("Montante a levantar > ");
        scanf("%f", &montante);
        fflush(stdin);

        if(montante <= 0)
            printf("\nERRO: O montante deve ser superior a 0!\n");
    }
    while(montante <= 0);

    if(montante >= 400)
    {
        printf("\nAVISO: O montante indicado é considerado um movimento suspeito!\n");
        printf("Iremos proceder a perguntas de segurança!\n");

        aprovacao = aprovarTransacao(conta);
    }
    else
        aprovacao = 1;


    if(aprovacao == 1)
    {
        //verificação da modalidade da conta, verificação de saldo suficiente e realização da operação
        if(conta->modalidade == normal)
        {
            saldoSuficiente = verificarSaldoConta(conta, montante + 5);

            if(saldoSuficiente == 1)
            {
                conta->saldo -= montante + 5;
                printf("\nMontante levantada com sucesso (%.2f EUR)!\n", montante);

                //chamada da função atualizarHistorico() para atualização do histórico de movimentos
                atualizarHistorico(conta, montante, "Levantamento");
            }
            else printf("\nERRO: Saldo insuficiente!\n");
        }
        else
        {
            saldoSuficiente = verificarSaldoConta(conta, montante);

            if(saldoSuficiente == 1)
            {
                conta->saldo -= montante;
                printf("\nMontante levantada com sucesso (%.2f EUR)!\n", montante);

                //chamada da função atualizarHistorico() para atualização do histórico de movimentos
                atualizarHistorico(conta, montante, "Levantamento");
            }
            else printf("\nERRO: Saldo insuficiente!\n");

        }
    }
    else
        printf("\nERRO: A aprovação da transação falhou!\n");

}

//função para transferência de dinheiro entre contas
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino)
{
    float montante = 0.0F;
    int saldoSuficiente = 0;
    int aprovacao;

    //leitura do montante a transferir
    do
    {
        printf("Montante a transferir > ");
        scanf("%f", &montante);
        fflush(stdin);

        if(montante <= 0)
            printf("\nERRO: O montante deve ser superior a 0!\n");
    }
    while(montante <= 0);

    if(montante >= 400)
    {
        printf("\nAVISO: O montante indicado é consideraddo um movimento suspeito.\n");
        printf("Iremos proceder a perguntas de segurança!\n");

        aprovacao = aprovarTransacao(contaOrigem);
    }
    else
        aprovacao = 1;

    if(aprovacao == 1)
    {
        //verificação da modalidade da conta, verificação de saldo suficiente e realização da operação
        if(contaOrigem->modalidade == normal)
        {
            saldoSuficiente = verificarSaldoConta(contaOrigem, montante + 5);

            if(saldoSuficiente == 1)
            {
                contaOrigem->saldo -= montante + 5;
                contaDestino->saldo += montante;
                printf("\nMontante transferido com sucesso (%.2f EUR)!\n", montante);

                //chamada da função atualizarHistorico() para atualização do histórico de movimentos
                atualizarHistorico(contaOrigem, montante, "Envio de dinheiro por transferência");
                atualizarHistorico(contaDestino, montante, "Receção de dinheiro por transferência");
            }
            else
                printf("\nERRO: Saldo insuficiente!\n");
        }
        else
        {
            saldoSuficiente = verificarSaldoConta(contaOrigem, montante);

            if(saldoSuficiente == 1)
            {
                contaOrigem->saldo -= montante;
                contaDestino->saldo += montante;
                printf("\nMontante transferido com sucesso (%.2f EUR)!\n", montante);

                //chamada da função atualizarHistorico() para atualização do histórico de movimentos
                atualizarHistorico(contaOrigem, montante, "Envio de dinheiro por transferência");
                atualizarHistorico(contaDestino, montante, "Receção de dinheiro por transferência");
            }
            else
                printf("\nERRO: Saldo insuficiente!\n");
        }
    }
    else
        printf("\nERRO: A aprovação falhou!\n");
}

//função para atualização do histórico
void atualizarHistorico(TipoConta *conta, float valor, char descricao[101])
{
    strcpy(conta->historico[2].descricao, conta->historico[1].descricao);
    conta->historico[2].valor = conta->historico[1].valor;

    strcpy(conta->historico[1].descricao, conta->historico[0].descricao);
    conta->historico[1].valor = conta->historico[0].valor;

    strcpy(conta->historico[0].descricao, descricao);
    conta->historico[0].valor = valor;
}
