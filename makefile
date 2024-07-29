CC = gcc


CFLAGS = -Wall -Werror

SRC = src/main.c src/searchfile.c src/hashmap.c
OBJ = $(SRC:.c=.o)

TARGET = cgrep

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ 

clean:
	rm -f $(OBJ) $(TARGET)
	rm -f *.txt
