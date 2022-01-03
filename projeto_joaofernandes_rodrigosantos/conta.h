#ifndef CONTA_H_INCLUDED
#define CONTA_H_INCLUDED

//estruturas de dados
typedef struct{
    int nif;
    char nome[101];
}TipoCliente;

typedef enum {normal, isenta}TipoModalidadeConta;

typedef struct{
    char descricao[101];
    float valor;
}TipoHistorico;

typedef struct{
    int dia, mes, ano;
}TipoData;

typedef struct{
    int numero, totalTitulares;
    TipoCliente titulares[5];
    TipoModalidadeConta modalidade;
    float saldo;
    TipoHistorico historico[3];
    TipoData data;
}TipoConta;

//protótipos de funções
void lerNumConta(int *numConta, TipoConta contas[], int numAtualContas);
void abrirConta(TipoConta *conta);
void imprimirConta(TipoConta conta);
//void consultarDetalhesConta(TipoConta contas[], int numAtualContas);
void depositarDinheiro(TipoConta *conta);
void levantarDinheiro(TipoConta *conta);
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino);
void editarDetalhesConta(TipoConta *conta);
void elimiarConta(TipoConta conta);

#endif // CONTA_H_INCLUDED
