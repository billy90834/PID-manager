
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MIN_PID 0
#define MAX_PID 128
/* Declare an integer array with 4701 slots for pids */
int pid_array [4701];
int last;

/* The function below creates and initializes an array data structure for representing pids */
int allocate_map(void) {
  int i;
  for (i = 0; i <=(MAX_PID - MIN_PID); i++) {
    pid_array[i] = 0;
  }
  last = 0;
  if (pid_array[4700] == 0) {
    return 1;           // return 1 if successful
  } else {
    return -1;          // return —1 if unsuccessful
  }
}

/* The function below allocates and returns a pid */
int allocate_pid(void) {
    int i = 0;        // Loop counter
    int next;         // Pointer to next pid
    if (last == MAX_PID) {
      next = MIN_PID;
    } else {
      next = last + 1;
    }
    while ((i <= (MAX_PID - MIN_PID)) && (pid_array[next] == 1)) {
      ++i;
      ++next;
      if (next > MAX_PID) {
        next = MIN_PID;
      }
    }
    if (i == (MAX_PID - MIN_PID) + 1) {
        return -1;      // return — 1 if unable to allocate a pid (all pids are in use)
    }
    pid_array[next] = 1;
    last = next;
    return last ;
}


/* The function below releases a pid */
void release_pid(int pid) {
    pid_array[pid ] = 0;
}

// We need this function to avoid the array from over filling up
int PID_slot_number(int pid){
    return pid_array[pid ];
}

/////////////////////////////////////////////////////////

void *createProcess(void *param) {
    int i, pid,c;
   
    pid = allocate_pid();
    printf("Allocating PID: %d\n TID:%u\n", pid, pthread_self());
    sleep(rand() % 10);
    
    release_pid(pid);
    printf("Releasing PID: %d\n", pid);
    /*pthread_exit(0);*/
    return 0;
}

int  main() {
    int i, pid, c;
    time_t t;
    srand((unsigned) time(&t));
    printf("Allocating map: %d\n\n", allocate_map());
    printf("------------------allocating bitmap------------------------");
    printf("\n(1) create 100 process  (2)exit\n ");
    scanf("%d",&c);
    
    pthread_t tid[100];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    switch(c)
    {
    case 1:
    // Create threads
    for(i = 0; i < 100; i++){
        pthread_create(&tid[i],&attr,createProcess,NULL);
    }
    for(i = 0; i < 100; i++){
        pthread_join(tid[i],NULL);
    }break;
    
    // Then join threads
    
    case 2:
    printf("exit this process\n");}
    
}
