all:
	g++ -o bin/tracer src/Main.cpp
clean:
	rm -f bin/tracer bin/out.bmp