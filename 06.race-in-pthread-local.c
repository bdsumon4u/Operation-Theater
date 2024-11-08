#include <stdio.h>
#include <threads.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void deposit(void *arg)
{
    int balance = *(int *)arg;
    srand(time(NULL) ^ thrd_current());
    usleep(rand() % 1000000);
    *((int *)arg) = balance + 1;
    printf("Deposit: +[%d].\n", *(int *)arg);
}

void withdraw(void *arg)
{
    int balance = *(int *)arg;
    srand(time(NULL) ^ thrd_current());
    usleep(rand() % 1000000);
    *((int *)arg) = balance - 1;
    printf("Withdraw: -[%d].\n", *(int *)arg);
}

void main()
{
    int local = 100;
    pthread_t thread1, thread2;

    for (int i = 1; i <= 10; i++)
    {
        int thread1_return = pthread_create(&thread1, NULL, (void *)deposit, &local);
        int thread2_return = pthread_create(&thread2, NULL, (void *)withdraw, &local);

        if (thread1_return != thrd_success || thread2_return != thrd_success)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
    }
    printf("The final balance is: %d\n", local);

    exit(EXIT_SUCCESS);
}

/**
 * pthread_detach() is used to detach the thread, so that the resources are automatically released when the thread terminates.
 * pthread_detach(pthread_t thread); doesn't catch the return value of the thread.
 * pthread_exit() is used to terminate the calling thread.
 */