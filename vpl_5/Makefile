CC = g++
CFLAGS = -Iinclude -std=c++11
SRC = src/main.cpp src/set.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = bin/pa5.out

# Regra padrão
all: bin $(EXEC)

# Cria a pasta bin se não existir
bin:
	mkdir -p bin

# Compila o executável
$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ)

# Compila arquivos objeto
src/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Remove arquivos gerados e a pasta bin
clean:
	rm -f $(OBJ) $(EXEC)
	rm -rf bin