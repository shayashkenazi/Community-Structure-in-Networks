FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm
CC = gcc
EXEC = cluster
FILES = cluster.o spmat.o community.o divisionTwo.o group.o leadingEigen.o modularityGroups.o modularityMaximization.o readAndWrite.o matrixCalculation.o


all: $(FILES)
	$(CC) $(FILES) -o $(EXEC) $(LIBS)

clean:
	rm -f $(FILES) $(EXEC)

$(EXEC): $(FILES)
	$(CC) $(FILES) -o $@ $(LIBS)

cluster.o: cluster.c spmat.h community.h modularityGroups.h
	$(CC) $(FLAGS) -c $*.c

spmat.o: spmat.c spmat.h
	$(CC) $(FLAGS) -c $*.c

community.o: community.c community.h
	$(CC) $(FLAGS) -c $*.c

divisionTwo.o: divisionTwo.c divisionTwo.h community.h leadingEigen.h matrixCalculation.h
	$(CC) $(FLAGS) -c $*.c

group.o: group.c group.h community.h divisionTwo.h
	$(CC) $(FLAGS) -c $*.c

leadingEigen.o: leadingEigen.c leadingEigen.h community.h matrixCalculation.h
	$(CC) $(FLAGS) -c $*.c

modularityGroups.o: modularityGroups.c modularityGroups.h community.h divisionTwo.h modularityMaximization.h readAndWrite.h
	$(CC) $(FLAGS) -c $*.c

modularityMaximization.o: modularityMaximization.c modularityMaximization.h community.h
	$(CC) $(FLAGS) -c $*.c

readAndWrite.o: readAndWrite.c readAndWrite.h community.h
	$(CC) $(FLAGS) -c $*.c

matrixCalculation.o: matrixCalculation.c matrixCalculation.h
	$(CC) $(FLAGS) -c $*.c


