CC = gcc
CFLAGS = -Wall -g

BINS=hello

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $?

clean:
	$(RM) $(BINS)
	$(RM) -r *.dSYM
	clear
