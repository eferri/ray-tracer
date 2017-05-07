all: Main.cpp RayTracer.hpp ImageWriter.hpp Exceptions.hpp
	g++ -o tracer Main.cpp
clean:
	rm tracer out.bmp
