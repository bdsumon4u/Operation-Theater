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
    int fd[2];
    char buffer[BUFFER_SIZE];

    if (pipe(fd) == -1)
    {
        perror("pipe");
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
        write(fd[STDOUT_FILENO], buffer, strlen(buffer));
        close(fd[STDOUT_FILENO]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        int n = read(fd[STDIN_FILENO], buffer, BUFFER_SIZE);
        close(fd[STDIN_FILENO]);
        buffer[n] = '\0';
        printf("%s", buffer);
        wait(NULL);
        printf("Parent process is TERMINATING.\n");
    }

    exit(EXIT_SUCCESS);
}