all:
	g++ -std=c++11 -Wall -o hw1 lorenz.cpp -lglut -lGLU -lGL -lm
clean:
	rm -f hw1