SOURCES:=$(wildcard *.cc) $(wildcard *.cpp)
CC=g++
FLAGS = -std=c++11 -I ../../inc
main:${SOURCES}
	$(CC) $^ -o $@ $(FLAGS)
.PHONY : clean
clean:
	-rm main 
