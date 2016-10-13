#include "contas.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define atrasar() sleep(ATRASO)

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
	if (!contaExiste(idConta))
		return -1;
	if (contasSaldos[idConta - 1] < valor)
		return -1;
	atrasar();
	contasSaldos[idConta - 1] -= valor;
	return 0;
}

int creditar(int idConta, int valor) {
	atrasar();
	if (!contaExiste(idConta))
		return -1;
	contasSaldos[idConta - 1] += valor;
	return 0;
}

int lerSaldo(int idConta) {
	atrasar();
	if (!contaExiste(idConta))
		return -1;
	return contasSaldos[idConta - 1];
}

void simular(int numAnos) {
	int custo_manutencao = 1;
	float taxa_juros = 0.10;
	int j,l,i;
	int saldoAsomar;
	int saldoNovo;

	for (l = 0; l < NUM_CONTAS; l++) {
		printf("SIMULACAO: Ano %d \n", i);

	}

	for (i = 0; i <= numAnos; i++) {
		printf("SIMULACAO: Ano %d \n", i);

		for (j = 1; j <= NUM_CONTAS; j++) {
			int saldoAnterior = lerSaldo(j);
			if (i == 0) {
				printf("Conta  %d, Saldo %d\n", j, lerSaldo(j));
			} else {
				if (saldoAnterior * (1 + taxa_juros) - custo_manutencao <= 0) {
					saldoNovo = 0;
				} else {
					saldoAsomar = saldoAnterior * taxa_juros - custo_manutencao;
					creditar(j,saldoAsomar);
					saldoNovo = saldoAnterior + saldoAsomar;
				}
	
				//	saldoNovo = max(saldoAnterior * (1 + taxa_juros) - custo_manutencao, 0);

				printf("Conta  %d, Saldo %d\n", j, saldoNovo);
			}
		}

	}
}



int meu_fork(int numAnos){
	int pid = 0;
	pid = fork();
	
	if (pid == 0) {
	 // child process
	 simular(numAnos);
	 exit(0);
	}
	
	else if (pid > 0) {
	 // parent process
	 }
	else if (pid < 0){
		printf("fork() failed! \n");
		return 1

	}
	return pid;
}

/*

 

 int status = 0;
 int wpid;
 
void sairAgora(){

	teremos que fazer get_pid? para achar o pid do processo que queremos terminar? OU É 0?
	No chrome tens uma página aberta com o kill ( matar processos tendo o pid) mas não sei se não é para ser 
	usado só no terminal, eu acho que não pq está no enunciado que devemos usar o comando kill
	
 
 
 	 
 
 }
 

 }
 else if (pid > 0) {
 // parent process
 pid = getpid();
 wpid = wait(&status);
 while ((wpid = wait(&status)) > 0){
 
 }
 printf("i-banco terminou.");
 }
 
 else {
 // fork failed
 printf("fork() failed!\n");
 return 1;
 }

 printf("--end of program--\n");

 return 0;
 }

 */

