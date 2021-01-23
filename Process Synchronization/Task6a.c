#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"
#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1

FILE *fp1, *fp2, *fp3, *fp4, *fd;			/* File Pointers */

int semaphore;
int semaphore2; 

main()
{
	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables

	int n = 0;						// Time measurements
	

	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 20;
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);


	// Keep track of the number of trials for T(P)
	fd = fopen("attempt.txt", "w");
	fprintf(fd, "%d \n", n);
	fclose(fd);
	
	/* Creating the semaphores
	* The semget() system call returns the semaphore set identifier 
	* associated with the argument key. A new set of nsems semaphores is 
	* created if key has the value IPC_PRIVATE or if no existing semaphore 
	* set is associated with key and IPC_CREAT is specified in semflg.
	*/
	semaphore = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
	semaphore2 = semget(IPC_PRIVATE, 1, 0666|IPC_CREAT);
	sem_create(semaphore,1);
	sem_create(semaphore2, 20);

	//Create child processes that will do the updates
	if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
	
		N=5;
		for(i=1;i<=N; i++)
		{
			// When account balance being accessed
			P(semaphore); 
			P(semaphore2); 

			// Increment number of trials and write
			// r+ open text file for update, dont create != exist
			fd = fopen("attempt.txt", "r+");
			fscanf(fd, "%d", &n);
			fseek(fd, 0L, 0);
			n++;
			fprintf(fd, "%d\n", n );
			fclose(fd);

			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);
			
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */

			// Dad has finished updates
			V(semaphore);
			V(semaphore2);
		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{
				// Poor son attempts to do updates
				P(semaphore); 
				P(semaphore2);

				// Increment number of trials and write
				fd = fopen("attempt.txt", "r+");
				fscanf(fd, "%d", &n);
				fseek(fd, 0L, 0);
				n++;
				fprintf(fd, "%d\n", n );
				fclose(fd);

				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2,"%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}

				V(semaphore);
				V(semaphore2);
			}
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{
					// Second son attempts
					P(semaphore);
					P(semaphore2);

					// Increment number of trials and write
					fd = fopen("attempt.txt", "r+");
					fscanf(fd, "%d", &n);
					fseek(fd, 0L, 0);
					n++;
					fprintf(fd, "%d\n", n );
					fclose(fd);

					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
					//second son finsihed attempts
					V(semaphore);
					V(semaphore2);
				}
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				// Display number of attempts
			    fd=fopen("attempt.txt","r+");
				fscanf(fd,"%d",&n);
				printf("Num of attempt: %d\n", n);
				fclose(fd);
				
			}
			exit(0);
		}
		exit(0);
	}
	exit(0);
}
