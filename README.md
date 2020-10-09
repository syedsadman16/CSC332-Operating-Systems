# Operating Systems Assignments
A few assignments from CSC332 Operating Systems with C programming in Linux. Each folder contains C program files containing my solution to the tasks. A brief description is listed under Contents in the README.

# Contents

## Threads
(Note: this assignment was written in Java, not C)

Main.java
- Develop a multithreaded app that can find the integer in the range 1 to 10000 that has the largest
number of divisors. It should print that integer as well as the time spent to finish the calculation. You
can use any language (e.g. C, Java, or Python)

## Process Management

Task3.c
- Create a system with one parent process and two child processes where the children communicate using a pipe. Use fork() and one formof exec() functions so that the first child will perform ls -F andp ass the output to the second child using one direction pipe, so the second one can perform nl on the list of current directory contents. Later the second child process will print to the screen

Task4.c
- Consider the parent process as P. The program consists of fork() system call statements placed at different points in the code to create new processes Q and R. The program also shows three variables: a, b, and pid - with the print out of these variables occurring from various processes. Show the values of pid, a, and b printed by the processes P, Q, and R. Guarantee that the parent terminates after the children terminate (Note, you need to wait for two child processes

## File Management and System Calls

Task1.c
- The ​cp command copies the source file specified by the SourceFile parameter to the destination file specified by the DestinationFile parameter. Write a C program that mimics the ​ cp ​ command using ​ open() ​ system call to open ​ source.txt ​file in read-only mode and copy the contents of it to ​ destination.txt ​ using ​ read() ​ and ​ write() ​ system calls.

Task2.c
- The UNIX ​cat command has three functions with regard to text files: displaying them, combining copies
of them and creating new ones. Write a C program to implement a command called ​ printcontent t​hat takes a (text) file name as argument and display its contents. Report an appropriate message if the file does not exist or can’t
be opened (i.e. the file doesn’t have read permission). 






