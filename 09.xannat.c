#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // mkfifo
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#define BUFFER_SIZE 1024

void terminate_program(int sig)
{
    unlink("garden");
    unlink("xannat");
    exit(EXIT_SUCCESS);
}

int main()
{
    char buffer[BUFFER_SIZE];
    char *garden = "Garden: ";

    signal(SIGTERM, terminate_program);

    if (access("xannat", F_OK) == -1 && mkfifo("xannat", 0644) == -1)
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    if (access("garden", F_OK) == -1 && mkfifo("garden", 0644) == -1)
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
        int fd = open("garden", O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            _exit(EXIT_FAILURE);
        }
        do
        {
            int n = read(fd, buffer, BUFFER_SIZE);
            if (n > 0)
            {
                buffer[n] = '\0';
                write(STDOUT_FILENO, garden, strlen(garden));
                write(STDOUT_FILENO, buffer, strlen(buffer));
            }
        } while (strcmp(buffer, "bye\n") != 0);
        close(fd);
        kill(getppid(), SIGTERM);
    }
    else
    {
        int fd = open("xannat", O_WRONLY);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        do
        {
            int n = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            buffer[n] = '\0';
            write(fd, buffer, strlen(buffer));
        } while (strcmp(buffer, "bye\n") != 0);
        close(fd);
        kill(pid, SIGTERM);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}