#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string.h>

#define SHM_NAME "/shared"
#define SHM_SIZE 1024

int main()
{
    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0644);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    char *shared = mmap(NULL, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared == MAP_FAILED)
    {
        perror("mmap");
        close(shm_fd);
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    write(STDOUT_FILENO, shared, strlen(shared));

    close(shm_fd);
    munmap(shared, SHM_SIZE);
    shm_unlink(SHM_NAME);

    return EXIT_SUCCESS;
}

/**
 * Compile: gcc 10.shared-memory-consumer.c -o consumer -lrt
 * Run: ./consumer && rm consumer
 */