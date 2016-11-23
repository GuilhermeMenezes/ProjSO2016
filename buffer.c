#include "cmd.h"
#include "buffer.h"
#include "includes.h"
#include <semaphore.h>
#include <pthread.h>
comando_t cmd_buffer[CMD_BUFFER_DIM];
buff_read_idx = 0;
buff_write_idx = 0;
conta_items = 0;

void buff_insert(comando_t cmd) {
	//Insere uma estrutura no buffer de estruturas
	sem_wait(&semCanInsert);
	pthread_mutex_lock(&mutex);

	cmd_buffer[buff_write_idx] = cmd;
	conta_items++;											//Adiciona 1 a variavel "conta_items" para sabermos quantos items foram introduzidos no buffer
	buff_write_idx = (buff_write_idx + 1) % CMD_BUFFER_DIM;

	pthread_mutex_unlock(&mutex);
	sem_post(&semCanPop);
}

comando_t buff_pop() {
	//retira uma estrutura do buffer de estruturas
	comando_t cmd;

	sem_wait(&semCanPop);
	pthread_mutex_lock(&mutex);

	cmd = cmd_buffer[buff_read_idx];
	conta_items --;											//subtrai 1 a variavel "conta_items" para saber quantos items ficaram no buffer depois de se retirar 1
	buff_read_idx = (buff_read_idx + 1) % CMD_BUFFER_DIM;

	pthread_mutex_unlock(&mutex);
	sem_post(&semCanInsert);

	return cmd;
}
