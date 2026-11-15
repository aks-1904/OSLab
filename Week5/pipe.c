#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    pid_t pid;
    char message[] = "Graphic Era";
    char buffer[100];

    if (-1 == pipe(fd))
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid = fork();

    if (0 > pid)
    {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (0 == pid)
    {
        close(fd[0]);

        write(fd[1], message, strlen(message) + 1);

        printf("Child wrote: %s\n", message);

        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));

        printf("Parent read: %s\n", buffer);

        close(fd[0]);
        wait(NULL);
    }

    return EXIT_SUCCESS;
}