#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>  
int main(int argc, char* argv[]){          
	if (argc != 6){ //check for correct num of args
		printf("USAGE: ./Coordinator [Divisor] [Dividend_1] [Dividend_2] [Dividend_3] [Dividend_4]\n");         
		return -1; //break if not
	}else{
		int returnValue; // local variable for storing the return values
		for ( int i = 1 ; i <= 4 ; i++){  //loop runs 4 times to create 4 children to do all checks
			int processID = fork(); //get pid from forked child
			if (processID == 0) execl("./checker", "checker", argv[1], argv[i+1], NULL); // if pid is the child then run checker
			if (processID > 0){  // when parent function is back print coordinator responses
				printf("Coordinator: forked with process ID %d\n", processID);
				printf("Coordinator: waiting for process [%d]\n", processID);
				wait(&returnValue); // wait for return value
				printf("Coordinator: child process %d returned %d.\n", processID, WEXITSTATUS(returnValue));
			}         
	}
	printf("Coordinator: exiting.\n");     //final message when program is done
	}
	return 0;
}
