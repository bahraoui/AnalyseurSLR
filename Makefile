# PAS DE COPIER-COLLER (makefile n'accepte que les tabs)
CC=gcc
OPTS=-Wall
FOLDER=code
MAIN=$(FOLDER)/client.c
EXE=LRanalyzer
DEPS=$(FOLDER)/LRGrammar.h $(FOLDER)/read_file.h
PRECOMP=$(FOLDER)/LRGrammar.o $(FOLDER)/read_file.o
FILE_TEST=assets/toto
WORD_TEST="ab"

all: $(PRECOMP)
	@$(CC) $(OPTS) $(MAIN) $(PRECOMP) -o $(EXE)
	@if [ -e $(EXE) ]; then echo 'Compilation effectue\nlancement : ./$(EXE)'; fi

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $<

test: $(PRECOMP)
	@if [ -e $(EXE) ]; then rm ./$(EXE); fi
	@$(CC) $(OPT) $(MAIN) $(PRECOMP) -o $(EXE)
	./$(EXE) $(FILE_TEST) $(WORD_TEST)

clean:
	rm $(FOLDER)/*.o
	rm $(EXE)