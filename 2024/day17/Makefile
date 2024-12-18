CXX:=g++

all: aoc ctrl

aoc: main.cc
	$(CXX) -O3 -o aoc $^

ctrl: controll.cc
	$(CXX) -o $@ $^

clean:
	rm -f aoc ctrl
