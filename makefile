CC = g++

ones_ea: ones_ea.o population.o tournaments.o mutations.o crossovers.o 
	g++ -o ones_ea ones_ea.o population.o tournaments.o mutations.o crossovers.o


tsp_ea: tsp_ea.o population.o tournaments.o mutations.o crossovers.o tsp_functions.o 
	g++ -o tsp_ea tsp_ea.o population.o tournaments.o mutations.o crossovers.o tsp_functions.o
