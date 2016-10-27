#include "cmd.h"
#include "buffer.h"
#include "includes.h"
#include <stdio.h>

void *worker(void *arg){

	while(1){
		
		printf("WWWWWWWWWWWWWWWWWWWW1\n");
		comando_t executa;
		executa = buff_pop();

		printf("%d %d\n", executa.idConta, executa.valor);

		if (executa.operacao == OP_DEBITAR){
			printf("ENTREI NO DEBITAR\n");
			if (debitar(executa.idConta, executa.valor) < 0)
				printf("%s(%d, %d): Erro\n\n", COMANDO_DEBITAR, executa.idConta, executa.valor);
			else
				printf("%s(%d, %d): OK\n\n", COMANDO_DEBITAR, executa.idConta, executa.valor);
		}
		if (executa.operacao == OP_CREDITAR){
			printf("ENTREI NO CREDITAR\n");
			if (creditar(executa.idConta, executa.valor) < 0)
				printf("%s(%d, %d): Erro\n\n", COMANDO_CREDITAR, executa.idConta, executa.valor);
			else
				printf("%s(%d, %d): OK\n\n", COMANDO_CREDITAR, executa.idConta, executa.valor);
			
		}
		if (executa.operacao == OP_LERSALDO){
			printf("ENTREI NO LERSALDO\n");
			if (lerSaldo(executa.idConta) < 0)
				printf("%s(%d): Erro.\n\n", COMANDO_LER_SALDO, lerSaldo(executa.idConta));
			else
				printf("%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO, executa.idConta, lerSaldo(executa.idConta));
			sleep(5);
		}
		
	}
}