# Compiler settings
CC = gcc
CFLAGS = -Wall -pthread

# Target executable
TARGET = webserver

# Object files with correct paths
OBJS = src/webserver.o src/request.o

# Default target: Compile the web server
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

src/webserver.o: src/webserver.c src/request.h
	$(CC) $(CFLAGS) -c src/webserver.c -o src/webserver.o

src/request.o: src/request.c src/request.h
	$(CC) $(CFLAGS) -c src/request.c -o src/request.o

# Clean build files
clean:
	rm -f src/*.o $(TARGET)
