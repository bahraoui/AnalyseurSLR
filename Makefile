# PAS DE COPIER-COLLER (makefile n'accepte que les tabs)
CC=gcc
OPTS=-Wall -o1
FOLDER=code
MAIN=$(FOLDER)/client.c
EXE=LRanalyzer
DEPS=$(FOLDER)/LRGrammar.h $(FOLDER)/read_file.h $(FOLDER)/arbre.h $(FOLDER)/analyseurLR.h
PRECOMP=$(DEPS:.h=.o)
FILE_TEST=assets/toto
WORD_TEST="aabb"

all: $(PRECOMP)
	@if [ -e $(EXE) ]; then rm ./$(EXE); fi
	@$(CC) $(OPTS) $(MAIN) $(PRECOMP)  -o $(EXE)
	@if [ -e $(EXE) ]; then echo 'Compilation effectue\nlancement : ./$(EXE) [fichier] [mot]'; fi

%.o: %.c $(DEPS)
	@$(CC) -c -o $@ $<

clean:
	@if [ `ls -1 $(PRECOMP) 2>/dev/null | wc -l` -gt 0 ]; then rm $(PRECOMP); echo "everything is clean."; else echo "nothing to clean."; fi
	@if [ -e $(EXE) ]; then rm ./$(EXE); fi

 # regle make pour tester avec un exemple simple
test: $(PRECOMP)
	@$(CC) $(OPTS) $(MAIN) $(PRECOMP) -o $(EXE)
	./$(EXE) $(FILE_TEST) $(WORD_TEST)

 # regle make pour tester avec valgrind
val: $(PRECOMP)
	@if [ -e $(EXE) ]; then rm ./$(EXE); fi
	@$(CC) $(OPT) $(MAIN) $(PRECOMP) -o $(EXE)
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(EXE) $(FILE_TEST) $(WORD_TEST)
	