#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define QTD_MESSAGES 2

int main(void)
{
    int pipeFileDescriptors[2];
    int returnStatus;
    char writeMessages[QTD_MESSAGES][20] = {"Maria", "Joao andou a noite"};
    char readMessages[20];
    memset(readMessages, '\0', sizeof(char) * 20);

    returnStatus = pipe(pipeFileDescriptors);

    if (returnStatus == -1) {
        printf("Error when create pipe\n");
        return 1;
    }

    pid_t pid;

    printf("Writing Message %d is %s\n", 1, writeMessages[0]);
    write(pipeFileDescriptors[1], writeMessages[0], sizeof(char) * 20);

    pid = fork();

    if (pid == 0){
        read(pipeFileDescriptors[0], readMessages, sizeof(char) * 20);
        printf("Reading Message %d is %s\n", 1, readMessages);
        exit(0);
    }

    else {
            printf("Writing Message %d is %s\n", 2, writeMessages[1]);
            write(pipeFileDescriptors[1], writeMessages[1], sizeof(char) * 20);

            pid = fork();

            if (pid == 0){
                read(pipeFileDescriptors[0], readMessages, sizeof(char) * 20);
                printf("Reading Message %d is %s\n", 2, readMessages);
                exit(0);
            }
            else{
                return 0;
            }
    }    
}