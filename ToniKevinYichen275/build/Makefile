
CC=g++

CFLAGS=-w

LIBS=-I../src/ -I/usr/local/include/ -I/usr/include /usr/lib/libGLEW.a -L/usr/local/lib -lode -lglfw3 -framework OpenGL -framework CoreFoundation -framework CoreGraphics -framework CoreVideo -framework IOKit -framework AppKit

all: learner jumper


learner: ../src/NEAT/*.cpp ../src/common/*.cpp ../src/camera.cpp ../src/interface.cpp ../src/model.cpp ../src/objects.cpp ../src/scene.cpp ../src/shapes.cpp
	$(CC) $(CFLAGS) $(LIBS) -I../src/NEAT/ ../src/NEAT/*.cpp ../src/common/*.cpp ../src/camera.cpp ../src/interface.cpp ../src/model.cpp ../src/objects.cpp ../src/scene.cpp ../src/shapes.cpp -o learner

jumper: ../src/common/*.cpp ../src/*.cpp
	$(CC) $(CFLAGS) $(LIBS) ../src/*.cpp ../src/common/*.cpp -o jumper

learn:
	 echo "1" | ./learner-demo ../src/NEAT/test.ne output.txt

jump:
	./jumper-demo output.txt

sample1:
	./jumper-demo stand.txt

sample2:
	./jumper-demo quickjump.txt

sample3:
	./jumper-demo jumpland.txt

clean:
	rm learner jumper


