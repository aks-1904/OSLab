#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void)
{
    key_t key;
    int shmid;
    char *shared;

    key = ftok(".", 'S');

    shmid = shmget(key, 1024, 0666);

    if(-1 == shmid)
    {
        perror("shmget");
        return EXIT_FAILURE;
    }

    shared = (char *)shmat(shmid, NULL, 0);

    if((char *)-1 == shared)
    {
        perror("shmat");
        return EXIT_FAILURE;
    }

    printf("Data received: %s", shared);

    shmdt(shared);

    shmctl(shmid, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}