compile:

g++ -o jumper *.cpp common/*.cpp -I/usr/local/include/ -I/usr/include /usr/lib/libGLEW.a -L/usr/local/lib -lode -lglfw3 -framework OpenGL -framework CoreFoundation -framework CoreGraphics -framework CoreVideo -framework IOKit -framework AppKit

run:

./jumper torques.txt
