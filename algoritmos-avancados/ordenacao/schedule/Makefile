CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17

TARGET = schedule
SRC = schedule.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)