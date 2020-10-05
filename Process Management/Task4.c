// Show the values of pid, a, and b printed by the processes P, Q, and R. Guarantee that the parent terminates 
// after the children terminate (Note, you need to wait for two child processes

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    // Init children
    int child_1, child_2;
    int a=10, b=25;

    child_1 = fork(); // fork a child - call it Process Q

    // Handle failure
    if(child_1 == -1){
        printf("Child process failed");
    }

    if(child_1 == 0){ // Child successfully forked
       //print values of a, b, and process_id
       a=a+b; 
       printf("I am a child, my PID is %d\n", getpid());
       printf("Values: a = %i, b = %i\n",a,b);

       child_2 = fork(); // fork another child - call it Process R
       if(child_2!=0){

            b=b+20;
            printf("Process ID: %d\n", getpid());
            printf("Values: a = %i, b = %i\n",a,b); 
            
        } else{
            
            a=(a*b)+30;
            printf("Process ID: %d\n", getpid());
            printf("Values: a = %i, b = %i\n",a,b); 
        }

    }
    else {

       b=a+b-5;
       printf("Process ID: %d\n", getpid());
       printf("Values: a = %i, b = %i\n",a,b); 
      
    }

    // Wait for child processes to terminate
    wait(NULL);
    wait(NULL);
    return 0;

}