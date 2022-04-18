output: main.o DE1SoCfpga.o Box.o Pixel.o Polygon.o Bounds.o
	g++ main.o DE1SoCfpga.o Box.o Pixel.o Polygon.o Bounds.o  -o output

main.o : main.cpp
	g++ -c main.cpp

DE1SoCfpga.o: DE1SoCfpga.cpp DE1SoCfpga.h
	g++ -c DE1SoCfpga.cpp
 
Box.o: Box.cpp Box.h
	g++ -c Box.cpp

Pixel.o: Pixel.cpp Pixel.h
	g++ -c Pixel.cpp
 
Polygon.o: Polygon.cpp Polygon.h
	g++ -c Polygon.cpp

Bounds.o: Bounds.cpp Bounds.h
	g++ -c Bounds.cpp

clean:
	rm *.o output