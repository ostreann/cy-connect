all: exec

main.o : main.c Def.h
	gcc -c main.c -o main.o
	


IHM.o :	IHM.c  Def.h
	gcc -c IHM.c -o IHM.o

Calcul.o :Calcul.c Def.h
	gcc -c Calcul.c -o Calcul.o


Sauvegarde.o :Sauvegarde.c Def.h
	gcc -c Sauvegarde.c -o Sauvegarde.o


exec :main.o IHM.o Calcul.o  Sauvegarde.o
	gcc *.o -o exec

 clean : 
	rm *.o
	rm exec
