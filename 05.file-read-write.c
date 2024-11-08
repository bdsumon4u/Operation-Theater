#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

void main()
{
    char buffer[BUFFER_SIZE];

    int fdw = open("HotashTech.txt", O_WRONLY | O_CREAT, 0644);
    printf("What do you want to write in the file?\n");
    scanf("%[^\n]", buffer);
    if (write(fdw, buffer, strlen(buffer)) == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }
    close(fdw);

    printf("Modify the file HotashTech.text fast!\n");
    sleep(10);
    printf("Reading the file HotashTech.txt\n");

    int fdr = open("HotashTech.txt", O_RDONLY | O_CREAT, 0644);
    int n = read(fdr, buffer, BUFFER_SIZE);
    if (n == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("The content of the file is: %s\n", buffer);
    close(fdr);

    unlink("HotashTech.txt");
    exit(EXIT_SUCCESS);
}