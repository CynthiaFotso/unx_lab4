CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = lab4
SRC = lab4.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) Screen.log
