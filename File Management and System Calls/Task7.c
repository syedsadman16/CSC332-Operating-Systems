/*
*Consider a system with 3 smoker processes and 1 agent process. Each smoker continuously rolls a
cigarette and then smokes it. The smoker needs three ingredients: tobacco, paper, and matches. One of
the smokers has paper, another has tobacco, and the third has matches. The agent has an infinite supply
of all three materials and (randomly) places two of the ingredients on the table each time. The smoker who
has the remaining ingredient then makes and smokes a cigarette, signaling the agent on completion. The
agent then puts out another two of the three ingredients, and the cycle repeats.

Write program to synchronize the agent and smoker processes using pthreads
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <pthread.h>


/*
 * Create table and references 
 */ 
#define tobacco 1 
#define paper 2
#define match 3

int table[2];

/*
 * Initializing all the pthreads
 */ 
pthread_t smokerOne_pthread;
pthread_t smokerTwo_pthread;
pthread_t smokerThree_pthread;

/*
 * Initializing all the mutexes
 */ 
pthread_mutex_t agent_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tobacco_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t paper_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t match_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int smokerOne;
int smokerTwo;
int smokerThree;

/*
 * Since list of ingrtedients are mapped to a integer,
 * use the integer as a reference to get the ingredient
 */ 
char* ingredientType(int type){
    if (type == tobacco)
        return "Tobacco";
    	
    if (type == paper)
        return "Paper";
    	
    if (type == match)
        return "Match"; 
     
    return "";
}

char* clearTables(){
    table[0] = 0;
    table[1] = 0;
}


void* smoker1(){
    while(true){
        // Smoker 1 is ready to go once signaled by the agent 
        pthread_mutex_lock(&tobacco_mutex);
        pthread_mutex_lock(&mutex);

        printf("Smoker 1 has Tobacco\n");
        printf("Smoker 1 picks up %s and %s from table\n",
        ingredientType(table[0]), ingredientType(table[1]));

        // Reset values 
        clearTables();
        printf("Smoker 1 combines the ingredients and smokes the cigarette\n\n");

        // Unlocking the mutex to signal agent for completion
        pthread_mutex_unlock(&agent_mutex);
        pthread_mutex_unlock(&mutex);
    }
}

void* smoker2(){
    while (true){
        // Smoker 2 is ready to go 
        pthread_mutex_lock(&match_mutex);
        pthread_mutex_lock(&mutex);

        printf("Smoker 2 has match\n");
        printf("Smoker 2 picks up %s and %s from table\n",
        ingredientType(table[0]), ingredientType(table[1]));

        // Reset values 
        clearTables();
        printf("Smoker 2 combines the ingredients and smokes the cigarette\n\n");

        // Unlocks the mutex
        pthread_mutex_unlock(&agent_mutex);
        pthread_mutex_unlock(&mutex);
    }
}

void* smoker3(){
    while (true){
        // Smoker 3 is ready to go 
        pthread_mutex_lock(&paper_mutex);
        pthread_mutex_lock(&mutex);

        printf("Smoker 3 has paper\n");
        printf("Smoker 3 picks up %s and %s from table\n",
        ingredientType(table[0]), ingredientType(table[1]));

        clearTables();
        printf("Smoker 3 combines the ingredients and smokes the cigarette\n\n");

        // Unlocks the mutex
        pthread_mutex_unlock(&agent_mutex);
        pthread_mutex_unlock(&mutex);
    }
}

void agent(){

    int ingredientCount = 10;

    /*
     * Let the agent place ingrendie
     */ 
    for (int i = 0; i < ingredientCount; i++){

        /*
         * Generate random ingredient based on definitions 
         */ 
        int random = ((rand() % 3) + 1);
        pthread_mutex_lock(&mutex);
       
        /*
         * Agent places tobacco and paper on the table
         * Smoker 1 has the match as a remaining ingredient
         */
        if(random == 1){
            table[0] = tobacco; table[1] = paper;
            printf("The Agent placed %s and %s on the table\n", 
            ingredientType(table[0]), ingredientType(table[1]));

            // Start smoker 1 thread
            pthread_mutex_unlock(&match_mutex);
        }
        
        /*
         * Agent places tobacco and matches on the table
         * Smoker 2 has the paper as a remaining ingredient
         */
        if(random == 2){
            table[0] = tobacco; table[1] = match;
            printf("The Agent placed %s and %s on the table\n", 
            ingredientType(table[0]), ingredientType(table[1]));

            // Start smoker 2 thread 
            pthread_mutex_unlock(&paper_mutex);
        } 

        /*
         * Agent places tobacco and matches on the table
         * Smoker 3 has the paper as a remaining ingredient
         */
         if(random == 3){
            table[0] = match; table[1] = paper;
            printf("The Agent placed %s and %s on the table\n", 
            ingredientType(table[0]), ingredientType(table[1]));

            // Start smoker 1 thread
            pthread_mutex_unlock(&tobacco_mutex);
        }
        
       
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&agent_mutex);
    }
}



int main(int argc, char* argv[]){
    
    /*
     * Randomize seends
     */ 
    srand(time(NULL));
    
    /*
     * Setup the mutex
     */ 
    pthread_mutex_lock(&agent_mutex);
    pthread_mutex_lock(&tobacco_mutex);
    pthread_mutex_lock(&paper_mutex);
    pthread_mutex_lock(&match_mutex);
    pthread_mutex_unlock(&mutex);

    /*
     * Create pthreads associated with their own functions
     */ 
    smokerOne = pthread_create(&smokerOne_pthread, NULL, smoker1, NULL);
    smokerTwo = pthread_create(&smokerTwo_pthread, NULL, smoker2, NULL);
    smokerThree = pthread_create(&smokerThree_pthread, NULL, smoker3, NULL);
    agent();

    return 0;
}