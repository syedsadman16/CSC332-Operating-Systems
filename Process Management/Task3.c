// Create a system with one parent process and two child processes where the children communicate using a pipe. 
// The first child will perform ls -F andp ass the output to the second child using one direction pipe, so the second one can 
// perform nl on the list of current directory contents. 

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    // Array containing arguments to be called
    char *ls[] = {"ls", "-F", NULL};
    char *nl[] = {"nl", "-s:", NULL};
    // Init children
    int child_1, child_2;
    // Pipe
    int fd[2]; 
    int p = pipe(fd);

    child_1 = fork();

    // Handle failure
    if(child_1 == -1){
        printf("Child process failed");
    }

    if(child_1 == 0){

        // Write 1 Read 0
        // Write to file descriptor
        dup2(fd[1], 1);

        close(fd[0]); // Close read end of pipe
        close(fd[1]); // Close write end

        // execvp(file_to_execute, array_of_arguments);
        execvp(ls[0], ls);
       
    }
    else {
        child_2 = fork();

        if(child_2 == 0){
            // Read from file descriptor
            dup2(fd[0], 0);

            close(fd[1]); // Close write end of pipe
            close(fd[0]); // Close stdin

            // execute nl command with output from child_1
            execvp(nl[0], nl);  
            
        }
        
        // Close the pipe
        close(fd[0]);
        close(fd[1]);
        // Wait for child process to terminate
        wait(NULL);
        printf("Process finished\n");
    }

    return 0;

}