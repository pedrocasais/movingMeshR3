# g++ main.cpp shader.cpp objloader.cpp controls.cpp -o main -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -ldl

CC = g++
LIBS = -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -ldl
OBS = main.o shader.o objloader.o controls.o

all: main

main.o : main.cpp
	$(CC) -c main.cpp	
shader.o : shader.cpp
	$(CC) -c shader.cpp
objloader.o : objloader.cpp
	$(CC) -c objloader.cpp
controls.o : controls.cpp
	$(CC) -c controls.cpp
main : $(OBS)
	$(CC)  -o main  $(OBS) $(LIBS)

clean:
	rm -f *.o main