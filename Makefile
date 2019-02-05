run: main
	./main < in.txt

clean:
	rm -f *.o main out.txt opt.txt

main: main.cc
	g++ -o main -O2 -std=c++11 -pthread main.cc

.PHONY: run clean
