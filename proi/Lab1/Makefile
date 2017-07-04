all: main.o Polynomial.o
        g++  main.o Polynomial.o -o main

polynomial.o: Polynomial.cpp
        g++ -c Polynomial.cpp

main.o: main.cpp
        g++ -c main.cpp

clean:
        rm -rf *.o main





