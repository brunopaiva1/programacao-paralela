CXX = mpicxx

CXXFLAGS = -O3 -Wall

TARGET = saida.exe

all: $(TARGET)

$(TARGET): Escalar.cpp
	$(CXX) $(CXXFLAGS) Escalar.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)