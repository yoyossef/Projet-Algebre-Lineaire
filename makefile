main : m_resol.o main.o
	gcc -g -o main main.o m_resol.o -Wall -Wextra -lm

m_resol.o : m_resol.c m_resol.h tp1.h
	gcc -g -o m_resol.o -c m_resol.c -Wall -Wextra

main.o : main.c m_resol.h tp1.h
	gcc -g -o main.o -c main.c -Wall -Wextra