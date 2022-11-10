#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define length 4

unsigned long bitmap[length];

int allocate_map(void){
	int i;
	int flag=0;
	for (i=0;i<length;i++){
		bitmap[i]==0;
		flag=1;
		
	}
	if(flag==1){
		return 1;
	}
	else{
		return -1;
	}
}


int allocate_pid(void){
	int i,j;
	int flag=0;
	int k=32*length;
	int tmp;
	for(i=0;i<k;i++){
		tmp=bitmap[(i/32)]&(1<<(i%32));
		if(tmp==0){
			bitmap[(i/32)]=bitmap[(i/32)]|(1<<(i%32));
			flag=1;
			printf("Sucessful to allocate PID.The PID of new process:%d\n",i);
			break;
			}
		}
		
	if(flag==0){
		printf("Fail to allocate PID.");
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

int main(void){
	int n,i,x,k;
	printf("-----------------Allocating bitmap----------------------------\n");
	x=allocate_map();
	if(x==1){
		for(i=0;i<length;i++){
			printf("bitmap[%d]=%d\n",i,bitmap[i]);
	    	}
    	}
    else{
    	printf("Fail to allocate bitmap!\n");
	}
	while(1){
		printf("--------------------------------------------------------------\n");
		printf("(1)creat a process (2)delete a process (3)exit\n");
		printf("Please enter your choice: ");
		scanf(" %d",&n);
		if(n==1){
			allocate_pid();
			for(i=0;i<length;i++){
				printf("bitmap[%d]=%u\n",i,bitmap[i]);
			}
		}
		else if(n==2){
			int d;	
			printf("Please enter the PID you want to delete: ");
			scanf(" %d",&d);
			release_pid(d);
			for(i=0;i<length;i++){
				printf("bitmap[%d]=%u\n",i,bitmap[i]);
			}
					
		}
		else if(n==3){
			break;
		}
		else{
			printf("Please enter number again!\n");
		}
  	 }
  	 return 0;
}


