#include "libraries.h"

void back(char* argument_pointer[],int l,char command[],int background_flag,int procs[],int *proc_ind,char **pname,char **pargs)
{
	char dir[2] = "/.";
	char *path = getenv("PATH");
	pid_t ret_fork = fork() ,test;
	int status,id=-1;
	if(ret_fork < 0)
		perror("failed to execute fork command due to");
	if (ret_fork == 0)
	{
		argument_pointer[0] = &command[0];
		argument_pointer[l++] = NULL;
		int ret_exec = -100;
		if(l!=0)
		{
			setpgid(0, 0);
			ret_exec = execvp(command,argument_pointer);
		}
		if (ret_exec != -100 && ret_exec < 0)
			perror("failed to execute execvp command due to");

	}
	else
	{
		setpgid(ret_fork,ret_fork);
		if(background_flag == 0)
		{	
			pid_t return_pid = waitpid(ret_fork, &status, WUNTRACED);
		}
		if(background_flag)
		{
			procs[*proc_ind]=ret_fork;
			int val=*proc_ind;
			pname[val]=malloc(strlen(command)*sizeof(char));
			if(argument_pointer[1]){
				pargs[val]=malloc(strlen(argument_pointer[1])*sizeof(char));
				strcpy(pargs[val],argument_pointer[1]);
			}
			strcpy(pname[val],command);
			(*proc_ind) = (*proc_ind) + 1;
		}
	}
}