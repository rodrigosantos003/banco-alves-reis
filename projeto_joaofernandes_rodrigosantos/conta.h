#ifndef CONTA_H_INCLUDED
#define CONTA_H_INCLUDED

//estruturas de dados
typedef struct
{
    int nif;
    char nome[101];
} TipoCliente;

typedef enum {normal, isenta} TipoModalidadeConta;

typedef struct
{
    char descricao[101];
    float valor;
} TipoHistorico;

typedef struct
{
    int dia, mes, ano;
} TipoData;

typedef struct
{
    int numero, totalTitulares;
    TipoCliente titulares[5];
    TipoModalidadeConta modalidade;
    float saldo;
    TipoHistorico historico[3];
    TipoData data;
} TipoConta;

//protótipos de funções
int lerNumConta(TipoConta contas[], int numAtualContas);
void abrirConta(TipoConta *conta, int numAtualContas);
void imprimirConta(TipoConta conta);
void editarDetalhesConta(TipoConta *conta);
void eliminarConta(TipoConta contas[], int numAtualContas, int indiceApagar);

#endif // CONTA_H_INCLUDED
