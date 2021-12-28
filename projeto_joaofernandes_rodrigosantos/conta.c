#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "conta.h"

//função para abertura de conta
void abrirConta(TipoConta *conta){
    printf("INTRODUZA OS DADOS DA CONTA:\n");

    //leitura do número de conta
    printf("Número > ");
    scanf("%d", &conta->numero);
    fflush(stdin);

    //leitura do número de titulares
    printf("Nº de titulares > ");
    scanf("%d", &conta->totalTitulares);
    fflush(stdin);

    //leitura dos dados dos titulares
    for(int i = 0; i < conta->totalTitulares; i++){
        printf("TITULAR %d\n", i+1);

        printf("NIF > ");
        scanf("%d", &conta->titulares[i].nif);

        getchar();

        printf("Nome > ");
        gets(conta->titulares[i].nome);
    }
    fflush(stdin);

    //leitura da modalidade
    printf("Modalidade da Conta (Normal:0 / Isenta:1) > ");
    scanf("%d", &conta->modalidade);
    fflush(stdin);

    //leitura do montante inicial
    do{
        printf("Saldo > ");
        scanf("%f", &conta->saldo);

        if(conta->saldo < 150)
            printf("O saldo inicial deve ser igual ou superior a 150€!\n");
    } while(conta->saldo < 150);
    fflush(stdin);

    //leitura da data de abertura
    printf("Data de Abertura (dia/mes/ano) > ");
    scanf("%d/%d/%d", &conta->data.dia, &conta->data.mes, &conta->data.ano);
    fflush(stdin);
}

//função que escreve os detalhes de uma conta
void imprimirConta(TipoConta conta){
    printf("----------------\n");

    printf("Número: %d\n", conta.numero);

    for(int i = 0; i < conta.totalTitulares; i++){
        printf("TITULAR %d\n", i+1);
        printf("Nome: %-25s\n", conta.titulares[i].nome);
        printf("NIF: %d\n", conta.titulares[i].nif);
    }

    if(conta.modalidade == 0)
        printf("Modalidade: Normal\n");
    else
        printf("Modalidade: Isenta\n");

    printf("Saldo: %.2f€\n", conta.saldo);

    printf("Histórico (útlimos 3 movimentos)\n");
    for(int i = 0; i < 3; i++){
        printf("Descrição: %s | ", conta.historico[i].descricao);
        printf("Valor: %.2f\n", conta.historico[i].valor);
    }

    printf("Data de abertura: %d/%d/%d\n", conta.data.dia, conta.data.mes, conta.data.ano);

    printf("----------------\n");
}
