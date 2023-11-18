#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>
const int inf = 1e9;

int main(){
    

    int pipefd[2];
    pipe(pipefd);



    // Input from user 
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)scanf("%d",&arr[i]);

    FILE *f = fdopen(pipefd[0],"r");
    dup2(pipefd[0],0);

    // forking first child
    pid_t child1 = fork();

    if(child1 < 0){
        perror("Error in fork");
        exit(1);
    }
    else if(child1 == 0){
        printf("Entered in child process\n");

        FILE *f = fdopen(pipefd[1],"w");
        dup2(pipefd[1],1);
        int largest1 = -inf;
        int largest2 = -inf;
        
        for(int i=0;i<n/2;i++){
            if(largest1 < arr[i]){
                largest1 = arr[i];
            }
        }

        for(int i=0;i<n/2;i++){
            if(arr[i] == largest1)continue;
            if(arr[i] > largest2){
                largest2 = arr[i];
            }
        }

        // returns two integers using pipe
        printf("%d %d ",largest1,largest2);
        exit(0);
    }
    else {
        int l1,l2,l3,l4;
            wait(&child1);
            scanf("%d %d",&l1,&l2);
            
        //parent process creates second child
        pid_t child2 = fork();
        
        if(child2 < 0){
            perror("Error in second fork");
            exit(1);
        }
        else if(child2 == 0){
            printf("Entered in child2\n");

            FILE *f = fdopen(pipefd[1],"w");
            dup2(pipefd[1],1);
        
            int largest1 = -inf;
            int largest2 = -inf;
            
            for(int i=n/2;i<n;i++){
                if(largest1 < arr[i]){
                    largest1 = arr[i];
                }
            }

            for(int i=n/2;i<n;i++){
                if(arr[i] == largest1)continue;
                if(arr[i] > largest2){
                    largest2 = arr[i];
                }
            }

            // returns two integers using pipe
            printf("%d %d\n",largest1,largest2);
            exit(0);

        }
        else{
            wait(&child2);
            scanf("%d %d",&l3,&l4);
           
            int largest1=-inf,largest2=-inf;

            int arr2[4];
            arr2[0] = l1;
            arr2[1] = l2;
            arr2[2] = l3;
            arr2[3] = l4;

            for(int i=0;i<4;i++){
                if(largest1 < arr2[i])
                largest1 = arr2[i];
            }
            for(int i=0;i<4;i++){
                if(arr2[i] == largest1)continue;
                if(largest2 < arr2[i])
                largest2 = arr2[i];
            }

            printf("%d %d are largest numbers found\n",largest1,largest2);
        }
    }
    

    
}
