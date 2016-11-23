#include "cmd.h"
#include "buffer.h"
#include "includes.h"
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

pthread_cond_t condWorkersStopped = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexWorkersStopped = PTHREAD_MUTEX_INITIALIZER;
int conta_working = 0;

void *worker(void *arg) {
	while (1) {
		comando_t executa = buff_pop();
		set_worker_stopped(false);
		work(executa);
		set_worker_stopped(true);
	}
}

bool all_workers_stopped() {
	//verifica se o buffer esta vazio
	if (buff_write_idx == buff_read_idx && conta_items == 0){
		return conta_working == 0;
	}
}

void set_worker_stopped(bool val) {
	pthread_mutex_lock(&mutexWorkersStopped);
	//aumenta o valor da variavel "conta_working" que conta o numero de threads a trabalhar
	if (val == false) {
		conta_working++;
	} else {
		conta_working--;
	}

	if (all_workers_stopped()) {
		pthread_cond_signal(&condWorkersStopped);
	}
	pthread_mutex_unlock(&mutexWorkersStopped);
}

void wait_all_workers_stopped(void) {
	//espera que todas as tarefas não estejam a trabalhar
	pthread_mutex_lock(&mutexWorkersStopped);
	while (!all_workers_stopped())
		pthread_cond_wait(&condWorkersStopped, &mutexWorkersStopped);
	pthread_mutex_unlock(&mutexWorkersStopped);
}

void work(comando_t executa) {
	//dependendo da operacao que a thread vai encontrar no item que retirar buffer, vai fazer uma de 5 operacoes (debitar, creditar, lersaldo, sair e transferir)
	if (executa.operacao == OP_DEBITAR) {
		if (debitar(executa.idConta, executa.valor) < 0) { 
			printf("%s(%d, %d): Erro\n\n", COMANDO_DEBITAR, executa.idConta,
					executa.valor);
		} else
			printf("%s(%d, %d): OK\n\n", COMANDO_DEBITAR, executa.idConta,
					executa.valor);
	}
	if (executa.operacao == OP_CREDITAR) {
		if (creditar(executa.idConta, executa.valor) < 0)
			printf("%s(%d, %d): Erro\n\n", COMANDO_CREDITAR, executa.idConta,
					executa.valor);
		else
			printf("%s(%d, %d): OK\n\n", COMANDO_CREDITAR, executa.idConta,
					executa.valor);

	}
	if (executa.operacao == OP_LERSALDO) {
		if (lerSaldo(executa.idConta) < 0)
			printf("%s(%d): Erro.\n\n", COMANDO_LER_SALDO, executa.idConta);
		else
			printf("%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO,
					executa.idConta, lerSaldo(executa.idConta));
	}
	if (executa.operacao == OP_SAIR) {

		pthread_exit(NULL);

	}
	if (executa.operacao == OP_TRANSFERIR) {
		if (transferir(executa.idConta, executa.idContaDestino, executa.valor)
				< 0)
			printf("Erro ao transferir valor da conta %d para a conta %d.\n",
					executa.idConta, executa.idContaDestino);

		else
			printf("transferir (%d, %d, %d): OK \n", executa.idConta,
					executa.idContaDestino, executa.valor);

	}
}

