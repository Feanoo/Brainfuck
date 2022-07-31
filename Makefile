CC=gcc
CFLAGS=-g -Wall -Werror
LD=
BINPATH=bin
SRCPATH=src

build: $(BINPATH) $(BINPATH)/brainfuck

run:
	make build
	./$(BINPATH)/brainfuck

$(BINPATH):
	mkdir $(BINPATH)

$(BINPATH)/brainfuck: $(BINPATH)/main.o
	$(CC) $(BINPATH)/*.o -o $(BINPATH)/brainfuck ${LD}

$(BINPATH)/main.o: $(SRCPATH)/main.* $(BINPATH)/stack.o
	$(CC) -c ${CFLAGS} $(SRCPATH)/main.c -o $(BINPATH)/main.o

$(BINPATH)/stack.o: $(SRCPATH)/stack.*
	$(CC) -c ${CFLAGS} $(SRCPATH)/stack.c -o $(BINPATH)/stack.o

clean:
	rm -r $(BINPATH)