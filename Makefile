all:
	g++ -c src/comp.cpp -std=c++14
	g++ -c src/define.cpp -std=c++14
	g++ -c src/run.cpp -std=c++14
	g++ -c src/proto.cpp -std=c++14
	g++ -c src/editcode.cpp -std=c++14
	g++ comp.o define.o -o bin/proc
	g++ run.o define.o -o bin/prun
	g++ proto.o define.o -o bin/proto
	g++ editcode.o define.o -o bin/comp+
	rm *.o
