#include "libraries.h"

void nightwatch(char arguments_echo[],char arguments[])
{
	int check_watch=0;
	if(arguments_echo[check_watch] == '-' && arguments_echo[check_watch+1] == 'n')
	{
		char s[6];
		int zzind=0,zz;
		for(zz=check_watch+3;;zz++){
			if(arguments[zz]==' ')
				break;
			else
				s[zzind++]=arguments[zz];
		}
		int time=atoi(s),timer=0;
		while(1){
			struct /*poll*/ mypoll = { STDIN_FILENO,POLLIN|POLLPRI};
			char string[10];	
		}
	}	
}
