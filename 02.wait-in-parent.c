#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void main()
{
    printf("Hello, I am the parent process. My PID is %d\n", getpid());
    int num_of_child = 20;
    // printf("Enter the number of child processes you want to create: ");
    // scanf("%d", &num_of_child);

    for (int i = 1; i <= num_of_child; i++)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
        }
        if (pid == 0)
        {
            for (int j = 1; j <= 10; j++)
            {
                srand(time(NULL) ^ getpid());
                usleep(rand() % 1000000 + 1000000);
                printf("Child[%d] with PID %d is sleeping.\n", i, getpid());
            }
            printf("Child[%d] with PID %d is TERMINATING.\n", i, getpid());
            exit(EXIT_SUCCESS);
        }
    }

    while (wait(NULL) != -1)
        ;

    printf("Parent process is TERMINATING.\n");
    exit(EXIT_SUCCESS);
}