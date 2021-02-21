CC=gcc
OBJ= main.o scissors.o

scissors: $(OBJ)
	$(CC) -o $@ $^

$(OBJ): scissors.h

.PHONY: clean

clean:
	rm *.o scissors
