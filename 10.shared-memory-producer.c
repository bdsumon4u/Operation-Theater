#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>

#define SHM_NAME "/shared"
#define SHM_SIZE 1024 // 1KB

int main()
{
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0644);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Typically for producer
    if (ftruncate(shm_fd, SHM_SIZE) == -1)
    {
        perror("ftruncate");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }

    char *shared = mmap(NULL, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared == MAP_FAILED)
    {
        perror("mmap");
        close(shm_fd);
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    char *message = "Hotash World!\n";
    strcpy(shared, message);
    shared += strlen(message);
    sprintf(shared, "%d\n", 123);

    close(shm_fd);
    munmap(shared, SHM_SIZE);

    return EXIT_SUCCESS;
}

/**
 * Compile: gcc 10.shared-memory-producer.c -o producer -lrt
 * Run: ./producer && cat /dev/shm/shared && rm producer
 */