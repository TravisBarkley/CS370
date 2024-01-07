Travis-Barkley-HW2 

The objective of this assignment is to get you to use the fork(), exec(), and wait() system calls on Unix.

(all below was written for the initial submission, this professor asked us to share are thoughts + clarify things in our code) 

This assignment had plent of speed bumps for me but looking back wasn't as hard as I thought. 
I got the checker working quite quickly and then the coordinator after that but I couldn't get the coordinator to call the exec() command properly. After looking around I tried execlp() which sounded like it would fix my problems but that wouldn't call it either. Eventually I went back to exec() and the compiler told me to use execl() and it finally got my program working. 
I was not completely sure what the Checker.h file was for (i need to brush up on my c for sure) but the Makefile had calls to it so I just made one with a main header. 
