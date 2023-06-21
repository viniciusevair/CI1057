CFLAGS = -Wall -g
LDFLAGS = -lm
programName = myht

CC = gcc

# arquivos-objeto
objects = main.o libHASH.o libINSSORT.o

all: $(programName)

$(programName): $(objects)
	$(CC) -o $(programName) $(objects) $(LDFLAGS)

libHASH.o: libHASH.c
	$(CC) -c $(CFLAGS) libHASH.c

libINSSORT.o: libINSSORT.c
	$(CC) -c $(CFLAGS) libINSSORT.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects)

purge: clean
	rm -f $(programName)

