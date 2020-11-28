#ifndef _func_dec_h_
#define _func_dec_h

void clear_str(char str[],int len);

void clear_str_ptr(char *str[],int len);

void cd(char* ,char* ,char*);

void pwd(char*);

void echo(int,char*);

void pinfo(char*,int);

void ls(char*,char*,char*,int);

void env(char*);

void redir(char *,char *,char **,char,char,char *);

void unenv(char*);

void back(char**,int,char*,int,int*,int*,char**,char**);

void job(int* ,int* ,char**,char**,int*);

void kjob(char* ,int* ,int*,int*);


#endif
