a.out: main.o ls.o pwd_echo_cd.o pinfo.o background.o env.o unenv.o job.o redir.o kjob.o fg.o
	gcc -o a.out main.o ls.o pwd_echo_cd.o pinfo.o background.o env.o unenv.o job.o redir.o kjob.o fg.o

main.o : main.c libraries.h variables.h colored_text.h
	gcc -c main.c
ls.o : ls.c libraries.h variables.h colored_text.h
	gcc -c ls.c
pwd_echo_cd.o : pwd_echo_cd.c libraries.h variables.h colored_text.h
	gcc -c pwd_echo_cd.c
pinfo.o : pinfo.c libraries.h variables.h colored_text.h
	gcc -c pinfo.c
background.o : background.c libraries.h variables.h colored_text.h
	gcc -c background.c
env.o : env.c libraries.h variables.h colored_text.h
	gcc -c env.c
unenv.o : unenv.c libraries.h variables.h colored_text.h
	gcc -c unenv.c
job.o : job.c libraries.h variables.h colored_text.h
	gcc -c job.c
redir.o : redir.c libraries.h variables.h colored_text.h
	gcc -c redir.c
kjob.o : kjob.c libraries.h variables.h colored_text.h
	gcc -c kjob.c
fg.o : fg.c libraries.h variables.h colored_text.h
	gcc -c fg.c

clean :
	rm -rf *.o
