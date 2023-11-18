#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define BUFFER_SIZE 1

char buffer1[BUFFER_SIZE];
char buffer2[BUFFER_SIZE];


sem_t emptyBuffer1, fullBuffer1, emptyBuffer2, fullBuffer2;

 

void* threadA(void* arg) {

	FILE *file = fopen("sample.txt","r");
	
	if(file == NULL){
		perror("File not opening");
		exit(1);
	}
	
	char data;
	
	
    while ((data = fgetc(file)) != EOF) {
       
        sem_wait(&emptyBuffer1);
        buffer1[0] = data;
        
        printf("Thread A: Successfully read data %c from the file \n", data);
        sem_post(&fullBuffer1);
    }
    
    fclose(file);
 
}

void* threadB(void* arg) {
    while (1) {
        char data;
        sem_wait(&fullBuffer1);
        sem_wait(&emptyBuffer2);
        
        buffer2[0] = buffer1[0];// Copying from Buffer1 to Buffer2
        				
        sem_post(&emptyBuffer1);
        sem_post(&fullBuffer2);
        
        printf("Thread B: Successfully copied data from Buffer1 to Buffer2\n"); 
    }
}

void* threadC(void* arg) {
    while (1) {
        char data;
        sem_wait(&fullBuffer2);
        data = buffer2[0];
        printf("Thread C: Printing data  from Buffer2\n");
        printf("data '%c'\n",data);
        sem_post(&emptyBuffer2); 
    }
}

int main() {
    pthread_t threadA_t, threadB_t, threadC_t;

    sem_init(&emptyBuffer1, 0, 1);
    sem_init(&fullBuffer1, 0, 0);
    sem_init(&emptyBuffer2, 0, 1);
    sem_init(&fullBuffer2, 0, 0);

    pthread_create(&threadA_t, NULL, threadA, NULL);
    pthread_create(&threadB_t, NULL, threadB, NULL);
    pthread_create(&threadC_t, NULL, threadC, NULL);

    pthread_join(threadA_t, NULL);
    pthread_join(threadB_t, NULL);
    pthread_join(threadC_t, NULL);

    sem_destroy(&emptyBuffer1);
    sem_destroy(&fullBuffer1);
    sem_destroy(&emptyBuffer2);
    sem_destroy(&fullBuffer2);

    return 0;
}

