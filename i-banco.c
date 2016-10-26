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



int main(int argc, char** argv) {
	int pid = 0;
	int numSimulacoes = 0;
	int listaFilhos[20];
	int contador = 0;
	int i;

	
	pthread_mutex_init(&mutex, NULL);
	sem_init(&semCanInsert,0, CMD_BUFFER_DIM);
	sem_init(&semCanPop, 0, 0);


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
			
			if ((numargs > 1 && (strcmp(args[1], COMANDO_AGORA) == 0))) {
				for(i=0;i<contador; i++){
					kill(listaFilhos[contador], SIGUSR2);
				}
			}
			printf("O i-banco vai terminar.\n");
			printf("--\n");
			while(numSimulacoes != 0){
				pid = wait(&returnStatus); // Parent process waits here for child to terminate.
				if (WIFEXITED(returnStatus)) { // Verify child process terminated without error.   
					printf("FILHO TERMINADO: %d ; terminou normalmente \n", pid);
				}
			
				else
					printf("FILHO TERMINADO: %d; terminou abruptamente \n", pid);
				

				
				numSimulacoes -= 1;
			
			}
			printf("--\n");
			printf("O i-banco terminou.\n");
			
			exit (EXIT_SUCCESS);
		}
			

		else if (numargs == 0)
			/* Nenhum argumento; ignora e volta a pedir */
			continue;

		/* Debitar */
		else if (strcmp(args[0], COMANDO_DEBITAR) == 0) {
			int idConta, valor;
			if (numargs < 3) {
				printf("%s: Sintaxe inválida, tente de novo.\n",
						COMANDO_DEBITAR);
				continue;
			}
			comando_t cmd2;
			cmd2.operacao = OP_DEBITAR;
			cmd2.idConta = atoi(args[1]);
			cmd2.valor = atoi(args[2]);
			
			buff_insert(cmd2);

			idConta = atoi(args[1]);
			valor = atoi(args[2]);

			if (debitar(idConta, valor) < 0)
				printf("%s(%d, %d): Erro\n\n", COMANDO_DEBITAR, idConta, valor);
			else
				printf("%s(%d, %d): OK\n\n", COMANDO_DEBITAR, idConta, valor);
		}

		/* Creditar */
		else if (strcmp(args[0], COMANDO_CREDITAR) == 0) {
			int idConta, valor;
			if (numargs < 3) {
				printf("%s: Sintaxe inválida, tente de novo.\n",
						COMANDO_CREDITAR);
				continue;
			}

			idConta = atoi(args[1]);
			valor = atoi(args[2]);

			if (creditar(idConta, valor) < 0)
				printf("%s(%d, %d): Erro\n\n", COMANDO_CREDITAR, idConta,
						valor);
			else
				printf("%s(%d, %d): OK\n\n", COMANDO_CREDITAR, idConta, valor);
		}

		/* Ler Saldo */
		else if (strcmp(args[0], COMANDO_LER_SALDO) == 0) {
			int idConta, saldo;

			if (numargs < 2) {
				printf("%s: Sintaxe inválida, tente de novo.\n",
						COMANDO_LER_SALDO);
				continue;
			}
			idConta = atoi(args[1]);
			saldo = lerSaldo(idConta);
			if (saldo < 0)
				printf("%s(%d): Erro.\n\n", COMANDO_LER_SALDO, idConta);
			else
				printf("%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO,
						idConta, saldo);
		}

		/* Simular */
		else if (strcmp(args[0], COMANDO_SIMULAR) == 0) {
			int numAnos = atoi(args[1]);
			numSimulacoes += 1;
			if (numAnos < 0) {
				return -1;
			} else
				pid = meu_fork(numAnos);
				listaFilhos[contador] = pid;
				contador += 1;

			
		}
		
		 
		else {
			printf("Comando desconhecido. Tente de novo.\n");
		}

	}
}

