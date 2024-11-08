#include <stdio.h>
#include <threads.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
    thrd_t thread1, thread2;

    for (int i = 1; i <= 10; i++)
    {
        int thread1_return = thrd_create(&thread1, (int (*)(void *))deposit, &local);
        int thread2_return = thrd_create(&thread2, (int (*)(void *))withdraw, &local);

        if (thread1_return != thrd_success || thread2_return != thrd_success)
        {
            perror("thrd_create");
            exit(EXIT_FAILURE);
        }

        thrd_join(thread1, NULL);
        thrd_join(thread2, NULL);
    }
    printf("The final balance is: %d\n", local);

    exit(EXIT_SUCCESS);
}

/**
 * thrd_join() is used to wait for the termination of the thread.
 * Second argument is used to store the return value of the thread.
 */