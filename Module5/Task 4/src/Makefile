SRC_FILES=main.c students.c loader.c cli.c

all: main

main: $(SRC_FILES)
	gcc -pedantic -Wall -Wextra -std=c99 -g -o $@ $(SRC_FILES)

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
