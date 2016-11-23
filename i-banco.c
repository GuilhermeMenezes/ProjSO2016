/* Grupo 39
 // Projeto SO - exercicio 1, version 1
 // Sistemas Operativos, DEI/IST/ULisboa 2016-17
 */

#include "commandlinereader.h"
#include "contas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "buffer.h"
#include "includes.h"
#include <semaphore.h>
#include <pthread.h>
#include "worker.h"
#include <stdbool.h>

int main(int argc, char** argv) {
	int pid = 0;
	int numSimulacoes = 0;
	int listaFilhos[20];
	int contador = 0;
	int i, a, b;
	pthread_t tid[NUM_TRABALHADORAS];
	buff_empty = 1;
	pthread_mutex_init(&mutex, NULL);

	//inicializacao do mutex
	if (pthread_mutex_init(&mutex, NULL)) {
		printf("Error creating mutex.");
		exit(EXIT_FAILURE);
	}

	//inicializacao dos semaforos
	sem_init(&semCanInsert, 0, CMD_BUFFER_DIM);
	sem_init(&semCanPop, 0, 0);

	//verificacao de erros na criacao de semaforos
	if (sem_init(&semCanInsert, 0, CMD_BUFFER_DIM) != 0) {
		printf("Error creating semaphore.");
		exit(EXIT_FAILURE);
	}

	if (sem_init(&semCanPop, 0, 0) != 0) {
		printf("Error creating semaphore.");
		exit(EXIT_FAILURE);
	}

	//criacao de threads
	for (a = 0; a < NUM_TRABALHADORAS; a++) {
		if (pthread_create(&tid[a], NULL, worker, NULL) != 0) {
			printf("Error creating thread.");
			exit(EXIT_FAILURE);
		}
	}

	char *args[MAXARGS + 1];
	char buffer[BUFFER_SIZE];

	inicializarContas();

	printf("Bem-vinda/o ao i-banco\n\n");

	while (1) {
		int numargs;

		numargs = readLineArguments(args, MAXARGS + 1, buffer, BUFFER_SIZE);

		/* EOF (end of file) do stdin ou comando "sair" */
		if (numargs < 0
				|| (numargs > 0 && (strcmp(args[0], COMANDO_SAIR) == 0))) {
			int returnStatus;

			//criacao de uma estrutura especifica do Sair, ou seja, so com os atributos necessarios preenchidos 
			comando_t cmd3;
			cmd3.operacao = OP_SAIR;
			cmd3.idConta = NULL;
			cmd3.valor = NULL;

			
			for (a = 0; a < NUM_TRABALHADORAS; a++) {
				buff_insert(cmd3);
			}

			//espera que todas as threads retirem a "sua" estrutura para sair
			for (b = 0; b < NUM_TRABALHADORAS; b++) {
				pthread_join(tid[b], NULL);
			}

			if ((numargs > 1 && (strcmp(args[1], COMANDO_AGORA) == 0))) {
				for (i = 0; i < contador; i++) {

					kill(listaFilhos[i], SIGUSR2);
				}

			}

			printf("O i-banco vai terminar.\n");
			printf("--\n");
			while (numSimulacoes != 0) {
				pid = wait(&returnStatus); // Parent process waits here for child to terminate.
				if (WIFEXITED(returnStatus)) { // Verify child process terminated without error.   
					printf("FILHO TERMINADO: %d ; terminou normalmente \n",
							pid);
				}

				else
					printf("FILHO TERMINADO: %d; terminou abruptamente \n",
							pid);

				numSimulacoes -= 1;

			}
			printf("--\n");
			printf("O i-banco terminou.\n");

			exit(EXIT_SUCCESS);
		}

		else if (numargs == 0)

			continue;

		/* Debitar */
		else if (strcmp(args[0], COMANDO_DEBITAR) == 0) {
			if (numargs < 3) {
				printf("%s: Sintaxe inválida, tente de novo.\n",
				COMANDO_DEBITAR);
				continue;
			}

			comando_t cmd2;
			cmd2.operacao = OP_DEBITAR;
			cmd2.idConta = atoi(args[1]);
			cmd2.valor = atoi(args[2]);
			cmd2.idContaDestino = NULL;
			//insere a estrutura no buffer
			buff_insert(cmd2);

		}

		/* Creditar */
		else if (strcmp(args[0], COMANDO_CREDITAR) == 0) {

			if (numargs < 3) {
				printf("%s: Sintaxe inválida, tente de novo.\n",
				COMANDO_CREDITAR);
				continue;
			}

			comando_t cmd1;
			cmd1.operacao = OP_CREDITAR;
			cmd1.idConta = atoi(args[1]);
			cmd1.valor = atoi(args[2]);
			cmd1.idContaDestino = NULL;
			buff_insert(cmd1);

		}

		/* Ler Saldo */
		else if (strcmp(args[0], COMANDO_LER_SALDO) == 0) {

			if (numargs < 2) {
				printf("%s: Sintaxe inválida, tente de novo.\n",
				COMANDO_LER_SALDO);
				continue;
			}
			comando_t cmd0;
			cmd0.operacao = OP_LERSALDO;
			cmd0.idConta = atoi(args[1]);
			cmd0.valor = NULL;
			cmd0.idContaDestino = NULL;
			buff_insert(cmd0);

		}

		/* Simular */
		else if (strcmp(args[0], COMANDO_SIMULAR) == 0) {
			int numAnos = atoi(args[1]);
			numSimulacoes += 1;
			if (numAnos < 0) {
				return -1;
			} else {

				wait_all_workers_stopped();

				pid = meu_fork(numAnos);
				listaFilhos[contador] = pid;
				contador += 1;

			}
		}

		/* Transferir */
		else if (strcmp(args[0], COMANDO_TRANSFERENCIA) == 0) {

			if (numargs < 4) {
				printf("%s: Sintaxe inválida, tente de novo.\n",
				COMANDO_TRANSFERENCIA);
				continue;
			}

			comando_t cmd4;
			cmd4.operacao = OP_TRANSFERIR;
			cmd4.idConta = atoi(args[1]);
			cmd4.idContaDestino = atoi(args[2]);
			cmd4.valor = atoi(args[3]);
			buff_insert(cmd4);

		} else {
			printf("Comando desconhecido. Tente de novo.\n");
		}

	}
}

