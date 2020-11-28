#ifndef _variables_h_
#define _variables_h_

extern int i,j,k,z,p_flag,dir_name_flag,y;

extern int escape_space;
extern size_t size_dir;

extern char *argument_pointer[(int)10e3];		//l is used for this
extern char command[(int)10e4],arguments[(int)10e4],temp_char[(int)10e4],*token,arguments_echo[(int)10e4];
extern int ret_cmp,l;	//write check for cd ~
extern int background_flag;
extern int procs[100];
extern char *pname[100];
extern char *pargs[100];
extern int valid_proc[100];
#endif
