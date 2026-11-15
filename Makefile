CC     = gcc
CFLAGS = -Wall -Wextra

SRC  = $(wildcard *.c)
BINS = $(SRC:.c=)

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BINS)
