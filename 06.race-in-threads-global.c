#include <stdio.h>
#include <threads.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int global = 100;

void thread(void *arg)
{
    int balance = global;
    srand(time(NULL) ^ thrd_current());

    if (strcmp((char *)arg, "Deposit") == 0)
    {
        usleep(rand() % 1000000);
        global = balance + 1;
        printf("%s: +[%d].\n", (char *)arg, global);
    }
    if (strcmp((char *)arg, "Withdraw") == 0)
    {
        usleep(rand() % 1000000);
        global = balance - 1;
        printf("%s: -[%d].\n", (char *)arg, global);
    }
}

void main()
{
    thrd_t thread1, thread2;

    for (int i = 1; i <= 10; i++)
    {
        int thread1_return = thrd_create(&thread1, (int (*)(void *))thread, "Deposit");
        int thread2_return = thrd_create(&thread2, (int (*)(void *))thread, "Withdraw");

        if (thread1_return != thrd_success || thread2_return != thrd_success)
        {
            perror("thrd_create");
            exit(EXIT_FAILURE);
        }

        thrd_join(thread1, NULL);
        thrd_join(thread2, NULL);
    }
    printf("The final balance is: %d\n", global);

    exit(EXIT_SUCCESS);
}

/**
 * thrd_join() is used to wait for the termination of the thread.
 * Second argument is used to store the return value of the thread.
 */