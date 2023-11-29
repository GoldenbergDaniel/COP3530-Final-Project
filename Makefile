NAME = SpaceGame
CC = c++

CFLAGS = -Ilib/ \
				 -std=c++17 -O1 \
				 -Wall -Wextra -Wpedantic \
				 -Wno-missing-braces \
				 -Wno-unused-function \

LDFLAGS = -framework OpenGL \
					-lsdl2 \

LIB = lib/glad/glad.cpp \

SRC = src/main.cpp \

.PHONY: all compile compile_t run test debug combine

all: compile run

compile:
	@echo "Compiling project..."
	@./ParseShaders
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LIB) $(SRC) -o $(NAME)
	@echo "Compilation complete!"

compile_t:
	@echo "Compiling timed compilation..."
	@time $(CC) $(CFLAGS) $(LDFLAGS) $(LIB) $(SRC) -o $(NAME)
	@echo "Compilation complete!"

run:
	./$(NAME)

debug:
	@echo "Compiling debug..."
	@cd debug; \
	$(CC) -I../lib/ $(LDFLAGS) ../lib/glad/glad.c ../src/*.c -g
	@echo "Compilation complete!"
