default: diff

diff: run
	diff main.out in01

run: main.go
	./main.go < in01 > main.out

main.go: main.cpp
	g++ -Wall main.cpp -o main.go

clean:
	$(RM) *.out *.go

