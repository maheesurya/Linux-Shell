#include "libraries.h"

void kjob(char arguments_echo[],int procs[],int valid_proc[],int *proc_ind)
{
	int i=0,j=0,n=strlen(arguments_echo),cnt=0,error=0;
	int a=0,b=0;
	const char delim=' ';
	char *token;
	token  = strtok(arguments_echo,&delim);
	while(token != NULL)
	{
		cnt++;
		if(cnt==1)
			a=atoi(token);
		else if(cnt==2)
			b=atoi(token);
		else
			error=1;
		token = strtok(NULL,&delim);
	}
	if(cnt==0)
		error=1;
	if(error)
		printf("error in number of arguments passed\n");
	else
	{
		if(!valid_proc[a] && a<*proc_ind)
		{
			kill(procs[a],b);
		}
		else
			printf("Error\n");
	}
}