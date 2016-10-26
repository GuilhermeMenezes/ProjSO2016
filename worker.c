void worker(void *arg){
	if (*arg == OP_DEBITAR){
		debitar(executa.idConta, executa.valor);
	}
	if (*arg == OP_CREDITAR){
		creditar(executa.idConta, executa.valor);
	}
	if (*arg == OP_LERSALDO){
		lerSaldo(executa.idConta);
	}
}