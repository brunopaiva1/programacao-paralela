CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

TARGET = bench_radix
SRC = bench_radix.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Compilando $(SRC) com otimização -O3..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "Build concluído!"

clean:
	@echo "Limpando arquivos antigos..."
	rm -f $(TARGET) *.csv *.png