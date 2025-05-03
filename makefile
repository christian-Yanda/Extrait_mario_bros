all:

gcc -I src/SDL2/include -L src/SDL2/lib -o jump src/*.c -lmingw32 -lSDL2main -lSDL2