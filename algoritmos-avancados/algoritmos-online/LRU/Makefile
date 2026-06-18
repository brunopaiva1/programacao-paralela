CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17

TARGET = lru_experimento
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) saida_lru.txt
