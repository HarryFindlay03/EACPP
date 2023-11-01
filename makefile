CC = g++

ones_ea: ones_ea.o population.o tournaments.o mutations.o crossovers.o 
	g++ -o ones_ea ones_ea.o population.o tournaments.o mutations.o crossovers.o
