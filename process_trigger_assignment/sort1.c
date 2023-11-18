#include <stdio.h>
#include <stdlib.h>


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int main(int argc, char *argv[]) {
    
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error occured while opening file");
        return 1;
    }
    
    int numbers[1000];
    int numCount = 0;

    while (numCount < 1000 && fscanf(file, "%d", &numbers[numCount]) == 1) {
        numCount++;
    }
    
    fclose(file);

    bubbleSort(numbers, numCount);
    
    
    printf("Sorted numbers:\n");
    for (int i = 0; i < numCount; i++) {
        printf("%d\n", numbers[i]);
    }

    return 0;
}

