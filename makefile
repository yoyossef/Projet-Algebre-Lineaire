main : m_resol.o main.o
	gcc -g -o main main.o m_resol.o -Wall -Wextra

m_resol.o : m_resol.c
	gcc -o m_resol.o -c m_resol.c -Wall -Wextra

main.o : main.c tp1.h
	gcc -o main.o -c main.c -Wall -Wextra