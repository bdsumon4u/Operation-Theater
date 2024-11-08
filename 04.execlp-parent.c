#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
    printf("Hello, I am the parent process. My PID is %d\n", getpid());

    if (system("gcc -o 04.execlp-child 04.execlp-child.c") == -1)
    {
        perror("system");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    if (pid == 0)
    {
        printf("Child process with PID %d is EXECUTING.\n", getpid());
        execlp("./04.execlp-child", "04.execlp-child", NULL);
        printf("CHILD process with PID %d is TERMINATING.\n", getpid());
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    system("rm 04.execlp-child");
    printf("Parent process is TERMINATING.\n");
    exit(EXIT_SUCCESS);
}

/**
 * CHILD will not be printed because execlp() replaces the current process with the new process.
 * The new process will have the same PID as the old process.
 * 
 * exec
 * |-> execl("path", "arg0", "arg1", ..., NULL)
 * |---|-> execlp("file", "arg0", "arg1", ..., NULL)
 * |---|-> execle("path", "arg0", "arg1", ..., NULL, env)
 * |-> execv("path", vector)
 * |---|-> execvp("file", vector)
 * |---|-> execve("path", vector, env)
 * 
 * list, vector, path, env
 * arg0 is conventionally the name of the program.
 */