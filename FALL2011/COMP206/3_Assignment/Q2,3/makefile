passweb : passweb.o cipher.o menu.o
	gcc -o passweb passweb.o cipher.o menu.o

passweb.o : passweb.c cipher.h menu.h
	gcc -c passweb.c

cipher.o : cipher.c cipher.h
	gcc -c cipher.c

menu.o : menu.c menu.h
	gcc -c menu.c

backup :
	cp *.c ../../backup

clean :
	rm -f *.o
