#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    if (argc != 6) { //checks for propper amount of arguments
        fprintf(stderr, "Usage: %s divisor dividend1 dividend2 dividend3 dividend4\n", argv[0]);
        return 1;
    }

    int divisor = atoi(argv[1]); // gets divisor
    int dividends[4]; // array for dividends

    for (int i = 0; i < 4; i++) { // fills dividends array from args
        dividends[i] = atoi(argv[i + 2]);
    }

    int shm_ids[4];
    int pipe_fds[4][2];

    for (int i = 0; i < 4; i++) {  //creates pipes
        if (pipe(pipe_fds[i]) == -1) {
            perror("pipe");
            return 1;
        }

        int pid = fork(); // forks and makes sure fork is successful

        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            // Child process
            close(pipe_fds[i][1]); // close writing

            char shm_id_str[20]; // make "string" for shared memory id
            read(pipe_fds[i][0], shm_id_str, sizeof(shm_id_str));// get shared mem id

            int shm_id = atoi(shm_id_str); // convert to int


            close(pipe_fds[i][0]); // close reading

            char dividend_str[20];
            sprintf(dividend_str, "%d", dividends[i]);

            execl("./checker", "checker", argv[1], dividend_str, shm_id_str, NULL); // call checker
            perror("exec");
            exit(1);
        } else {
            // Parent process
            printf("Coordinator: forked process with ID %d.\n", pid);
            close(pipe_fds[i][0]); // close reading

            // make shared mem
            shm_ids[i] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

            if (shm_ids[i] == -1) { // check shared memory
                perror("shmget");
                return 1;
            }

            // write sh mem to pipe
            char shm_id_str[20];
            sprintf(shm_id_str, "%d", shm_ids[i]);
            write(pipe_fds[i][1], shm_id_str, sizeof(shm_id_str));
            close(pipe_fds[i][1]); // close writing
        }
    }

    // wait for children
    for (int i = 0; i < 4; i++) {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            int result;
            // get result from shared mem
            int *shm_data = (int *)shmat(shm_ids[i], NULL, 0);
            result = *shm_data;
            shmdt(shm_data);
            printf("Coordinator: result %d read from shared memory: %d is %s divisible by %d.\n", i + 1, dividends[i], result ? "": "not", divisor);
        }
    }

    return 0;
}
