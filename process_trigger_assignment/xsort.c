#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    const char *command = "gnome-terminal -- bash -c './sort1 ";
    
    const char * secondCommand=  ";read -p \"Press Enter to close the terminal\" -s'";
    char * finalCommand = malloc(strlen(command) + strlen(argv[1]) + strlen(secondCommand));
    
    strcat(finalCommand,command);
    strcat(finalCommand,argv[1]);
    strcat(finalCommand,secondCommand);

    int result = system(finalCommand);
   
    if (result == -1) {
        perror("Error executing gnome-terminal command");
        return 1;
    }


    return 0;
}

