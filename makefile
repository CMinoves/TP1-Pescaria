CC=gcc
OPCOES_COMPILADOR=-lglut -lGLU -lGLEW -lGL -lSDL -lSDL_mixer -lSOIL -lm

TODOS_ARQUIVOS_PONTOH = 
TODOS_ARQUIVOS_OBJ = Menu.o

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o Menu $^ $(OPCOES_COMPILADOR)

run: all
	./Menu

clean:
	rm *.o Menu
