#include "libraries.h"

void env(char arguments_echo[])
{
	int i=0,j=0,n=strlen(arguments_echo),cnt=0,error=0;
	char a[100]={},b[100]={};
	const char delim=' ';
	char *token;
	token  = strtok(arguments_echo,&delim);
	while(token != NULL)
	{
		cnt++;
		if(cnt==1)
			strcpy(a,token);
		else if(cnt==2)
			strcpy(b,token);
		else
			error=1;
		token = strtok(NULL,&delim);
	}
	if(cnt==0)
		error=1;
	if(error)
		printf("error in number of arguments passed\n");
	else
		setenv(a,b,1);
}