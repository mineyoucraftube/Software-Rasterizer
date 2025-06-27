
PROJECT_NAME = software_rasterizer

CC = gcc
CPP = g++

SRC_DIR = src
SRC_DIR_OGL = $(SRC_DIR)/openGL

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
OBJ_DIR_C = $(OBJ_DIR)/obj_c
OBJ_DIR_CPP = $(OBJ_DIR)/obj_cpp
OBJ_DIR_OGL = $(OBJ_DIR)/openGL

OUT_DIR = $(BUILD_DIR)/out

CFLAGS = -g


#https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html ____LOOK AT THIS NEXT TIME____


_SRCC = $(wildcard $(SRC_DIR)/*.c)
_SRCCPP = $(wildcard $(SRC_DIR)/*.cpp)
_SRCOGL = $(wildcard $(SRC_DIR_OGL)/*.c)
SRC = $(_SRCC) $(_SRCCPP) $(_SRCOGL)

_OBJC = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_C)/%.o, $(wildcard $(SRC_DIR)/*.c))
_OBJCPP = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR_CPP)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
_OBJOGL = $(patsubst $(SRC_DIR_OGL)/%.c, $(OBJ_DIR_OGL)/%.o, $(wildcard $(SRC_DIR_OGL)/*.c))
OBJ = $(_OBJC) $(_OBJCPP) $(_OBJOGL)

_LIBOGL = $(SRC_DIR_OGL)/libglfw3.a
LIB = $(_LIBOGL)

SRC_C	= $(SRC_DIR)/%.c
SRC_CPP	= $(SRC_DIR)/%.cpp
SRC_OGL = $(SRC_DIR_OGL)/%.c

OBJ_C	= $(OBJ_DIR_C)/%.o
OBJ_CPP	= $(OBJ_DIR_CPP)/%.o
OBJ_OGL = $(OBJ_DIR_OGL)/%.o

OUT = $(OUT_DIR)/$(PROJECT_NAME)
#OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) 
#OBJSS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
#OBJSSS = $(patsubst $(LIB_DIR)/%.a, $(OBJ_DIR)/%.o, $(SRC))


all: $(OUT)

$(OBJ_C): $(SRC_C)
	@mkdir -p $(OBJ_DIR_C)
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(SRC_DIR_OGL)
	
$(OBJ_CPP): $(SRC_CPP)
	@mkdir -p $(OBJ_DIR_CPP)
	$(CPP) $(CFLAGS) -c $^ -o $@ -I $(SRC_DIR_OGL)

$(OBJ_OGL): $(SRC_OGL)
	@mkdir -p $(OBJ_DIR_OGL)
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(SRC_DIR_OGL)

$(OUT): $(OBJ)
	@mkdir -p $(OUT_DIR)
	$(CPP) $(OBJ) $(LIB) -o $(OUT)
	@echo "\033[0;32mgood to go\033[0m"


run:
	@mkdir -p build/images
	-./$(OUT)
#	cp test.bin test.bmp

clean:
	rm -f $(OBJ)

rmbuild:
	rm -f $(OUT)
.INTERMEDIATE: $(OBJ)