CC = gcc
CFLAGS = -Wall -g

BINS=hello

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -lgpiod -o $@ $?

clean:
	$(RM) $(BINS)
	$(RM) -r *.dSYM
	clear
