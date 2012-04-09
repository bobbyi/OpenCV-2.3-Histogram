all: hist

hist: histogram.cpp
	g++ -Wall -Wextra `pkg-config --cflags opencv` $< `pkg-config --libs opencv` -o $@

clean:
	rm -f hist
