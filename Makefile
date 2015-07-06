CC=cc
target=adts_example
$(target):main.o adts.o
	$(CC) -o $(target) main.o adts.o

main.o:main.c adts.h
	$(CC) -c main.c
adts.o:adts.c adts.h
	$(CC) -c adts.c

.PHONY: clean
clean:
	rm $(target) main.o adts.o
