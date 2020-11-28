#include "libraries.h"

void clear_str(char str[],int len)
{
	int i=0;
	for(i=0;i<len;i++)
		str[i] = '\0';
}

void clear_str_ptr(char *str[],int len)
{
	int i=0;
	for(i=0;i<len;i++)
		str[i] = '\0';
}

void sigintHandler()
{
	return;
}

int main(int argc, char* argv[])
{
	int i=0,j=0,k=0,z,p_flag = 0,dir_name_flag = 0,quit_flag=0;
	char *pname[100];
	char *pargs[100];
	int left_redir = 0;int left_redir_index = 0;
	struct utsname uname_buffer;
	int proc_id=1,procs[100]={};
	int *proc_ind = &proc_id;
	int ret_uname = uname(&uname_buffer);
	if(ret_uname < 0)
	{
		perror("failed to get username due to:");		//uname command
	}
	int flag; //for removing preceeding spaces.
	size_t size_dir = 0;
	char *dir_name = getcwd(NULL,size_dir);
	char *current_dir_name,*final_dir_name,home_dir[1000] ="~",*home;
	if(dir_name == NULL)						//cwd
	{
		perror("failed to get cwd due to:");
	}
	int ret_cmp,l;	//write check for cd ~
	int background_flag = 0;
	char *argument_pointer[(int)10e3];		//l is used for this
	char command[(int)10e4],arguments[(int)10e4],temp_char[(int)10e4],*token,arguments_echo[(int)10e4];
	home = getcwd(NULL,0);
	int valid_proc[100]={};
	signal(SIGINT, sigintHandler);
	do								//do while loop for commands
	{
		left_redir = 0;
		left_redir_index = 0;
		flag=0;
		background_flag = 0;
		current_dir_name = getcwd(NULL,0);
		if(strlen(current_dir_name) >= strlen(dir_name))
		{
			ret_cmp = strcmp(dir_name,current_dir_name);
		}
		else
			ret_cmp = 100;
		if(ret_cmp == 0)
			printf("%s%s<%s@%s:%s%s~/%s%s> %s%s%s%s",bold,green,uname_buffer.nodename,uname_buffer.sysname,green,blue,blue,green,green,bold,reset,reset);
		else if(strlen(current_dir_name) > strlen(dir_name))
		{
			size_dir = strlen(dir_name);
			dir_name_flag = 0;
			for(z=0;z<size_dir;z++)
				if(current_dir_name[z] != dir_name[z])
				{
					dir_name_flag = 1;
					break;
				}
			if(dir_name_flag == 1)
			{
				printf("%s%s<%s@%s:%s%s%s%s%s> %s%s%s%s",bold,green,uname_buffer.nodename,uname_buffer.sysname,green,blue,current_dir_name,blue,green,green,bold,reset,reset);
			}
			else
			{
				final_dir_name = strcat(home_dir,&current_dir_name[size_dir]);
				printf("%s%s<%s@%s:%s%s%s%s%s> %s%s%s%s",bold,green,uname_buffer.nodename,uname_buffer.sysname,green,blue,final_dir_name,blue,green,green,bold,reset,reset);
				clear_str(home_dir,1000);
				home_dir[0] = '~';
			}
		}
		else
		{
			printf("%s%s<%s@%s:%s%s%s%s%s> %s%s%s%s",bold,green,uname_buffer.nodename,uname_buffer.sysname,green,blue,current_dir_name,blue,green,green,bold,reset,reset);
		}
		clear_str(temp_char,(int)10e4);
		fgets(temp_char,sizeof (temp_char),stdin);
		const char delim = ';';
		token  = strtok(temp_char,&delim);
		int status;
		pid_t pid = waitpid(-1,&status,WNOHANG);
		if(pid>0){
			if(WIFEXITED(status))
			{	
				printf("process with pid %d exited normally\n",pid);
				int test_proc=1;
				while(procs[test_proc]!=pid && test_proc <(*proc_ind)+1)
					test_proc++;
				if(procs[test_proc] == pid)
				{	
					valid_proc[test_proc]=1;
				}
			}
			else if(WIFSIGNALED(status))
			{
				printf("process with pid %d was terminated by a signal\n", pid);
				int test_proc=1;
				while(procs[test_proc]!=pid && test_proc <(*proc_ind)+1)
					test_proc++;
				if(procs[test_proc] == pid)
					valid_proc[test_proc]=1;
			}
		}
		while(token != NULL && !quit_flag)
		{
			clear_str(command,(int)10e4);
			clear_str(arguments,(int)10e4);
			clear_str(arguments_echo,(int)10e4);
			clear_str_ptr(argument_pointer,(int)10e3);
			i=0;
			p_flag=0;
			j=0;
			k=0;
			l=1;
			current_dir_name = getcwd(NULL,0);
			while(token[i] == ' ' || token[i] == '\t')
				i++;
			if(token[i] == '\n')
			{
				break;
			}
			else
			{
				while(token[i] != ' ' && token[i] != '\n' && token[i] != EOF && token[i] != '\0' && token[i] != '<' && token[i] != '>' && token[i] != '|')
				{
					command[j++] = token[i++];
				}
				command[j++] = '\0';
				while(token[i] == ' ' || token[i] == '\t')
				{
					i++;
				}
				while(token[i] !='\0' && token[i] != '\n')
				{
					if(token[i] == ' ' || token[i] == '\t')
					{
						arguments_echo[k] = token[i];
						arguments[k++] = '\0';
						p_flag=0;
						i++;
						continue;
					}
					if (token[i] == '&')
					{
						background_flag = 1;
						i++;
						continue;
					}
					if(token[i] == '|' || token[i] == '<' || token[i] == '>')
					{
						left_redir = 1;
						i++;
						argument_pointer[l++] = NULL;
						redir(token,command,argument_pointer,token[i-1],token[i] ,token);
						break;
						//do something to go to next semi colon code
					}
					/*if(token[i] == '<' || token[i] == '>')
					{
						left_redir = 1;
						i++;
						argument_pointer[l++] = NULL;
						redir_dir(token,command,argument_pointer,token[i],token[i+1],token);
						break;
					}*/
					if(p_flag == 0)
					{
						argument_pointer[l++] = &arguments[k];
						p_flag = 1;
					}
					arguments_echo[k] = token[i];
					arguments[k++] = token[i++];
				}
				if(left_redir == 1)
				{
					left_redir = 0;
					token = strtok(NULL,&delim);
					continue;
				}
			}
			i = 0;
			// strcpy(command,)
			//write code for executing the commands
			{
				if(j == 3 && command[i] == 'c' && command[i+1] == 'd' && (background_flag == 0))	//check for i+1 < length
				{
					cd(arguments_echo,arguments,home);
				}
				else if(j == 4 && command[i] == 'p' && command[i+1] == 'w' && command[i+2] == 'd' && (background_flag == 0))
				{
					pwd(current_dir_name);
				}

				//write code for other commands
				// check for 'echon'
				else if (j == 5 && command[i] == 'e' && command[i+1] == 'c' && command[i+2] == 'h' && command[i+3] == 'o' && (background_flag == 0))
				{
					echo(k,arguments_echo);
				}
				// code for ls
				else if(j == 3 && command[i] == 'l' && command[i+1] == 's'  && (background_flag == 0))
				{
					ls(current_dir_name,arguments,arguments_echo,k);
				}

				else if(command[i] == 'p' && command[i+1] == 'i' && command[i+2] == 'n' && command[i+3] == 'f' && command[i+4] == 'o')
				{
					pinfo(arguments,k);
				}
				
				else if(command[i] == 's' && command[i+1] == 'e' && command[i+2] == 't')
				{
					if(command[i+3] == 'e' && command[i+4] == 'n' && command[i+5] == 'v')
					{
						env(arguments_echo);
					}
				}

				else if(command[i] == 'u' && command[i+1] == 'n' && command[i+2] == 's' && command[i+3] == 'e')
				{
					if(command[i+4] == 't' && command[i+5] == 'e' && command[i+6] == 'n' && command[i+7] == 'v')
					{
						unenv(arguments);
					}
				}

				else if(command[i] == 'n' && command[i+1] == 'i' && command[i+2] == 'g' && command[i+3] == 'h')
				{
					if(command[i+4] == 't' && command[i+5] == 's' && command[i+6] == 'w' && command[i+7] == 'a')
					{
						if(command[i+8] == 't' && command[i+9] == 'c' && command[i+10] == 'h')
						{
							//nightwatch(arguments_echo,arguments);
						}
					}
				}
				else if(command[i] == 'q' && command[i+1] == 'u' && command[i+2] == 'i' && command[i+3] == 't')
				{
					quit_flag=1;
				}
				else if (command[i] == 'j' && command[i+1] == 'o' && command[i+2] == 'b' && command[i+3] == 's')
				{
					job(procs,proc_ind,pname,pargs,valid_proc);
				}
				else if(command[i] == 'k' && command[i+1] == 'j' && command[i+2] == 'o' && command[i+3] == 'b')
				{
					kjob(arguments_echo,procs,valid_proc,proc_ind);
				}
				else if(command[i] == 'f' && command[i+1] == 'g')
				{
					fg(arguments,procs,valid_proc,proc_ind);
				} 
				else
				{
					back(argument_pointer,l,command,background_flag,procs,proc_ind,pname,pargs);
				}
			}
			token = strtok(NULL,&delim);
		}

	}while(!quit_flag);
	return 0;
}