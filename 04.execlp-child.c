#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void main()
{
    printf("Hello, I am the child process. My PID is %d\n", getpid());
    for (int j = 1; j <= 10; j++)
    {
        printf("[%d->Child] with PID %d is sleeping.\n", getppid(), getpid());
        srand(time(NULL) ^ getpid());
        usleep(rand() % 1000000 + 1000000);
    }
    printf("[%d->Child] with PID %d is TERMINATING.\n", getppid(), getpid());
    exit(EXIT_SUCCESS);
}