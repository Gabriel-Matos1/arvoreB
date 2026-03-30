CC = gcc-14
CFLAGS = -Wall -Wextra -g3 -std=c23

TARGET = prova1_GRR
SRC = main.c arvoreB.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) main