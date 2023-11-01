CC = g++

ones_ea: ones_ea.o population.o tournaments.o mutations.o crossovers.o 
	g++ -o ones_ea ones_ea.o population.o tournaments.o mutations.o crossovers.o


ea_tsp: ea_tsp.o population.o tournaments.o mutations.o crossovers.o tsp_functions.o 
	g++ -o ea_tsp ea_tsp.o population.o tournaments.o mutations.o crossovers.o tsp_functions.o
