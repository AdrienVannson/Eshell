all: bin/eshell bin/args bin/hello bin/count bin/background bin/count10

clean:
		rm -r bin

bin:
	  mkdir -p bin

bin/eshell: src/main.c src/processes.c src/processes.h src/env.c src/env.h | bin
		gcc -Wall -Wextra src/main.c src/processes.c src/env.c -o bin/eshell

bin/args: tests/args.c | bin
		gcc -Wall -Wextra tests/args.c -o bin/args

bin/hello: tests/hello.c | bin
		gcc -Wall -Wextra tests/hello.c -o bin/hello

bin/background: tests/background.c | bin
		gcc -Wall -Wextra tests/background.c -o bin/background

bin/count: tests/count.c | bin
		gcc -Wall -Wextra tests/count.c -o bin/count

bin/count10: tests/count10.c | bin
		gcc -Wall -Wextra tests/count10.c -o bin/count10

.PHONY: all clean
