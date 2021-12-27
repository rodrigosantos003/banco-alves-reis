#ifndef CONTA_H_INCLUDED
#define CONTA_H_INCLUDED

typedef struct {
    int numeroConta, nif;
    char nome[100];
    float saldo;
}TipoConta;

void abrirConta(TipoConta *conta);
void imprimirConta(TipoConta conta);

#endif // CONTA_H_INCLUDED
