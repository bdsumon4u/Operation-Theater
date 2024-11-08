#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // mkfifo
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void main()
{
    char buffer[BUFFER_SIZE];

    if (mkfifo("pipe", 0644) == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    if (pid == 0)
    {
        sprintf(buffer, "Child[%d] process is EXECUTING.\n", getpid());
        int fd = open("pipe", O_WRONLY);
        write(fd, buffer, strlen(buffer));
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else
    {
        sleep(5);
        int fd = open("pipe", O_RDONLY);
        int n = read(fd, buffer, BUFFER_SIZE);
        close(fd);
        buffer[n] = '\0';
        printf("%s", buffer);
        wait(NULL);
        printf("Parent process is TERMINATING.\n");
        unlink("pipe");
    }

    exit(EXIT_SUCCESS);
}