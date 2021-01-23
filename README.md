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

Task5.c
 - Write a program that has a main Director process which reads a file containing grades for all homeworks of all chapters and creates [x] number of manager processes. Each manager processes willl create [y] number of worker processes and pass one homework to each of them and calculate and print the max and average 

Task7.c 
- Consider a system with 3 smoker processes and 1 agent process. Each smoker continuously rolls a cigarette and then smokes it. The smoker needs three ingredients: tobacco, paper, and matches. One of the smokers has paper, another has tobacco, and the third has matches. The agent has an infinite supply
of all three materials and (randomly) places two of the ingredients on the table each time. The smoker who has the remaining ingredient then makes and smokes a cigarette, signaling the agent on completion. The agent then puts out another two of the three ingredients, and the cycle repeats.

```
gcc -o Task7 Task7.c -pthread
```

## Process Synchronization
Task6a.c & Task6b.c
- The given bank.c program has 3 processes namely, the ​ dad ​ process and two ​ son ​ processes. The critical section (CS) in the given problem is a son withdrawing money from the bank and the dad depositing money in the bank, at randomly selected time intervals. The program in the given form has synchronization errors, i.e., these 3 processes get into a race condition when accessing the shared bank_balance variable.
- In ​ Step 1​ , you need to run the program and analyze the execution traces whereupon you have to identify the synchronization errors. After identifying the synchronization errors, you need to insert the "P(sem)" and "V(sem)" operations at the right places in the code that fix the synchronization errors.
- In​ Step 2​, you work on a measurement component. A mutex algorithm is associated with a "bounded wait" property, i.e., how long a process P is forced to wait for entry into a CS after P has expressed interest in the CS. Let’s call the wait time T(P), where T(P) is the number of times processes other than P enter the CS after P expresses interest in the CS but before P actually
enters the CS. You need to compute T(P) for all three processes in the problem and display it at the end of "N" different attempts. 




