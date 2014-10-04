################################################################
# Variables
################################################################

# Compiler
CPP = gcc

# Compilation options
CFLAGS = -std=c11

# Optimizations compilation options
OPTIMIZATION = -lm -O2

# Directory of included files
INCLUDE = -I .

# Dependencies
OBJ =

################################################################
# Compilation OSX
################################################################

# OSX
osx: cleanosx progosx

# deletes the binary files
cleanosx:
	rm -rf progosx bin/osx/BPPC.o

# compilation
progosx: bin/osx/BPPC.o
	gcc bin/osx/BPPC.o -o progosx

bin/osx/BPPC.o: src/BPPC.c
	gcc -c -Wall src/BPPC.c -o bin/osx/BPPC.o

################################################################
# Compilation Linux
################################################################

# Linux
linux: cleanlinux proglinux

# deletes the binary files
cleanlinux:
	rm -rf proglinux bin/linux/BPPC.o

# compilation
proglinux: bin/linux/chaine.o bin/linux/BPPC.o
	$(CPP) $(CFLAGS) bin/linux/chaine.o bin/linux/BPPC.o -o proglinux $(OPTIMIZATION)

bin/linux/BPPC.o: src/BPPC.c
	$(CPP) $(CFLAGS) $(INCLUDE) -g -c src/BPPC.c -o bin/linux/BPPC.o $(OPTIMIZATION)

bin/linux/chaine.o: src/chaine.c
	$(CPP) $(CFLAGS) $(INCLUDE) -g -c src/chaine.c -o bin/linux/chaine.o $(OPTIMIZATION)
