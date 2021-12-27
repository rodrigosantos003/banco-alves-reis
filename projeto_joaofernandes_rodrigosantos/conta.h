#ifndef CONTA_H_INCLUDED
#define CONTA_H_INCLUDED

typedef struct {
    int numero, nif;
    char nome[100];
    float saldo;
}TipoConta;

void abrirConta(TipoConta *conta);
void imprimirConta(TipoConta conta);
void consultarDetalhesConta(TipoConta conta);
void depositarDinheiro(TipoConta *conta);
void levantarDinheiro(TipoConta *conta);
void transferirDinheiro(TipoConta contaOrigem, TipoConta contaDestino);
void editarDetalhesConta(TipoConta *conta);
void elimiarConta(TipoConta conta);

#endif // CONTA_H_INCLUDED
