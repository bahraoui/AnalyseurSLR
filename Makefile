# PAS DE COPIER-COLLER (makefile n'accepte que les tabs)
CC=gcc
OPTS=-Wall
FOLDER=code
MAIN=$(FOLDER)/client.c
EXE=LRanalyzer
DEPS=$(FOLDER)/LRGrammar.h $(FOLDER)/read_file.h
PRECOMP=$(FOLDER)/LRGrammar.o $(FOLDER)/read_file.o

all: $(PRECOMP)
	clear
	$(CC) $(OPT) $(MAIN) $(PRECOMP) -o $(EXE)
	if [ -e $(EXE) ]; then clear; echo 'Compilation effectue\nlancement : ./$(EXE)'; fi

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

clean:
	rm $(FOLDER)/*.o
	rm $(EXE)