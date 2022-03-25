all: bin/eshell bin/hello bin/count bin/background bin/count10

clean:
		rm -r bin

bin:
	  mkdir -p bin

bin/eshell: main.c processes.c processes.h env.c env.h | bin
		gcc -g -Wall -Wextra main.c processes.c env.c -o bin/eshell

bin/hello: tests/hello.c | bin
		gcc -g -Wall -Wextra tests/hello.c -o bin/hello

bin/background: tests/background.c | bin
		gcc -g -Wall -Wextra tests/background.c -o bin/background

bin/count: tests/count.c | bin
		gcc -g -Wall -Wextra tests/count.c -o bin/count

bin/count10: tests/count10.c | bin
		gcc -g -Wall -Wextra tests/count10.c -o bin/count10

.PHONY: all clean
