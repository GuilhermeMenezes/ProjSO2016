#ifndef CMD_H
#define CMD_H

typedef struct {
	int operacao;
	int idConta;
	int idContaDestino;
	int valor;
} comando_t;

#endif