CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

TARGET = minmax
SRC = minmax.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Compilando $(SRC) com otimização de alto desempenho (-O3)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "Build concluído com sucesso!"

clean:
	@echo "Limpando arquivos binários..."
	rm -f $(TARGET)