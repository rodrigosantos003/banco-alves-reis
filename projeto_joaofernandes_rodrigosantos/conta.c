#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "conta.h"

//função para leitura do número de conta e verificação da sua existência
int lerNumConta(TipoConta contas[], int numAtualContas)
{
    int numConta = 0;

    //leitura do número de conta
    printf("Introduza o número de conta: ");
    scanf("%d", &numConta);
    fflush(stdin);

    //iteração para verificação da existência da conta
    for(int i = 0; i < numAtualContas; i++)
    {
        //se a conta existir é retornada a sua posição no array
        if(contas[i].numero == numConta)
        {
            return i;
        }
    }
    //senão é escrito no ecrã que a conta não existe e é retornado o valor de "erro" (i.e -1)
    printf("\nERRO:A conta não existe!\n");
    return -1;
}

//função para abertura de conta
void abrirConta(TipoConta *conta, int numAtualContas)
{
    int num, quantidadeDigitos;
    num = quantidadeDigitos = 0;

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t); /*retorna os valores da data local*/

    printf("INTRODUZA OS DADOS DA CONTA:\n");

    //atribuição do número de conta
    conta->numero = numAtualContas + 1;

    //leitura do número de titulares
    do
    {
        printf("Nº de titulares > ");
        scanf("%d", &conta->totalTitulares);
        fflush(stdin);

        if(conta->totalTitulares > 5)
            printf("\nERRO: A conta deve ter até 5 titulares!\n");
        else if(conta->totalTitulares <= 0)
            printf("\nERRO: O número de titulares deve ser maior que 0!\n");
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

            num = conta->titulares[i].nif;
            quantidadeDigitos = 0;
            do
            {
                num /= 10;
                quantidadeDigitos++;
            }
            while (num != 0);

            if(quantidadeDigitos != 9)
                printf("\nERRO: O NIF deve ter 9 dígitos!\n");
        }
        while(quantidadeDigitos != 9);

        printf("Nome > ");
        gets(conta->titulares[i].nome);
        fflush(stdin);
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


    //atribuição da data de abertura (através da data local)
    conta->data.dia = tm.tm_mday;
    conta->data.mes = tm.tm_mon+1;
    conta->data.ano = tm.tm_year+1900;
}

//função para escrever os detalhes de uma conta
void imprimirConta(TipoConta conta)
{
    printf("----------------\n");

    printf("Número: %d\n", conta.numero);

    printf("TITULARES\n");
    for(int i = 0; i < conta.totalTitulares; i++)
    {
        printf("\tTitular %d: ", i+1);
        printf("| Nome: %-25s ", conta.titulares[i].nome);
        printf("| NIF: %d\n", conta.titulares[i].nif);
    }

    if(conta.modalidade == normal)
        printf("Modalidade: Normal\n");
    else
        printf("Modalidade: Isenta\n");

    printf("Saldo: %.2f EUR \n", conta.saldo);

    printf("Histórico (últimos 3 movimentos)\n");
    for(int i = 0; i < 3; i++)
    {
        printf("\tDescrição: %-25s | ", conta.historico[i].descricao);
        printf("Valor: %.2f\n", conta.historico[i].valor);
    }

    printf("Data de abertura: %02d/%02d/%4d\n", conta.data.dia, conta.data.mes, conta.data.ano);

    printf("----------------\n");
}

//função para listar todas as contas registadas
void listarTodasContas(TipoConta contas[], int numAtualContas)
{
    //iteração para escrita de todas as contas existentes
    for(int i = 0; i < numAtualContas; i++)
    {
        imprimirConta(contas[i]);
        printf("\n");
    }
}

//função para listar todas as contas de um determinado cliente
void listarContasCliente(TipoConta contas[], int numAtualContas)
{
    int nif;

    //leitura do NIF do cliente
    printf("NIF a consultar > ");
    scanf("%d", &nif);
    fflush(stdin);

    //iteração para percorrer todas as contas
    for(int i = 0; i < numAtualContas; i++)
    {
        //iteração para percorrer os titulares da cintas
        for(int x = 0; x < contas[i].totalTitulares; x++)
        {
            //se o NIF do titular for igual ao NIF introduzido, são escritos os detalhes da conta
            if(contas[i].titulares[x].nif == nif)
            {
                imprimirConta(contas[i]);
                printf("\n");
            }
        }
    }
}

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

//função para transferência de dinheiro entre contas
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino)
{
    float montante = 0.0F;
    int saldoSuficiente = 0;

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
            printf("\nMontante levantada com sucesso (%.2f EUR)\n", montante);

            //chamada da função atualizarHistorico() para atualização do histórico de movimentos
            atualizarHistorico(contaOrigem, montante, "Envio de dinheiro por transferência");
            atualizarHistorico(contaDestino, montante, "Receção de dinheiro por transferência");
        }
        else
            printf("\nERRO: Saldo insuficiente!\n");
    }
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

//função para edição dos detalhes da conta
void editarDetalhesConta(TipoConta *conta)
{
    char resposta;
    int numTitulares, num, quantidadeDigitos;

    numTitulares = num = quantidadeDigitos = 0;

    printf("Pretende alterar o tipo de conta? (S/N) ");
    scanf("%c", &resposta);
    fflush(stdin);

    if(resposta == 'S' || resposta == 's')
    {
        do
        {
            printf("Novo tipo de conta (Normal:0 / Isenta:1) > ");
            scanf("%u", &conta->modalidade);
            fflush(stdin);

            if(conta->modalidade < 0 || conta->modalidade > 1)
                printf("\nERRO: A modalidade deve ser 0 ou 1, Normal ou Isenta respetivamente!\n");
        }
        while(conta->modalidade < 0 || conta->modalidade > 1);
    }

    printf("Pretende adicionar titulares? (S/N) ");
    scanf("%c", &resposta);
    fflush(stdin);

    if(resposta == 'S' || resposta == 's')
    {
        printf("Nº de titulares a adicionar > ");
        scanf("%d", &numTitulares);
        fflush(stdin);

        if(conta->totalTitulares + numTitulares <= 5)
        {
            for(int i = conta->totalTitulares; i < conta->totalTitulares + numTitulares; i++)
            {
                printf("TITULAR %d\n", i+1);

                do
                {
                    printf("NIF > ");
                    scanf("%d", &conta->titulares[i].nif);
                    fflush(stdin);

                    num = conta->titulares[i].nif;
                    quantidadeDigitos = 0;
                    do
                    {
                        num /= 10;
                        quantidadeDigitos++;
                    }
                    while (num != 0);

                    if(quantidadeDigitos != 9)
                        printf("\nERRO: O NIF deve ter 9 dígitos!\n");
                }
                while(quantidadeDigitos != 9);

                printf("Nome > ");
                gets(conta->titulares[i].nome);
                fflush(stdin);
            }

            conta->totalTitulares += numTitulares;
        }
        else
            printf("\nERRO: O número de titulares ultrapassa o limite!\n");
    }
}

void eliminarConta(TipoConta contas[], int numAtualContas, int indiceApagar){
    if(indiceApagar >= numAtualContas + 1){
        for(int i = indiceApagar - 1; i < numAtualContas - 1; i++){
            contas[i] = contas[i+1];
        }

        numAtualContas--;

    }
    else
        printf("\nERRO: Não é possível apagar a conta!\n");

}
