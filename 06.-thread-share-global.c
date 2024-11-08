#include <stdio.h>
#include <threads.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int global = 10;

void producer(void *arg)
{
    global = 100;
}

void consumer(void *arg)
{
    sleep(5);
    printf("The value of the shared variable is: %d\n", global);
}

void main()
{
    pthread_t thread1, thread2;

    int thread1_return = pthread_create(&thread1, NULL, (void *)producer, NULL);
    int thread2_return = pthread_create(&thread2, NULL, (void *)consumer, NULL);

    if (thread1_return != thrd_success || thread2_return != thrd_success)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("The final value of the shared variable is: %d\n", global);

    exit(EXIT_SUCCESS);
}
