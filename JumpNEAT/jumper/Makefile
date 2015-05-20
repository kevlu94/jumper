
CC=g++

CFLAGS=-w

LIBS=-I. -I/usr/local/include/ -I/usr/include /usr/lib/libGLEW.a -L/usr/local/lib -lode -lglfw3 -framework OpenGL -framework CoreFoundation -framework CoreGraphics -framework CoreVideo -framework IOKit -framework AppKit

all: learner jumper


learner: ../NEAT/*.cpp common/*.cpp camera.cpp interface.cpp model.cpp objects.cpp scene.cpp shapes.cpp
	$(CC) $(CFLAGS) $(LIBS) -I../NEAT/ ../NEAT/*.cpp common/*.cpp camera.cpp interface.cpp model.cpp objects.cpp scene.cpp shapes.cpp -o learner

jumper: common/*.cpp *.cpp
	$(CC) $(CFLAGS) $(LIBS) *.cpp common/*.cpp -o jumper

learn:
	 ./learner ../NEAT/test.ne output.txt

jump:
	./jumper output.txt

clean:
	rm learner jumper


