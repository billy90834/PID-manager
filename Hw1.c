#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define length 4
unsigned long bitmap[length];

int allocate_map(void){
	int i;
	int fg=0;
	for (i=0;i<length;i++){
		bitmap[i]==0;
		fg=1;
		
	}
	if(fg==1){
		return 1;
	}
	else{
		return -1;
	}
}


int allocate_pid(void){
	int i,j;
	int fg=0;
	
	int tmp;
	for(i=0;i<101;i++){
		tmp=bitmap[(i/32)]&(1<<(i%32));
		if(tmp==0){
			bitmap[(i/32)]=bitmap[(i/32)]|(1<<(i%32));
			fg=1;
			printf("Sucessful to allocate PID.The PID of new process:%d\n",i);
			
			}
		}
		
	if(fg==0){
		
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
    int a=rand()%10;
    time_t t;
    pid = allocate_pid();
    printf("\nTID:%u\n",  pthread_self());
    printf("\nAllocating PID: %d ,will sleep %d sec\n ",pid, a);
    sleep(a);
    release_pid(pid);
    printf("Releasing PID: %d\n", pid);
    pthread_exit(0);
    
}


int main(void){
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
			allocate_pid();
			for(i=0; i<length ;i++){
				printf("bitmap[%d]=%u\n",i,bitmap[i]);
				}
			for(i = 0; i < 101; i++){
        			pthread_create(&tid[i],&attr,createthread,NULL);
    			
				}
			for(i = 0; i < 101; i++){
        			pthread_join(tid[i],NULL);
    				}
		}
		else if(c==2){
			
			release_pid(100);
			for(i=0;i<length;i++){
				printf("bitmap[%d]=%u\n",i,bitmap[i]);
			}
					
		}
		else if(c==3){
			printf("exit the process\n");
			break;
		}
		else{
			printf("Please enter the number again!\n");
		}
  	 }
  	 return 0;
}

