#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void main()
{
    printf("Hello, I am the parent process. My PID is %d\n", getpid());

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    if (pid == 0)
    {
        for (int j = 1; j <= 10; j++)
        {
            printf("[%d->Child] with PID %d is sleeping.\n", getppid(), getpid());
            srand(time(NULL) ^ getpid());
            usleep(rand() % 1000000 + 1000000);
        }
        printf("[%d->Child] with PID %d is TERMINATING.\n", getppid(), getpid());
        exit(EXIT_SUCCESS);
    }

    sleep(50); // This is the only difference between this snippet and 03.orphan.c
    
    printf("Parent[%d] process is TERMINATING.\n", getpid());
    exit(EXIT_SUCCESS);
}

/**
 * To see the zombie process, run the program and then run the following command:
 * ps aux | grep "zombie"
 * Run the command multiple times to see the zombie process.
 * 
 * S: Sleeping
 * R: Running
 * Z: Zombie
 * N: Nice (low priority)
 * <: High-priority (not nice to other users)
 * +: Process is in the foreground process group
 * ?: Background process group (not associated with a terminal)
 */