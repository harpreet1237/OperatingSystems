#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    while (1) {
        char num1[12];
        char num2 [12];
        char op;

        printf("Enter two integers and an operator (+ or -): ");
        scanf("%s",num1);
        scanf("%s",num2);
        
        //temporary input to avoid reading \n
        scanf("%c",&op);
        scanf("%c",&op);
      
  	
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            execl("./server","server",&num1,&num2,&op,NULL);
            perror("Execl failure");

        } else {
            int status;
            wait(&status);
            
            int result = WEXITSTATUS(status);     
            printf("Result received from server.c : %d\n", result);
        }
    }

    return 0;
}

