CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

TARGET = bench_strassen
SRC = strassen.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Compilando $(SRC) com otimização máxima..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "Build concluído! Executável: $(TARGET)"

clean:
	@echo "Limpando binários e arquivos CSV..."
	rm -f $(TARGET) *.csv