exec=main.out
sources=$(wildcard src/*.c)
objects=$(sources:.c=.o)
flags=-g

$(exec):  $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $<  -o $@

install:
	make
	cp ./main.out /usr/local/bin/main

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o


