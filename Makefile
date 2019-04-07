manager : menu.o user.o main.o
	gcc -o manager menu.o user.o main.o
menu.o : menu.c
	gcc -c -o menu.o menu.c
user.o : user.c
	gcc -c -o user.o user.c
main.o : main.c
	gcc -c -o main.o main.c
clean :
	rm *.o manager
