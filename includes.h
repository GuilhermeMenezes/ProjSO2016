#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
#define COMANDO_AGORA "agora"

#define NUM_TRABALHADORAS 3
#define CMD_BUFFER_DIM (NUM_TRABALHADORAS * 2)

#define MAXARGS 3
#define BUFFER_SIZE 100

#define OP_DEBITAR 2
#define OP_CREDITAR 1
#define OP_LERSALDO 0

#include <pthread.h>
#include <semaphore.h>

sem_t semCanInsert;
sem_t semCanPop;
pthread_mutex_t mutex;