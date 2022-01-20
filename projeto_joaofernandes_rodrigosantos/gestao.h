#ifndef GESTAO_H_INCLUDED
#define GESTAO_H_INCLUDED

//protótipos de funções
float totalFundos(TipoConta contas[], int numAtualContas);
void listarTodasContas(TipoConta contas[], int numAtualContas);
void listarContasCliente(TipoConta contas[], int numAtualContas);
int aprovarTransacao(TipoConta *conta);
void guardarContas(TipoConta contas[], int numAtualContas);

#endif // GESTAO_H_INCLUDED
