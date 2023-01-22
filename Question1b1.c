#include <stdio.h>
#include <pthread.h>

#define numOfPhilosophers 5 // Number of philosophers at the table
#define LEFT_PHIL (philNum+4)%numOfPhilosophers // Macro to calculate the left philosopher's number
#define RIGHT_PHIL (philNum+1)%numOfPhilosophers // Macro to calculate the right philosopher's number

int philosopherArray[numOfPhilosophers]={0,1,2,3,4}; // Array to store the philosopher's numbers

pid_t pid[5]; // Thread ID array

void* philosopher(void* philNum){ // Function for philosopher thread
    int* i = philNum;   
    printf("Philosopher %d is HUNGRY now\n",i); // Philosopher is hungry
    
}

int main(){
    int philNum=0; // Initializing philosopher number
    int bowlNum=1; // Initializing bowl number

    while(1){

        pthread_create(&pid[philNum],NULL,&philosopher,philNum+1); // Creating a new thread for philosopher

        sleep(2); // Sleep for 2 seconds
      
        printf("Philosopher %d has PICKED up the forks %d and %d\n",philNum+1,LEFT_PHIL+1,philNum+1); // Philosopher picks up left and right fork

        sleep(2);

        printf("Philosopher %d is EATING now from BOWL %d\n",philNum+1,bowlNum); // Philosopher is eating

        sleep(2);

        printf("Philosopher %d has put down the forks %d and %d\n",philNum+1,LEFT_PHIL+1,philNum+1); // Philosopher puts down left and right fork

        sleep(2);
        
        // pthread_join(&pid[philNum],NULL);
        bowlNum=bowlNum+1; // Increment bowl number

        if(bowlNum>2){ // Check if all bowls have been used
            bowlNum=1;
        }

      
        philNum=philNum+1; // Increment philosopher number
        if(philNum+1==6){
            philNum=0;
        }
    }

    return 0;
}
