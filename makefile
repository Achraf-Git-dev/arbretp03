CC = gcc
OPT = -Wextra -Wall -g
OBJ = main.o pile.o arbre.o

prog : $(OBJ)
	$(CC) $(OBJ) $(OPT) -o prog
main.o : main.c pile.o pile.h arbre.o arbre.h chaine_caractere.o chaine_caractere.h
	$(CC) $(OPT) -c main.c
pile.o : pile.c pile.h
	$(CC) $(OPT) -c pile.c
arbre.o : arbre.c arbre.h
	$(CC) $(OPT) -c arbre.c
chaine_caractere.o : chaine_caractere.c chaine_caractere.h
	$(CC) $(OPT) -c chaine_caractere.c

clean :
	rm $(OBJ)