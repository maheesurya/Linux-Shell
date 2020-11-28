#include "libraries.h"

void fg(char arguments[],int procs[],int valid_proc[],int *proc_ind)
{
	int stat=0,a,error=0,cnt=0;
	const char delim=' ';
	char *token;
	token  = strtok(arguments,&delim);
	while(token != NULL)
	{
		cnt++;
		if(cnt==1)
			a=atoi(token);
		else
			error=1;
		token = strtok(NULL,&delim);
	}
	if(error)
			printf("error\n");
	else{
		if(!valid_proc[a] && a<*proc_ind){
			pid_t return_pid = waitpid(procs[a], &stat, WUNTRACED);
		}
		else{
			printf("error\n");
		}
	}
	return;
}