CC		:= gcc
CFLAGS	:= -g -Wall -pedantic -Wextra -Wwrite-strings

BIN		:= bin
SRC		:= src
INCLUDE	:= include

PROGARGS	:= 

EXECUTABLE	:= trab3
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.c=.o)

all: clean $(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(EXECUTABLE)
	-$(RM) $(OBJECTS)


run: all
	./$(EXECUTABLE) $(PROGARGS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(LIBRARIES) -lm

val: all
	valgrind ./$(EXECUTABLE) $(PROGARGS)

full: all
	- valgrind -v --leak-check=full ./$(EXECUTABLE) $(PROGARGS)