 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 int main(int argc, char* argv[]){
     int processID = getpid();  // get processID
     int divisor = atoi(argv[1]);     // get arguments
     int dividend = atoi(argv[2]);
     printf("Checker process [%d]: Starting.\n", processID);     //starting message
     if ( dividend % divisor == 0){    //check if is divisible
         printf("Checker process [%d]: %d *IS* divisible by %d\n", processID, dividend, divisor);
         printf("Checker process [%d]: Returning 1.\n", processID);
         exit(1);    //exit 1 as a success
    }else{ // if not say is not
        printf("Checker process [%d]: %d *IS NOT* divisible by %d\n", processID, dividend, divisor);
        printf("Checker process [%d]: Returning 0.\n", processID);
        exit(0); //exit 0 failure to divide
    }
}
