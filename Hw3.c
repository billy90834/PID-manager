#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define length 4

pthread_mutex_t mutex;    // Declare the name of pthread_mutex_t

unsigned long bitmap[length];

int allocate_map(void){
	int i;
	int fg=0;//bitmap 是否成功
	for (i=0;i<length;i++){
		bitmap[i]=0;
		fg=1;
		
	}
	if(fg==1){
		return 1; // return 1 if successful
	}
	else{
		return -1;// return —1 if unsuccessful
	}
}


int allocate_pid(void){
	int i,j;
	int fg=0;
	
	int tmp;
	for(i=0; i<100; i++){
		tmp=bitmap[(i/32)]&(1<<(i%32));
		if(tmp==0){
                bitmap[(i/32)]=bitmap[(i/32)]|(1<<(i%32));
                fg=1;
                
		return i;               
        }
        
	}
		
	if(fg==0){
		printf("allocate PID failed");
		return -1;
	}
}
	
void release_pid(int pid){
	int tmp=bitmap[(pid/32)]&(1<<(pid%32));
	if(tmp!=0){
		bitmap[(pid/32)]=bitmap[pid/32]&~(1<<(pid%32));
	}
	else{
		printf("This PID is not allocated.\n");
	}
}


void *createthread(void *param) {
    int i, pid,c;
    int a=rand()%4;
    time_t t;
    pid = allocate_pid();
    printf("\nTID:%u\n",  pthread_self());
    printf("Allocating PID: %d ,will sleep %d sec\n ",pid, a);
    //critical section start
    pthread_mutex_lock( &mutex );      //Lock the critical section
    sleep(a);
    release_pid(pid);
    printf("Releasing PID: %d\n", pid);
    pthread_mutex_unlock ( &mutex);	//Unlock the critical section.
    //critical section end

    
    pthread_exit(0);
    
}


int main(void){
	pthread_mutex_init(& mutex  , NULL );          //Initializes the mutex

	int c,i,a,k;
	
	pthread_t tid[100];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	printf("-----------------Allocating bitmap----------------------------\n");
	a=allocate_map();
	if(a==1){
		for(i=0;i<length;i++){
			printf("bitmap[%d]=%d\n",i,bitmap[i]);
	    	}
    	}
    	else{
    		printf("Fail to allocate bitmap!\n");
	}
	while(1){
		printf("--------------------------------------------------------------\n");
		printf("(1)creat 100 thread (2)exit\n");
		printf("Please input your choice: ");
		scanf(" %d",&c);
		if(c==1){
			
			for(i=0; i<length ;i++){
				printf("bitmap[%d]=%u\n",i,bitmap[i]);
				}
			for(i = 0; i < 100; i++){
        			pthread_create(&tid[i],NULL,createthread,(void*)&i);
                		}
            		sleep(1);
            		for(i=0; i<length ;i++){
				printf("bitmap[%d]=%u\n",i,bitmap[i]);
				}
            
			for(i = 0; i < 100; i++){
        			pthread_join(tid[i],NULL);
    				}
            		for(i=0; i<length ;i++){
				printf("bitmap[%d]=%u\n",i,bitmap[i]);
				}
		}
		else{
			printf("exit the process\n");
			break;
			
					
		}
		
		
  	 }
  	 pthread_mutex_destroy (& mutex );
  	 return 0;
}
