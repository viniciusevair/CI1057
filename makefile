# Makefile generico

# flags de compilacao
CFLAGS = -Wall -g 

# nome do executavel/main
programName = myavl

# compilador
CC = gcc

# arquivos-objeto
objects = $(programName).o libAVL.o

$(programName): $(objects)
	$(CC) -o $(programName) $(objects) $(LDFLAGS)

libAVL.o: libAVL.c
	$(CC) -c $(CFLAGS) libAVL.c

$(programName).o: $(programName).c
	$(CC) -c $(CFLAGS) $(programName).c

clean:
	rm -f $(objects)

purge: clean
	rm -f $(programName)

run: $(programName)
	./$(programName) < teste4.in > saida4
	diff saida4 teste4.out
