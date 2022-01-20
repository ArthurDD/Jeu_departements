
ecriture : jeu_dep.o main2.o
	gcc main2.o jeu_dep.o -o ecriture -lm

jeu_dep : jeu_dep.o main1.o
	gcc main1.o jeu_dep.o -o jeu_dep -lm

jeu_dep.o : jeu_dep.c jeu_dep.h
	gcc -c jeu_dep.c

main2.o : main2.c jeu_dep.h
	gcc -c main2.c

main1.o : main1.c jeu_dep.h
	gcc -c main1.c
