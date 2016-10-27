#include "cmd.h"
#include "buffer.h"
#include "includes.h"
#include <semaphore.h>
#include <pthread.h>




comando_t cmd_buffer[CMD_BUFFER_DIM];
int buff_write_idx = 0, buff_read_idx = 0;



void buff_insert(comando_t cmd){

	sem_wait(&semCanInsert);
	pthread_mutex_lock(&mutex);
	
	cmd_buffer[buff_write_idx] = cmd;
	buff_write_idx = (buff_write_idx + 1) % CMD_BUFFER_DIM;
	
	pthread_mutex_unlock(&mutex);
	sem_post(&semCanPop);
	}


comando_t buff_pop(){
	comando_t cmd;

	
	sem_wait(&semCanPop);
	pthread_mutex_lock(&mutex);

		
	cmd = cmd_buffer[buff_read_idx];
	buff_read_idx = (buff_read_idx + 1) % CMD_BUFFER_DIM;
		

	pthread_mutex_unlock(&mutex);
	sem_post(&semCanInsert);
	
	return cmd;
}