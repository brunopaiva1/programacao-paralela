CXX = g++

CXXFLAGS = -O3 -Wall -fopenmp

TARGET = trapezio

SRC = trap.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)