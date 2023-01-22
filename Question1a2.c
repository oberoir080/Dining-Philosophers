#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define numOfPhilosophers 5
#define EATING_STATE 0
#define HUNGRY_STATE 1
#define THINKING_STATE 2

//Initializing mutex(locking mechanism) to synchronize access to a resource.
sem_t mutex;
sem_t S[numOfPhilosophers];

//Maintainig currentState array where the state of the current philosopher (EATING or HUNGRY or WAITING) is stored.
int currentState[numOfPhilosophers];
int philosopherArray[numOfPhilosophers]={0,1,2,3,4};

#define LEFT_PHIL (philNum+4)%numOfPhilosophers
#define RIGHT_PHIL (philNum+1)%numOfPhilosophers

//This function checks if the current philosopher is hungry, 
//and whether there are forks available towards the left and right of the current philosopher 
//if yes, then the current philosopher can start eating.
void stateCheck(int philNum){
    int currState;
    if(currentState[LEFT_PHIL] != EATING_STATE && currentState[RIGHT_PHIL] != EATING_STATE && currentState[philNum] == HUNGRY_STATE ){
        currState=HUNGRY_STATE;
        currentState[philNum] = EATING_STATE;
        currState=EATING_STATE;

        sleep(2);
        printf("-----A PHILOSOPHER HAS PICKED UP THE FORKS-----\n");
        printf("Philosopher %d has PICKED up the fork %d and %d\n",philNum+1,LEFT_PHIL+1,philNum+1);
        printf("Philosopher %d is EATING\n",philNum+1);
        sem_post(&S[philNum]);  //sem_post increments the value of the semaphore by 1 and if a thread is waiting it starts working on the program and decrements the value of the semaphore.
    }
}


void pick_up_fork( int currState,int philNum){
    currState = THINKING_STATE;
    sem_wait(&mutex);
    currentState[philNum] = HUNGRY_STATE;
    printf("Philosopher %d is HUNGRY now\n",philNum+1);
    currState = HUNGRY_STATE;
    stateCheck(philNum);
    sem_post(&mutex);
    sem_wait(&S[philNum]);
    sleep(2);
}

void put_down_fork(int currState,int philNum){
    currState = EATING_STATE;
    sem_wait(&mutex);
    currentState[philNum] = THINKING_STATE;

    printf("-----A PHILOSOPHER HAS PLACED THE FORKS DOWN-----\n");
    printf("Philosopher %d has PLACED the fork %d (to his/her left) and %d (to his/her right) DOWN\n",philNum+1,LEFT_PHIL+1,philNum+1);
    printf("Philosopher %d has EATEN\n",philNum+1);
    printf("-----NEXT PHILOSOPHERS-----\n");

    currState = THINKING_STATE;
    stateCheck(LEFT_PHIL);
    stateCheck(RIGHT_PHIL);

    sem_post(&mutex);
}


void* philosopher(void* num){
    int loop=1;
    while(loop){
        int* i = num;
        sleep(2);
        pick_up_fork(1,*i);
        sleep(2);
        put_down_fork(0,*i);
    }
}

int main(){
    pthread_t thread_id[numOfPhilosophers];
    sem_init(&mutex,0,1);
    for(int i = 0;i<numOfPhilosophers;i++){
        sem_init(&S[i],0,0);
    }
    for(int i = 0;i<numOfPhilosophers;i++){
        pthread_create(&thread_id[i],NULL,philosopher,&philosopherArray[i]);
        printf("Philosopher %d is THINKING\n",i+1);
    }
    for(int i=0;i<numOfPhilosophers;i++){
        pthread_join(thread_id[i],NULL);
    }
}



