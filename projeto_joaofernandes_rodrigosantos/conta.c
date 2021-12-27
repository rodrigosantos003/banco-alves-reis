#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "conta.h"

void abrirConta(TipoConta *conta){
    printf("INTRODUZA OS DADOS DA CONTA:\n");

    printf("Número > ");
    scanf("%d", &conta->numeroConta);
    fflush(stdin);

    printf("NIF > ");
    scanf("%d", &conta->nif);
    fflush(stdin);

    printf("Nome > ");
    gets(conta->nome);
    fflush(stdin);

    printf("Saldo > ");
    scanf("%f", &conta->saldo);
}
