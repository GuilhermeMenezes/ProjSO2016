#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
#define COMANDO_AGORA "agora"
#define COMANDO_TRANSFERENCIA "transferir"

#define NUM_TRABALHADORAS 4
#define CMD_BUFFER_DIM (NUM_TRABALHADORAS * 2)

#define MAXARGS 4
#define BUFFER_SIZE 100

#define OP_DEBITAR 2
#define OP_CREDITAR 1
#define OP_LERSALDO 0
#define OP_SAIR 3
#define OP_TRANSFERIR 4

#include <pthread.h>
#include <semaphore.h>



int buff_empty;
int idContaOrigem, idContaDestino;
sem_t semCanInsert;
sem_t semCanPop;
pthread_mutex_t mutex;
pthread_mutex_t mutexTransferir;
extern int buff_write_idx, buff_read_idx;
extern int conta_items;
