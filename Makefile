bin/eshell: main.c
	mkdir -p bin
	gcc -Wall -Wextra main.c -o bin/eshell
