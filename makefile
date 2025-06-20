
PROJECT_NAME = software_rasterizer

CC = gcc
CPP = g++

SRC_DIR = src

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
OBJ_DIR_C = $(OBJ_DIR)/obj_c
OBJ_DIR_CPP = $(OBJ_DIR)/obj_cpp

OUT_DIR = $(BUILD_DIR)/out

CFLAGS = -g


#https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html ____LOOK AT THIS NEXT TIME____

SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_C)/%.o, $(wildcard $(SRC_DIR)/*.c)) $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR_CPP)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
SRC_C	= $(SRC_DIR)/%.c
SRC_CPP	= $(SRC_DIR)/%.cpp
SRC_C_CPP_H	= $(SRC_DIR)/%.h
OBJ_C	= $(OBJ_DIR_C)/%.o
OBJ_CPP	= $(OBJ_DIR_CPP)/%.o

OUT = $(OUT_DIR)/$(PROJECT_NAME)
#OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) 
#OBJSS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
#OBJSSS = $(patsubst $(LIB_DIR)/%.a, $(OBJ_DIR)/%.o, $(SRC))


all: $(OUT)

$(OBJ_C): $(SRC_C)
	@mkdir -p $(OBJ_DIR_C)
	$(CC) $(CFLAGS) -c $^ -o $@
	
#$(OBJ_CPP): $(SRC_CPP) $(SRC_C_CPP_H)
#	@mkdir -p $(OBJ_DIR_CPP)
#	$(CPP) $(CFLAGS) -c $(patsubst $(SRC_DIR)/%.h, , $^) -o $@

$(OBJ_CPP): $(SRC_CPP)
	@mkdir -p $(OBJ_DIR_CPP)
	$(CPP) $(CFLAGS) -c $^ -o $@ 


$(OUT): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(CPP) $(OBJ) -o $(OUT)
	@echo "\033[0;32mgood to go\033[0m"


run:
	-./$(OUT)
#	cp test.bin test.bmp

clean:
	rm -f $(OBJ)

.INTERMEDIATE: $(OBJ)