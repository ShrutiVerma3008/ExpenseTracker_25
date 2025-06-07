# Makefile

CC = gcc
CFLAGS = -Wall
SRC = src/main.c src/personal.c src/group.c
OUT = cashflow

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
