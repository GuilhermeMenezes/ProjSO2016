#include <cmd.h>
#include <buffer.h>

#define NUM_TRABALHADORAS 3
#define CMD_BUFFER_DIM (NUM_TRABALHADORAS * 2)

semCanInsert = sem_init(CMD_BUFFER_DIM);
semCanPop = sem_init(0);
mutex = pthread_mutex_init();


comando_t cmd_buffer[CMD_BUFFER_DIM];
int buff_write_idx = 0, buff_read_idx = 0;
int contadorCasasVazias = 6;



void buff_insert(comando_t cmd){
	while (1){
	sem_wait(semCanInsert);
	pthread_mutex_lock(mutex);
	cmd_buffer[buff_write_idx] = cmd;
	buff_write_idx ++;
	contadorCasasVazias --;
	pthread_mutex_unlock(mutex);
	sem_post(semCanPop);
	}
}

comando_t buff_pop(){

	while(1){
		sme_wait(semCanPop);
		pthread_mutex_lock(mutex);

		
		cmd_buffer[buff_read_idx];
		buff_write_idx --;
		
    	for(int buffer_counter = 0; buffer_counter < CMD_BUFFER_DIM; buffer_counter++) {

        	if (cmd_buffer[buffer_counter] == buff_read_idx ) {

            	for(int j=buffer_counter; j< (CMD_BUFFER_DIM -1); j++){

                	cmd_buffer[j] = cmd_buffer[j+1];
                	cmd_buffer[CMD_BUFFER_DIM - (contadorCasasVazias-1)] = 0;
                	}
            	contadorCasasVazias +=1;
	        }
    
		}


		pthread_mutex_unlock(mutex);
		sem_post(semCanInsert);
	}
	return cmd_buffer[buff_read_idx];
}