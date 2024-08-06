# Nome do executável
EXEC = process_scheduler

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -std=c++11

# Diretório de origem
SRC_DIR = src

# Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Arquivos objeto (gerados a partir dos arquivos fonte)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

# Regra padrão para construir o executável
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Regra para compilar os arquivos objeto
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa os arquivos objeto e o executável
clean:
	rm -f $(SRC_DIR)/*.o $(EXEC)

# Regra para executar o programa
run: $(EXEC)
	./$(EXEC)

# Garante que 'make' sem argumentos compile e depois execute o programa
all: $(EXEC)
	@echo "Programa compilado com sucesso."
	@echo "Executando o programa..."
	./$(EXEC)