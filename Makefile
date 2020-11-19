OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -g -O2 -Wall -pedantic -Wextra -Wwrite-strings
EXE 	 := trab3
PROJETO  := main

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
main: $(OBJ)/utils.o $(OBJ)/$(PROJETO).o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/utils.o: $(SRC)/utils.c $(INC)/utils.h
	gcc -c $(CFLAGS) "$(SRC)/utils.c" -o "$(OBJ)/utils.o"

$(OBJ)/$(PROJETO).o: $(PROJETO).c
	gcc -c $(CFLAGS) $(PROJETO).c -o "$(OBJ)/$(PROJETO).o"

# Roda o programa com entrada 1
# run_1:
# 	./$(EXE) M entradas/1.txt

# Roda o programa com entrada 2
# run_2:
# 	./$(EXE) M entradas/2.txt

# Roda o programa com valgrind e flags úteis (entrada 3)
# val:
# 	valgrind --leak-check=full -v --track-origins=yes \
# 	--show-leak-kinds=all ./$(EXE)

# Roda o programa com valgrind sem flags (entrada 3)
# valzin:
# 	valgrind ./$(EXE)

# Roda o programa com valgrind e salva resultados num .txt (entrada 3)
# valtxt:
# 	valgrind --leak-check=full -v --show-leak-kinds=all --track-origins=yes --verbose --log-file="valgrind-out.txt" ./$(EXE)

# Limpa objetos e o executável do programa
clean:
	-rm $(OBJ)/*.o
	-rm $(EXE)
