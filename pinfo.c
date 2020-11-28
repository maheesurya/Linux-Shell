#include "libraries.h"

void pinfo(char arguments[],int k)
{
	int pid_val=getpid(),stu_val=0;
	char state[50]={},path1[1000]={},path2[1000]={},vmsize[10]={};
	char pid[10]={},str_line[1000]={},test1[100],test2[100];
	char execute_val[256]={};
	FILE *file1,*file2;
	if(k==0){
		sprintf(path1,"/proc/%d/status",pid_val);
 		sprintf(path2,"/proc/%d/exe",pid_val);
	}
	else{
		sprintf(path1,"/proc/%s/status",arguments);
 		sprintf(path2,"/proc/%s/exe",arguments);
	}
	file1 = fopen(path1,"r");
	if(file1 !=NULL)
	{
		while(fgets(str_line,500,file1) !=NULL)
		{
			fscanf(file1,"%s %s",test1,test2);
			if(strcmp(test1,"Pid:") == 0)
			{
				strcpy(pid,test2);
			}
			else if(strcmp(test1,"VmSize:") == 0)
			{
				strcpy(vmsize,test2);
			}
			else if(strcmp(test1,"State:") == 0)
			{
				strcpy(state,test2);
			}
		}
		fclose(file1);
		file2 = fopen(path2,"r");
		readlink(path2,execute_val,256);
		printf("Process Id: %s\n", pid);
		printf("State: %s\n",state);
		if(vmsize[0]==0)
		{
			vmsize[0]='0';
		}
		printf("Virtual MemorySize: %skB\n", vmsize);
		printf("Executable Path: ");
		for(stu_val=0;stu_val<299;stu_val++)
		{	
			if(execute_val[stu_val]!='0')	
				printf("%c",execute_val[stu_val]);
			else 
				break;
		}
		printf("\n");
		if(file2!=0)
			fclose(file2);
	}
}
