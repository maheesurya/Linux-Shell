#include "libraries.h"

char pin(int val){
	char state,path1[1000]={};
	char str_line[1000]={},test1[100],test2[100];
	FILE *file1;
	sprintf(path1,"/proc/%d/status",val);
	file1 = fopen(path1,"r");
	if(file1 !=NULL)
	{
		while(fgets(str_line,500,file1) !=NULL)
		{
			fscanf(file1,"%s %s",test1,test2);
			if(strcmp(test1,"State:") == 0)
			{
				state=test2[0];
			}
		}
		return state;
	}
}

void job(int procs[],int *proc_ind,char **pname,char **pargs,int valid_proc[])
{
	int i;
	for(i=1;i<(*proc_ind);i++)
	{
		if(!valid_proc[i]){
			char stat=pin(procs[i]);
			printf("[%d] ",i);
			if(stat == 'R')
				printf("Running ");
			else if(stat == 'T')
				printf("Stopped ");
			else if(stat == 'S')
				printf("Running ");
			else if(stat == 'Z')
				printf("Zombie ");
			printf("%s ",pname[i]);
			if(pargs[i])
				printf("%s",pargs[i]);
			printf("[%d]\n",procs[i]);
		}
	}
}