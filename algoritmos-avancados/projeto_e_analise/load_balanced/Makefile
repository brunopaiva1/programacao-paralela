CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

TARGET = load_balanced
SRC = load_balanced.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	@echo "Compilando $(SRC) com otimização -O3..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "Build concluído!"

clean:
	@echo "Limpando binários..."
	rm -f $(TARGET)