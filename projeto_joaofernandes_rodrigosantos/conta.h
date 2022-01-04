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
int lerNumConta(TipoConta contas[], int numAtualContas);
int verificarSaldoConta(TipoConta *conta, float montante);
void abrirConta(TipoConta *conta);
void imprimirConta(TipoConta conta);
void depositarDinheiro(TipoConta *conta);
void levantarDinheiro(TipoConta *conta);
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino);
void atualizarHistorico(TipoConta *conta, float valor, char descricao[101]);
void editarDetalhesConta(TipoConta *conta);
void elimiarConta(TipoConta conta);

#endif // CONTA_H_INCLUDED
