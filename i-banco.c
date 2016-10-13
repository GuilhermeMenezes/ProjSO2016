/*
 // Projeto SO - exercicio 1, version 1
 // Sistemas Operativos, DEI/IST/ULisboa 2016-17
 */

#include "commandlinereader.h"
#include "contas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
#define COMANDO_SAIRAGORA "sair_agora"

#define MAXARGS 3
#define BUFFER_SIZE 100

int main(int argc, char** argv) {
	int pid = 0;

	char *args[MAXARGS + 1];
	char buffer[BUFFER_SIZE];
	int numSimulacoes = 0;

	inicializarContas();

	printf("Bem-vinda/o ao i-banco\n\n");

	while (1) {
		int numargs;

		numargs = readLineArguments(args, MAXARGS + 1, buffer, BUFFER_SIZE);

		/* EOF (end of file) do stdin ou comando "sair" */
		if (numargs < 0 || (numargs > 0 && (strcmp(args[0], COMANDO_SAIR) == 0))) {

			int returnStatus;

			if (numSimulacoes == 0){
				printf("0 processos por terminar antes de sair.");
			}
			else{	
				while (numSimulacoes != 0){

					pid = wait(&returnStatus); // Parent process waits here for child to terminate.

					if (returnStatus == 0) { // Verify child process terminated without error.   
						printf("FILHO TERMINADO: %d ; terminou normalmente \n", pid);
					}
					//duvida******
					if (returnStatus == 1) {
						printf("FILHO TERMINADO: %d; terminou abruptamente \n", pid);
					}
					numSimulacoes -= 1;
				}
			}

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
			int i;
			numSimulacoes += 1;

				if (numAnos < 0) {
					return -1;
				} else{
					pid = meu_fork(numAnos);
				}	
			/* POR COMPLETAR */

		}/* else if (numargs < 0
				|| (numargs > 0 && (strcmp(args[0], COMANDO_SAIRAGORA) == 0))) {
			
			if (signal == SIGUSR2) {
				kill(pid, SIGUSR2);
			}

		}*/

		else {
			printf("Comando desconhecido. Tente de novo.\n");
		}

	}
}
