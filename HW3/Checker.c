#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    if (argc != 4) { // check for args
        fprintf(stderr, "Usage: %s divisor dividend shm_id\n", argv[0]);
        return 1;
    }

    int divisor = atoi(argv[1]);
    int dividend = atoi(argv[2]); // get arguments in int form
    int shm_id = atoi(argv[3]);
    int result;
    if (dividend % divisor == 0) // do mod and set result val
    {
        result = 1;
    }else{
        result = 0;
    }

    printf("Checker process [%d]: starting.\n", getpid());
    printf("Checker process [%d]: read 4 bytes containing shm ID %d\n", getpid(), shm_id);


    int *shm_data = (int *)shmat(shm_id, NULL, 0); // put result in sh mem
    *shm_data = result;
    shmdt(shm_data);

    printf("Checker process [%d]: %d %s divisible by %d.\n", getpid(), dividend, result ? "*IS*" : "*IS NOT*", divisor);
    printf("Checker process [%d]: wrote result (%d) to shared memory.\n", getpid(), result);

    return 0;
}
