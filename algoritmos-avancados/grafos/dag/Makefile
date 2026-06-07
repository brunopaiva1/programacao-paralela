CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17
TARGET = artigo_dag
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)