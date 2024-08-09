CC = gcc


CFLAGS = -Wall -Werror -lpthread 

SRC = src/main.c src/searchfile.c src/searchdir.c src/hashmap.c src/queue.c src/formatted_ans.c src/args.c
#SRC = src/*.c
OBJ = $(SRC:.c=.o)

TARGET = cgrep

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ 

clean:
	rm -f $(OBJ) $(TARGET)
	rm -f *.txt

test:
	gcc -std=c99 -g -o test src/main.o src/searchfile.o src/searchdir.o src/hashmap.o
