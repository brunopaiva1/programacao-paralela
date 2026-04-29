CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

TARGET = bench_quicksort
SRC = bench_quicksort.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.csv *.png