default: diff

diff: run
	diff main.out an01

run: main.go
	./main.go < in01 > main.out

valgrind: main.go
	valgrind --leak-check=full ./main.go < in01

debug: debmain.go
	./main.go < in01

main.go: main.cpp
	g++ -Wall main.cpp -o main.go

debmain.go: main.cpp
	g++ -g -Wall -Wextra -DDEBUG main.cpp -o main.go

clean:
	$(RM) *.out *.go

