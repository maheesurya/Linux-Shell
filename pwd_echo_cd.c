#include "libraries.h"

void cd(char arguments_echo[],char arguments[],char* home)
{
	if(strlen(arguments_echo) == 0) // simple cd takes directory to home
		chdir(home);
	else
		{
			int ret_chdir = chdir(arguments);
			if(ret_chdir < 0)
				perror("failed to chdir due to:");
			//break;
		}
	return;
}

void pwd(char current_dir_name[])
{
	printf("%s\n",current_dir_name);
	return;
}

void echo(int k,char arguments_echo[])
{
	int a=0;
	while(a<k)
	{
		if(arguments_echo[a] != 34)
			if(arguments_echo[a] != 39)
				printf("%c",arguments_echo[a]);
		a++;
	}
	puts("");
	return;
}
