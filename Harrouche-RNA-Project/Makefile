# Makefile

# Dépendances et cibles pour la compilation
CC = gcc
CFLAGS = -Wall -pthread -lm
SRC = src
OBJ = obj
BIN = bin
INCLUDE = include

# Liste des fichiers objets
OBJS = $(OBJ)/main.o $(OBJ)/rna.o $(OBJ)/logic_gates.o $(OBJ)/utils.o

# Cible par défaut
all: $(BIN)/main

# Compilation de l'exécutable
$(BIN)/main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# Compilation des fichiers objets
$(OBJ)/main.o: $(SRC)/main.c $(INCLUDE)/rna.h $(INCLUDE)/utils.h
	$(CC) -c $(SRC)/main.c -o $@ $(CFLAGS)

$(OBJ)/rna.o: $(SRC)/rna.c $(INCLUDE)/rna.h
	$(CC) -c $(SRC)/rna.c -o $@ $(CFLAGS)

$(OBJ)/logic_gates.o: $(SRC)/logic_gates.c $(INCLUDE)/rna.h $(INCLUDE)/utils.h
	$(CC) -c $(SRC)/logic_gates.c -o $@ $(CFLAGS)

$(OBJ)/utils.o: $(SRC)/utils.c $(INCLUDE)/utils.h
	$(CC) -c $(SRC)/utils.c -o $@ $(CFLAGS)

# Cible pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ)/*.o $(BIN)/main

# Cible pour exécuter le programme
run: $(BIN)/main
	./$(BIN)/main
