#include "libraries.h"

void unenv(char arguments[])
{
	int stat=0;
	if(unsetenv(arguments))
	{
		perror("Error:");
	}
	return;
}