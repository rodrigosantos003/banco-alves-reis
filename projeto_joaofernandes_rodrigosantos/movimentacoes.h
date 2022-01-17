#ifndef MOVIMENTACOES_H_INCLUDED
#define MOVIMENTACOES_H_INCLUDED

//protótipos de funções
int verificarSaldoConta(TipoConta *conta, float montante);
void depositarDinheiro(TipoConta *conta);
void levantarDinheiro(TipoConta *conta);
void transferirDinheiro(TipoConta *contaOrigem, TipoConta *contaDestino);
void atualizarHistorico(TipoConta *conta, float valor, char descricao[101]);

#endif // MOVIMENTACOES_H_INCLUDED
