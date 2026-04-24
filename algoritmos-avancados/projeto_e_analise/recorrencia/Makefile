CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

TARGET = bench_busca
SRC = busca_binaria.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.csv *.png