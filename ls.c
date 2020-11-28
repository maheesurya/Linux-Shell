#include "libraries.h"

void ls(char current_dir_name[],char arguments_echo[],char arguments[],int k)
{
	int looper=0,l_flag=0,a_flag=0,err_flag=0,simple=0;
	char args[1000000],ind_args=0,val_args=0;
	for(ind_args=0;ind_args<k;ind_args++)
	{
		if(arguments_echo[ind_args] == '-')
		{	
			args[val_args] = arguments_echo[ind_args];
			if(arguments_echo[ind_args+1] == ' ')
			{	
				err_flag =1;
				break;
			}
			if(arguments_echo[ind_args+1] == '\t')
			{	
				err_flag = 1;
				break;
			}
			if(arguments_echo[ind_args+1] == '\n')
			{	
				err_flag =1;
				break;
			}
		}
	}
	for(looper=0;looper<k;looper++)
	{
		if(arguments_echo[looper] == '-'){
			while(looper<k)
			{
				looper++;
				if(arguments_echo[looper] == 'a')
					a_flag=1;
				else if(arguments_echo[looper] == 'l')
					l_flag=1;
				else if(arguments_echo[looper] == 0 || arguments_echo[looper] == ' ' || arguments_echo[looper] == '\t')
					break;
				else
				{
					err_flag = 1;
					break;
				}
			}
		}
		else if(looper>0 && arguments_echo[looper-1] =='-' && (arguments_echo[looper] == ' ' || arguments_echo[looper] == '\n' || arguments_echo[looper] == '\t' || arguments_echo[looper] == 0))
		{
			err_flag = 1;
			break;
		}
		else if(arguments_echo[looper] != '-' && arguments_echo[looper] != ' ' && arguments_echo[looper] != '\t' || arguments_echo[looper] != '\n')
		{
			simple=1;
		}
	}
	DIR *dir;
	DIR *test_dir;
	struct dirent *godir,*total;
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	int char_val = w.ws_col,flag=0;
	dir = opendir(current_dir_name);
	test_dir = opendir(current_dir_name);
	godir = readdir(dir);
	total = readdir(test_dir);
	if(err_flag == 1){
		perror("Unknown flag specified due to:");
	}
	else if(simple==0)
	{
		if(l_flag!=1 && a_flag!=1)
		{
			while(godir != NULL)
			{
				struct stat file;
				stat(godir->d_name,&file);
				if(godir->d_name[0] != '.')
				{
					if((file.st_mode & S_IFDIR))	
						printf("%s%s%s%s%s%s%s\t",bold,blue,godir->d_name,blue,bold,reset,reset);
					else if((file.st_mode & S_IXUSR) || (file.st_mode & S_IXGRP) || (file.st_mode & S_IXOTH))
						printf("%s%s%s%s%s%s%s\t",bold,green,godir->d_name,green,bold,reset,reset);
					else
						printf("%s\t",godir->d_name);
				}
				godir = readdir(dir);
			}
			puts("");
		}
		else if(a_flag==1 && l_flag!=1){
			while(godir!=NULL)
			{
				struct stat file;
				stat(godir->d_name,&file);
				if(file.st_mode & S_IFDIR)	
					printf("%s%s%s%s%s%s%s\t",bold,blue,godir->d_name,blue,bold,reset,reset);
				else if((file.st_mode & S_IXUSR) || (file.st_mode & S_IXGRP) || (file.st_mode & S_IXOTH))
					printf("%s%s%s%s%s%s%s\t",bold,green,godir->d_name,green,bold,reset,reset);
				else
					printf("%s\t",godir->d_name);
				godir = readdir(dir);
			}
			puts("");
		}
		else if(a_flag!=1 && l_flag==1)
		{
			long int blocks=0;
			while(total!=NULL){
				struct stat file,filel;
				char cur_dir_name[100000]={};
				stat(total->d_name,&file);
				if(total->d_name[0]!='.')
				{
					int last_elem=0;
					strcpy(cur_dir_name,current_dir_name);
					while(cur_dir_name[last_elem]!=0)
						last_elem++;
					cur_dir_name[last_elem]='/';
					strcat(cur_dir_name,total->d_name);
					blocks+=file.st_blocks;
				}
				total = readdir(test_dir);
			}
			printf("total %ld\n",blocks/2 );
			while(godir!=NULL)
			{
				struct stat file,filel;
				stat(godir->d_name,&file);
				lstat(godir->d_name,&filel);
				if(godir->d_name[0] != '.')
				{
					if(file.st_mode & S_IFDIR)
						printf("d");
					else if(S_ISLNK(filel.st_mode))
						printf("l");
					else if(S_ISREG(file.st_mode))
						printf("-");
					(file.st_mode & S_IRUSR) ? (printf("r")) : (printf("-"));
					(file.st_mode & S_IWUSR) ? (printf("w")) : (printf("-"));
					(file.st_mode & S_IXUSR) ? (printf("x")) : (printf("-"));
					(file.st_mode & S_IRGRP) ? (printf("r")) : (printf("-"));
					(file.st_mode & S_IWGRP) ? (printf("w")) : (printf("-"));
					(file.st_mode & S_IXGRP) ? (printf("x")) : (printf("-"));
					(file.st_mode & S_IROTH) ? (printf("r")) : (printf("-"));
					(file.st_mode & S_IWOTH) ? (printf("w")) : (printf("-"));
					(file.st_mode & S_IXOTH) ? (printf("x")) : (printf("-"));
					printf(" ");
					printf("%lu ",file.st_nlink);
					struct passwd *usr = getpwuid(file.st_uid);
					struct group *grp = getgrgid(file.st_gid);
					printf("%s ",usr->pw_name);
					printf("%s ",grp->gr_name);
					printf("%lu ",file.st_size);
					char *a = ctime(&file.st_mtime);
					int a_len=strlen(a),a_loop=0;
					for(a_loop = 4;a_loop<16;a_loop++)
						printf("%c",a[a_loop]);
					printf(" ");
					if(file.st_mode & S_IFDIR)	
						printf("%s%s%s%s%s%s%s\t",bold,blue,godir->d_name,blue,bold,reset,reset);
					else if((file.st_mode & S_IXUSR) || (file.st_mode & S_IXGRP) || (file.st_mode & S_IXOTH))
						printf("%s%s%s%s%s%s%s\t",bold,green,godir->d_name,green,bold,reset,reset);
					else
						printf("%s\t",godir->d_name);
					printf("\n");
				}
				godir = readdir(dir);
			}
		}	
		else if(a_flag==1 && l_flag==1)
		{
			long int blocks=0;
			while(total!=NULL)
			{
				struct stat file,filel;
				char cur_dir_name[100000]={};
				stat(total->d_name,&file);
				int last_elem=0;
				strcpy(cur_dir_name,current_dir_name);
				while(cur_dir_name[last_elem]!=0)
					last_elem++;
				cur_dir_name[last_elem]='/';
				strcat(cur_dir_name,total->d_name);
				blocks+=file.st_blocks;
				total = readdir(test_dir);
			}
			printf("total %ld\n",blocks/2 );
			while(godir!=NULL)
			{
				struct stat file,filel;
				stat(godir->d_name,&file);
				lstat(godir->d_name,&filel);
				if(file.st_mode & S_IFDIR)
					printf("d");
				else if(S_ISLNK(filel.st_mode))
					printf("l");
				else if(S_ISREG(file.st_mode))
					printf("-");
				(file.st_mode & S_IRUSR) ? (printf("r")) : (printf("-"));
				(file.st_mode & S_IWUSR) ? (printf("w")) : (printf("-"));
				(file.st_mode & S_IXUSR) ? (printf("x")) : (printf("-"));
				(file.st_mode & S_IRGRP) ? (printf("r")) : (printf("-"));
				(file.st_mode & S_IWGRP) ? (printf("w")) : (printf("-"));
				(file.st_mode & S_IXGRP) ? (printf("x")) : (printf("-"));
				(file.st_mode & S_IROTH) ? (printf("r")) : (printf("-"));
				(file.st_mode & S_IWOTH) ? (printf("w")) : (printf("-"));
				(file.st_mode & S_IXOTH) ? (printf("x")) : (printf("-"));
				printf(" ");
				printf("%lu ",file.st_nlink);
				struct passwd *usr = getpwuid(file.st_uid);
				struct group *grp = getgrgid(file.st_gid);
				printf("%s ",usr->pw_name);
				printf("%s ",grp->gr_name);
				printf("%lu ",file.st_size);
				char *a = ctime(&file.st_mtime);
				int a_len=strlen(a),a_loop=0;
				for(a_loop = 4;a_loop<16;a_loop++)
					printf("%c",a[a_loop]);
				printf(" ");
				if(file.st_mode & S_IFDIR)	
					printf("%s%s%s%s%s%s%s\t",bold,blue,godir->d_name,blue,bold,reset,reset);
				else if((file.st_mode & S_IXUSR) || (file.st_mode & S_IXGRP) || (file.st_mode & S_IXOTH))
					printf("%s%s%s%s%s%s%s\t",bold,green,godir->d_name,green,bold,reset,reset);
				else
					printf("%s\t",godir->d_name);
				godir = readdir(dir);
				if(godir!=NULL)
					printf("\n");
			}
			printf("\n");
		}	
	}
	closedir(dir);
}
