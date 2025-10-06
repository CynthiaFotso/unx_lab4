CC = g++
CFLAGS = -Wall -std=c++11
TARGET = lab4
SRC = lab4.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) Screen.log
