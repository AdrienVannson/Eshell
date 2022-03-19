all: bin/eshell bin/hello bin/count

clean:
		rm -r bin

bin:
	  mkdir -p bin

bin/eshell: main.c processes.c processes.h env.c env.h | bin
		gcc -g -Wall -Wextra main.c processes.c env.c -o bin/eshell

bin/hello: tests/hello.c | bin
		gcc -g -Wall -Wextra tests/hello.c -o bin/hello

bin/count: tests/count.c | bin
		gcc -g -Wall -Wextra tests/count.c -o bin/count

.PHONY: all clean
