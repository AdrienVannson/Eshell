bin/eshell: main.c
	mkdir -p bin
	gcc -g -Wall -Wextra main.c processes.c -o bin/eshell
