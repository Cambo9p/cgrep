CC = gcc


CFLAGS = -Wall 

SRC = src/main.c src/search.c src/hashmap.c
OBJ = $(SRC:.c=.o)

TARGET = cgrep

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ 

clean:
	rm -f $(OBJ) $(TARGET)
