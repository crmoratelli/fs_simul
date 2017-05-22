CFLAGS = -Wall
LIBS=

SRC=$(wildcard *.c)

simulfs: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
	
clean:
	rm -f *.o
	rm -f simulfs
	rm -f simul.fs
	rm -f log.dat
	rm -f sector_map.png