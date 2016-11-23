#include "contas.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>
#include "includes.h"

pthread_mutex_t mutex1;
pthread_mutex_t mutexTransferir;
#define atrasar() sleep(ATRASO)
int warning = 0;

int contasSaldos[NUM_CONTAS];

int contaExiste(int idConta) {
	return (idConta > 0 && idConta <= NUM_CONTAS);
}

void inicializarContas() {
	int i;
	for (i = 0; i < NUM_CONTAS; i++)
		contasSaldos[i] = 0;
}

int debitar(int idConta, int valor) {
	atrasar();
	pthread_mutex_lock(&mutex1);
	if (!contaExiste(idConta))
		return -1;
	if (contasSaldos[idConta - 1] < valor)
		return -1;
	atrasar();
	contasSaldos[idConta - 1] -= valor;
	pthread_mutex_unlock(&mutex1);
	return 0;
}

int creditar(int idConta, int valor) {
	atrasar();
	pthread_mutex_lock(&mutex1);
	if (!contaExiste(idConta))
		return -1;
	contasSaldos[idConta - 1] += valor;
	pthread_mutex_unlock(&mutex1);
	return 0;
}

int lerSaldo(int idConta) {
	atrasar();

	if (!contaExiste(idConta))
		return -1;

	return contasSaldos[idConta - 1];
}

int debitar_sem_mutex(int idConta, int valor) {
	atrasar();
	if (!contaExiste(idConta))
		return -1;
	if (contasSaldos[idConta - 1] < valor)
		return -1;
	atrasar();
	contasSaldos[idConta - 1] -= valor;

	return 0;
}

int creditar_sem_mutex(int idConta, int valor) {
	atrasar();
	sleep(3);
	if (!contaExiste(idConta))
		return -1;
	contasSaldos[idConta - 1] += valor;
	return 0;
}

int transferir(int idConta, int idContaDestino, int valor) {
	if (lerSaldo(idConta) < valor) {
		return -1;
	} else {

		pthread_mutex_lock(&mutexTransferir);
		debitar_sem_mutex(idConta, valor);
		creditar_sem_mutex(idContaDestino, valor);
		pthread_mutex_unlock(&mutexTransferir);
		return 0;

	}
}

void simular(int numAnos) {
	int custo_manutencao = 1;
	float taxa_juros = 0.10;
	int saldoNovo;
	int i;
	int j;
	int saldoAsomar;


	for (i = 0; i <= numAnos && warning != 1; i++) {
		printf("SIMULACAO: Ano %d \n", i);
		printf("-----------------\n");

		for (j = 1; j <= NUM_CONTAS; j++) {
			int saldoAnterior = lerSaldo(j);
			if (i == 0) {
				printf("Conta  %d, Saldo %d\n", j, lerSaldo(j));
			} else {
				if (saldoAnterior * (1 + taxa_juros) - custo_manutencao <= 0) {
					saldoNovo = 0;
				} else {
					saldoAsomar = (saldoAnterior * taxa_juros)
							- custo_manutencao;
					creditar(j, saldoAsomar);
					saldoNovo = saldoAnterior + saldoAsomar;
				}

				printf("Conta  %d, Saldo %d\n", j, saldoNovo);
			}
		}

	}
}

void sairAgora(int signum) {

	warning = 1;

}

int meu_fork(int numAnos) {
	int pid = 0;
	signal(SIGUSR2, sairAgora);
	pid = fork();
	if (pid == 0) {
		simular(numAnos);
		exit(0);
	}

	else if (pid > 0) {

	} else if (pid < 0) {
		printf("fork() failed!\n");
		return 1;
	}
	return pid;
}

