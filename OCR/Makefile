# Simple SDL mini Makefile

CC=gcc -rdynamic

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm



SRC = main.c Pre-traitement/pixel_operations.c Pre-traitement/Filter.c NeuralNetwork/NeuralNetwork.c NeuralNetwork/NeuralNetworkTools.c NeuralNetwork/NeuralNetworkPrintValue.c segmentation/convert_image.c segmentation/resizeLetters.c segmentation/rlsa.c segmentation/segmentation.c segmentation/split.c

OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)



all: main

main: $(OBJ)

clean:
		$(RM) $(OBJ) $(OBJ_TESTS) $(DEP) $(DEP_TESTS) main && clear

# END
