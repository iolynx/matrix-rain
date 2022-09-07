all: compile link

test: compile link run

compile:
	g++ -I src/include -c main.cpp

link:
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	del *.o

run:
	main.exe