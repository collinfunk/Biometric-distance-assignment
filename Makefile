DIR_BUILD := _build
DIR_SRC := src

CC := clang
CFLAGS := 

SRC := $(wildcard $(DIR_SRC)/*.c)
OBJ := $(patsubst $(DIR_SRC)/%.c, $(DIR_BUILD)/%.o, $(SRC))
TARGET := $(DIR_BUILD)/main

.PHONY: all clean run

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(DIR_BUILD)/%.o: $(DIR_SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(DIR_BUILD)/*
