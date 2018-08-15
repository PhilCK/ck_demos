cc \
  src/main.c \
  -I /usr/local/include/ \
  -L /usr/local/lib/ \
  -lSDL2 \
  -framework OpenGL \
  -ansi -Wall -std=c89 \
  -o ./bin/demo
