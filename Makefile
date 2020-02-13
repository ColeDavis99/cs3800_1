CXX = g++
FLAGS = -W -Wall -pedantic-errors -g -std=c++17
LIBRARIES = -lpthread

.PHONY: default compile

default: compile

compile:
	${CXX} ${FLAGS} *.cpp ${LIBRARIES} -o program

run:
	clear && clear
	${CXX} ${FLAGS} *.cpp ${LIBRARIES} -o program
	./program sample_input.dat

run2:
	${CXX} ${FLAGS} *.cpp ${LIBRARIES} -o program
	./program sample_input.dat sample_input2.dat

clean:
	-@rm -rf *.o program core
