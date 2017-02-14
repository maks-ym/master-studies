all: main.o polyminos.o
        g++  main.o polyminos.o -o main

polyminos.o: polyminos.cpp
        g++ -c polyminos.cpp

main.o: main.cpp
        g++ -c main.cpp

clean:
        rm -rf *.o main





