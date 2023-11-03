



CC = gcc

CFLAGS = `pkg-config --cflags gtk+-3.0` -lX11

LIBS = `pkg-config --libs gtk+-3.0`

# File names

SRC = sglogout.c sglogout-cfg.c

OBJ = $(SRC:.c=.o)

EXE = sglogout sglogout-cfg

# Build executable files

all: $(EXE)

sglogout: sglogout.o

	$(CC) $(CFLAGS) -o $@ $< $(LIBS) -lm

sglogout-cfg: sglogout-cfg.o

	$(CC) $(CFLAGS) -o $@ $< $(LIBS) -lm

# Debug step

debug:

	$(CC) $(CFLAGS) -g $(SRC) -o debug $(LIBS)

# Test step

test:

	./sglogout

	./sglogout-cfg

# Clean object files and executables

clean:

	rm -f $(OBJ) $(EXE) debug
