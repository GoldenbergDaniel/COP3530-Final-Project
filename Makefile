NAME = Traveller
CC = c++

CFLAGS = 	-std=c++14 \
					-O0 \
					-Iext/ \
					-I/usr/local/Cellar/sdl2/2.28.4/include \
					-fno-exceptions \
					-Wall \
					-Wpedantic \
					-Wno-missing-braces \
					-Wno-unused-function \
					-Wno-language-extension-token \
					-Wno-gnu-anonymous-struct \
					-Wno-nested-anon-types \
					-Wno-c99-extensions \
					-Wno-vla-extension \

LDFLAGS = -framework OpenGL \
					-lsdl2 \

EXT = ext/base/*.cpp \
			ext/glad/*.cpp \
			-L. -limgui \

SRC = src/*.cpp \
			src/gfx/*.cpp \

.PHONY: all compile compile_t run test debug combine

all: compile run

compile:
	@echo "Compiling project..."
	@./ParseShaders
	@$(CC) $(CFLAGS) $(LDFLAGS) $(EXT) $(SRC) -o $(NAME)
	@echo "Compilation complete!"

compile_t:
	@echo "Compiling timed compilation..."
	@time $(CC) $(CFLAGS) $(LDFLAGS) $(EXT) $(SRC) -o $(NAME)
	@echo "Compilation complete!"

lib:
	@$(CC) $(CFLAGS) $(LDFLAGS) -shared -fPIC -o imgui.dylib ext/imgui/*.cpp

run:
	./$(NAME)
