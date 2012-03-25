default: diff

diff: run
	diff main.out an01

run: main.go
	./main.go < in01 > main.out

valgrind: main.go
	valgrind --leak-check=full ./main.go < in01

debug: main.go
	./main.go < in01

main.go: main.cpp
	g++ -Wall main.cpp -o main.go

clean:
	$(RM) *.out *.go

