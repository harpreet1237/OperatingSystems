// C program to demonstrate working of Semaphores 
#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <assert.h>
 
#define BUFFER_SIZE 10
sem_t empty,full;
int buffer[BUFFER_SIZE]; 

sem_t mutex; 


void display(){
	for(int i=0;i<BUFFER_SIZE;i++){
		printf("%d ",buffer[i]);
	}
	printf("\n");
}

void * producer(void * arg){
	
	int item = 1;
	
	while(1){
		 sleep(1);
		sem_wait(&empty);
		 
		 sem_wait(&mutex);
		buffer[item % BUFFER_SIZE] = item;
		printf("Produced %d\n",item);
		item++; 
		
		display();
		sem_post(&mutex);
		sem_post(&full);
	}
}

void * consumer(void * arg){
	
	while(1){
	 	sleep(1);
		sem_wait(&full);
		 sem_wait(&mutex);
		int item = buffer[0];
		
		printf("consumed %d\n",item);
		
		for(int i=1;i<BUFFER_SIZE;i++){
			buffer[i-1] = buffer[i];
		} 
		
		sem_post(&mutex);
		sem_post(&empty);
	}
	
	
	 
}
 
int main() 
{ 
	pthread_t producer_t, consumer_t;
	sem_init(&mutex, 0, 1); 
	sem_init(&empty,0,BUFFER_SIZE);
	sem_init(&full,0,0);
	printf("Semaphores initialized..\n");
	pthread_create(&producer_t,NULL,producer,NULL);
	pthread_create(&consumer_t,NULL,consumer,NULL);
	
	pthread_join(producer_t,NULL);
	pthread_join(consumer_t,NULL);
	
	sem_destroy(&empty);
	sem_destroy(&full);
	
	return 0;
	
	 
} 
