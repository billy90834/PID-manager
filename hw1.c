#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<semaphore.h>

#define MIN_PID 0
#define MAX_PID 128
pthread_mutex_t lock;
int PID_TABLE[128][2];
int n;

int count_running_threads()
{
	int i; int count=0;
	for(int i=0;i<129;i++)
	{
		if(PID_TABLE[i][1]!=-1)
		{
		   count++;
		  // printf("\t %d",i+100);
		}
	}
	
	return count;
}

int allocate_pid(int thread_no)
{
	
	int temp=-1; int i,count; 
	
	for(i=0;i<129;i++)
	{
		if(PID_TABLE[i][1]!=-1) continue;
		else
		{
			temp=PID_TABLE[i][0];
		//	PID_TABLE[i][0]=-1;
			PID_TABLE[i][1]=thread_no;
			break;
		}
	}
	
	return temp;
	
}
void fun(void *arg)
{	
	pthread_mutex_lock(&lock);
	int c;
	c=(int)arg;
	int temp=allocate_pid(c);
	pthread_mutex_unlock(&lock);
	

		printf("\np%d is allocated pid %d",c,temp);
		sleep(1);
		pthread_exit(0);
	printf("this line will never execute");
	
	
}

void map()
{
	int i;
	for(i=0;i<129;i++)
	{
		PID_TABLE[i][0]=i+MIN_PID;
		PID_TABLE[i][1]=-1;		
	}
	
}
void release_pid(int pid)
{
	int i;
	for(i=0;i<129;i++)
	{
		if(PID_TABLE[i][0]==pid&&PID_TABLE[i][1]!=-1)
		{
			printf("\n Termination successful");
			printf("\n process p%d was holding id %d",PID_TABLE[i][1],pid);
			printf("\nId %d is free now",pid);
			PID_TABLE[i][1]=-1;
			return;
		}
		
	}
	printf("\n No thread was assingned with id %d",pid);	
}
int max_pid()
{
	int i,max=-1;
	for(i=0;i<129;i++)
	{
		if(PID_TABLE[i][1]>max)
			max=PID_TABLE[i][1];	
	}
	return max+1;

}
void show_map()
{
	int i;
	for(i=0;i<129;i++)
	{
		
		printf("\n\tpid  %d  ------>",PID_TABLE[i][0]);
		if(PID_TABLE[i][1]==-1) printf("\t free");
		else
		printf("\t%d",PID_TABLE[i][1]);
		
	}


}
int main()
{
	pthread_mutex_init(&lock,NULL);
	map();
	
	pthread_t p[2000];
	int c,pid,thread_count=0,avail_threads=0,temp=0; char ch[10];  long i; 
	do
	{
		printf("\n1. create new threads\n2. delete a thread\n3. Show running threads\n4. show pid utilisation");
		scanf("%d",&c);
		switch(c)
		{
		case 1:
		printf("How many threads you want to create");
				scanf("%d",&n);
				thread_count=max_pid();
				avail_threads=129-count_running_threads();
				if(n>avail_threads)
					{
						temp=n-avail_threads; 
						printf("%d threads can be allocated pid",temp);
						temp=n-avail_threads;
					}
						
				
				for(i=thread_count;i<thread_count+n-temp;i++)
						pthread_create(&p[i],NULL,fun,(void*)i);	
				for(i=thread_count;i<thread_count+n-temp;i++)
						pthread_join(p[i],NULL); break;
		case 2:
				//printf("enter the thread id to terminate");
				printf("enter the thread id to delete");
				scanf("%d",&pid);
				release_pid(pid);
				break;
		case 3:
				printf("%d threads are running",count_running_threads());
				//running_threads();
				break;
		case 4:
				show_map(); break;
		default:
			printf("\ninvalid choice"); 
	}

		
			printf("\ny/n");fflush(stdin);
			scanf("%s",&ch);
	}while(strcmp(ch,"y")==0||strcmp(ch,"yes")==0||strcmp(ch,"Y")==0);


	pthread_mutex_destroy(&lock);
	return 0;


}
