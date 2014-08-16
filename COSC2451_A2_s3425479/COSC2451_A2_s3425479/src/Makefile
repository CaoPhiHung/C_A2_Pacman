CC = clang
CFLAGS = -Wall -g 
SOURCES = square.c map.c pacman.c pg.c move.c sll.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = square.h map.h pg.h move.h sll.h

pacman: $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) -o pacman $(OBJS) -lncurses

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm *.o cl
	
.PHONY: cleanall
cleanall:
	rm *.o *~ pacman
