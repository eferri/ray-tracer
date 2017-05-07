all: src/Main.cpp include/RayTracer.hpp include/ImageWriter.hpp include/Exceptions.hpp
	g++ -o bin/tracer src/Main.cpp
clean:
	rm -f bin/tracer bin/out.bmp
