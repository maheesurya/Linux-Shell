#include "libraries.h"

void remove_spaces(char file_name[],char file[])
{
    int j = 0;
    int i = 0;
    while(file_name[i] == ' ' || file_name[i] == '\t')
    {
        i++;
    }
    while(file_name[i] != ' ' && file_name[i] != '\n' && file_name[i] != EOF && file_name[i] != '\0')
    {
        file[j++] = file_name[i++];
    }
    file[j++] = '\0';
}

int get_tokenizer(char arr[],int *final_exec)
{
    int i = 0;
    while(arr[i] != '<' && arr[i] != '>' && arr[i] != '|')
    {
        if(arr[i] == '\n')
        {
            *final_exec = 1;
        }
        i++;
    }
    return i;
}

void redir(char token[],char orig_command[],char *arguments_pointer[],char tokenizer,char next_tokenizer,char copy_token[])
{
    int final_exec = 0;
    char command[(int)10e3];
    char prev_token = '\0';
    char *argument_pointer[(int)10e3];
    char arguments[(int)10e3], arguments_echo[(int)10e3];
    int stdin;
    int orig_stdin = dup2(0,stdin);

    int stdout;
    int orig_stdout = dup2(1,stdout);

    int l = 0; //argument_pointer_index
    int fd[2];
    int ret_pipe = pipe(fd);
    char exec_comm[100];
    //command = token;

    int i = 0, j = 0,k = 0;
    int p_flag = 0;
    const char c1 = '<',c2[2] = ">>",c3 = '>',c4 = '|';    //printf("%c\n",tokenizer);
    do
    {
        int z = 0,y = i;
        z = 0;
        while(token[y])
        {
            command[z++] = token[y++];
        }
        clear_str(arguments,(int)10e3);
        clear_str(arguments_echo,(int)10e3);
        clear_str_ptr(argument_pointer,(int)10e3);
        int index_token = get_tokenizer(command,&final_exec);
        if(token[index_token] == '|' || final_exec == 1)
        {

                j = 0;
                k = 0;
                p_flag = 0;
                l = 1;
                while(command[i] == ' ' || command[i] == '\t')
                {
                    i++;
                }
                while(command[i] != ' ' && command[i] != '\n' && command[i] != EOF && command[i] != '\0' && command[i] != '<' && command[i] != '>' && command[i] != '|')
                {
                    exec_comm[j++] = command[i++];
                }
                exec_comm[j++] = '\0';
                while(command[i] == ' ' || command[i] == '\t')
                {
                    i++;
                }

                while(command[i] !='\0' && command[i] != '\n' && command[i] != '|' && command[i] != EOF)
                {
                    if(command[i] == ' ' || command[i] == '\t')
                    {
                        arguments_echo[k] = command[i];
                        arguments[k++] = '\0';
                        p_flag = 0;
                        i++;
                        continue;
                    }

                    if(p_flag == 0)
                    {
                        argument_pointer[l++] = &arguments[k];
                        p_flag = 1;
                    }
                    arguments_echo[k] = command[i];
                    arguments[k++] = command[i++];
                }
                arguments[k++] = '\0';
                argument_pointer[0] = &exec_comm[0];
                argument_pointer[l++] = NULL;
                int ret_fork = fork();

                //printf("exec_comm:%s\n",exec_comm);
                if(ret_fork < 0)
                {
                    perror("pipe FORK");
                }

                if(ret_fork == 0)
                {
                    if(prev_token != '\0')
                    {
                        int r_dup = dup2(fd[0],0);
                        if(r_dup < 0)
                            perror("fd[0]");
                    }
                    if(final_exec == 0)
                    {
                        int ret_dup = dup2(fd[1],1);
                        if(ret_dup < 0)
                            perror("DUP2 PIPE write111");
                    }
                    int ret_exec = execvp(exec_comm,argument_pointer);
                    if(ret_exec < 0)
                    {
                        perror("|||EXEC");
                    }
                }
                else
                {
                    int status;
                    waitpid(ret_fork,&status,WUNTRACED);
                    close(fd[1]);
                    int ret_dup = dup2(stdout,1);
                    if(ret_dup < 0)
                        perror("DUP2 PIPE write");
                }
            //command = &token[++i];
            prev_token = '|';
            while(token[i] != '|' && final_exec == 0)
            {
                i++;
            }
            i++;
        }
        else if(token[index_token] == '<')
        {
            char *comman = strtok(token,&c1);
            char *file_name;
            char file[100];
            file_name = strtok(NULL,&c1);
            if(file_name == NULL)
            {
                //change it if possible
            }
            else
            {
                remove_spaces(file_name,file);
                pid_t ret_fork = fork();
                if(ret_fork == 0)
                {
                    FILE *ret_fopen = fopen(file,"r");
                    if(ret_fopen < 0)
                    {
                        perror("FILE NOT THERE");
                    }
                    int stdin;
                    int orig_stdin = dup2(0,stdin);
                    int ret_dup = dup2(fileno(ret_fopen),0);
                    if(ret_dup < 0)
                    {
                        perror("DUP2");
                    }
                    char *arg[2];
                    arg[1] = NULL;
                    arg[0] = &orig_command[0];
                    execvp(orig_command, arg);
                    int ret_close = close(fileno(ret_fopen));
                    int restore_stdin = dup2(stdin,0);
                    close(stdin);
                    fclose(ret_fopen);
                }
                else
                {
                    int status;
                    int ret_pid = waitpid(ret_fork,&status,WUNTRACED);
                    return;
                }
            }
        }
        else if(token[index_token] == '>' && token[index_token+1] == '>')
        {
            char *comman = strtok(token,c2);
            char *file_name;
            char file[100];
            file_name = strtok(NULL,c2);
            if(file_name == NULL)
            {
                perror("NO FILE");
                return;
                //change it if possible
            }
            else
            {
                remove_spaces(file_name,file);
                pid_t ret_fork = fork();
                if(ret_fork == 0)
                {
                    //FILE * ret_fopen = fopen(file,"a");
                    int ret_fopen = open(file,O_WRONLY | O_CREAT | O_APPEND ,0644);
                    if(ret_fopen < 0)
                    {
                        perror("FILE NOT THERE");
                    }
                    int stdin;
                    int orig_stdout = dup2(1,stdout);
                    //int ret_dup = dup2(fileno(ret_fopen),1);
                    int ret_dup = dup2(ret_fopen,1);
                    if(ret_dup < 0)
                    {
                        perror("DUP2");
                    }
                    arguments_pointer[0] = &orig_command[0];
                    execvp(orig_command, arguments_pointer);
                    int restore_stdin = dup2(stdout,1);
                    close(stdout);
                    close(ret_fopen);
                }
                else
                {
                    int status;
                    int ret_pid = waitpid(ret_fork,&status,WUNTRACED);
                    return;
                }
            }
        }
        else if(token[index_token] == '>')
        {
            char *command = strtok(token,&c3);
            char *file_name;
            char file[100];
            file_name = strtok(NULL,&c3);
            if(file_name == NULL)
            {
                perror("NO FILE");
                return;
                //change it if possible
            }
            else
            {
                remove_spaces(file_name,file);
                pid_t ret_fork = fork();
                if(ret_fork == 0)
                {
                    //FILE *ret_fopen = fopen(file,"w");
                    int ret_fopen = open(file,O_WRONLY | O_CREAT | O_TRUNC ,0644);
                    if(ret_fopen < 0)
                    {
                        perror("FILE NOT THERE");
                    }
                    int stdin;
                    int orig_stdout = dup2(1,stdout);
                    int ret_dup = dup2((ret_fopen),1);
                    //int ret_dup = dup2(fileno(ret_fopen),1);
                    if(ret_dup < 0)
                    {
                        perror("DUP2");
                    }
                    arguments_pointer[0] = &orig_command[0];
                    execvp(orig_command, arguments_pointer);
                    int restore_stdin = dup2(stdout,1);
                    close(stdout);
                    close(ret_fopen);
                }
                else
                {
                    int status;
                    int ret_pid = waitpid(ret_fork,&status,WUNTRACED);
                    return;
                }
            }
        }
        if(final_exec == 1)
            break;
    }while(!final_exec);
    return;
}
