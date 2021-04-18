CC=g++
LFLAGS=-ansi -pedantic -Wall -Wextra -O2

bad-apple: objects/main.o objects/lodepng.o objects/imageconverting.o
	$(CC) objects/main.o objects/lodepng.o objects/imageconverting.o $(LFLAGS) -o bad-apple

objects/main.o: src/main.cpp objectsFolder
	$(CC) -c src/main.cpp -o objects/main.o

objects/lodepng.o: src/lodepng.cpp objectsFolder
	$(CC) -c src/lodepng.cpp -o objects/lodepng.o

objects/imageconverting.o: src/imageconverting.cpp objectsFolder
	$(CC) -c src/imageconverting.cpp -o objects/imageconverting.o

.PHONY: objectsFolder
objectsFolder:
	mkdir -p objects

.PHONY: clean
clean:
	rm -f objects/*.o bad-apple
