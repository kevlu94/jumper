
cd jumper

g++ -o run *.cpp common/*.cpp ../NEAT/*.cpp -I. -I../NEAT/ -I/usr/local/include/ -I/usr/include /usr/lib/libGLEW.a -L/usr/local/lib -lode -lglfw3 -framework OpenGL -framework CoreFoundation -framework CoreGraphics -framework CoreVideo -framework IOKit -framework AppKit

./run ../NEAT.1.2.1/test.ne

press 1
