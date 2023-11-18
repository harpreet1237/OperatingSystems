#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc < 4) {
        printf("Failure in communication");
        exit(EXIT_FAILURE);
    }
    
 
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    char operator = argv[3][0];
     
	
	
    int result;
    if (operator == '+') {
        result = num1 + num2;
    } else if (operator == '-') {
        result = num1 - num2;
    } else {
        printf("Invalid operator\n");
        exit(EXIT_FAILURE);
    }

    exit(result);
}

