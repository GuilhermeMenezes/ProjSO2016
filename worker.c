#include "cmd.h"
#include "buffer.h"
#include "includes.h"

void worker(){

	comando_t executa;
	executa = buff_pop();

	if (executa.operacao == OP_DEBITAR){
		debitar(executa.idConta, executa.valor);
	}
	if (executa.operacao == OP_CREDITAR){
		creditar(executa.idConta, executa.valor);
	}
	if (executa.operacao == OP_LERSALDO){
		lerSaldo(executa.idConta);
	}
}