all: MCPwB

MCPwB: Main.o
	g++ -Wall -o MCPwB Main.o

Main.o: Main.cpp
	g++ -c Main.cpp

clean:
	rm *.o
