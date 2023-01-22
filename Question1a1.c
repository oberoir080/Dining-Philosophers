#include <stdio.h>
#include <pthread.h>

#define numOfPhilosophers 5
#define LEFT_PHIL (philNum+4)%numOfPhilosophers
#define RIGHT_PHIL (philNum+1)%numOfPhilosophers

int philosopherArray[numOfPhilosophers]={0,1,2,3,4};

pid_t pid[5];

// function for the philosopher thread
void* philosopher(void* philNum){
    int* i = philNum;  
    printf("Philosopher %d is HUNGRY now\n",i);
    
}

int main(){
    int philNum=0;
    
    // infinite loop to simulate the philosophers' continuous eating and thinking
    while(1){
        // creating a new thread for each philosopher
        pthread_create(&pid[philNum],NULL,&philosopher,philNum+1);

        // sleep for 2 seconds
        sleep(2);
      
        // philosopher picks up left and right fork
        printf("Philosopher %d has PICKED up the forks %d and %d\n",philNum+1,LEFT_PHIL+1,philNum+1);

        // sleep for 2 seconds
        sleep(2);

        // philosopher is eating
        printf("Philosopher %d is EATING now\n",philNum+1);

        // sleep for 2 seconds
        sleep(2);

        // philosopher puts down left and right fork
        printf("Philosopher %d has put down the forks %d and %d\n",philNum+1,LEFT_PHIL+1,philNum+1);

        // sleep for 2 seconds
        sleep(2);
      
        // increment philosopher number
        philNum=philNum+1;
        // if last philosopher, reset to first philosopher
        if(philNum+1==6){
            philNum=0;
        }
    }

    return 0;
}
