#include <stdio.h>
#include <threads.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

sem_t semaphore;

void deposit(void *arg)
{
    sem_wait(&semaphore);
    int balance = *(int *)arg;
    srand(time(NULL) ^ thrd_current());
    usleep(rand() % 1000000);
    *((int *)arg) = balance + 1;
    printf("Deposit: +[%d].\n", *(int *)arg);
    sem_post(&semaphore);
}

void withdraw(void *arg)
{
    sem_wait(&semaphore);
    int balance = *(int *)arg;
    srand(time(NULL) ^ thrd_current());
    usleep(rand() % 1000000);
    *((int *)arg) = balance - 1;
    printf("Withdraw: -[%d].\n", *(int *)arg);
    sem_post(&semaphore);
}

void main()
{
    int local = 100;
    thrd_t thread1, thread2;
    sem_init(&semaphore, 0, 1); // Binary semaphore
    // Second argument is 0 for thread sharing and 1 for process sharing.
    // Third argument is to specify how many threads can access the semaphore at the same time.

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
    sem_destroy(&semaphore);

    exit(EXIT_SUCCESS);
}
