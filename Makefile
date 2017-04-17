OBJS = main.o ssa.o rng.o model.o output.o
CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

gillespie : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o gillespie.out

main.o : main.cpp model.h rng.h output.h ssa.h
	$(CC) $(CFLAGS) main.cpp

ssa.o : ssa.h ssa.cpp
	$(CC) $(CFLAGS) ssa.cpp

rng.o : rng.h rng.cpp
	$(CC) $(CFLAGS) rng.cpp

model.o : model.h model.cpp
	$(CC) $(CFLAGS) model.cpp

output.o : output.h output.cpp
	$(CC) $(CFLAGS) output.cpp

ssa.h : model.h rng.h output.h




clean :
	\rm *.o *~ gillespie.out

