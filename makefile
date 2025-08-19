
PROJECT_NAME = software_rasterizer

CC = gcc
CPP = g++
AR = ar
CL = g++

SRC_DIR = src
SRC_DIR_OGL = $(SRC_DIR)/openGL/src

BUILD_DIR = build

OBJ_DIR = $(BUILD_DIR)/obj
OBJ_DIR_C = $(OBJ_DIR)/obj_c
OBJ_DIR_CPP = $(OBJ_DIR)/obj_cpp
OBJ_DIR_OGL = $(OBJ_DIR)/openGL

LIB_DIR = $(BUILD_DIR)/lib

INC_DIR = $(SRC_DIR)/openGL/include

OUT_DIR = $(BUILD_DIR)/out

CFLAGS = -g


#https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html ____LOOK AT THIS NEXT TIME____


_SRCC = $(wildcard $(SRC_DIR)/*.c)
_SRCCPP = $(wildcard $(SRC_DIR)/*.cpp)
_SRCOGL = $(wildcard $(SRC_DIR_OGL)/*.c)
SRC = $(_SRCC) $(_SRCCPP) $(_SRCOGL)
#unused lmao ^

_OBJC = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_C)/%.o, $(wildcard $(SRC_DIR)/*.c))
_OBJCPP = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR_CPP)/%.o, $(wildcard $(SRC_DIR)/*.cpp))
_OBJOGL = $(patsubst $(SRC_DIR_OGL)/%.c, $(OBJ_DIR_OGL)/%.o, $(wildcard $(SRC_DIR_OGL)/*.c))
#_APLOBJOGL = $(patsubst $(SRC_DIR_OGL)/%.m, $(OBJ_DIR_OGL)/%.o, $(wildcard $(SRC_DIR_OGL)/*.m))
OBJ = $(_OBJC) $(_OBJCPP) $(_OBJOGL)
OBJ_project = $(_OBJC) $(_OBJCPP)
OBJ_opengl = $(_OBJOGL)
#OBJ_opengl = $(_OBJOGL) $(_APLOBJOGL)


SRC_C	= $(SRC_DIR)/%.c
SRC_CPP	= $(SRC_DIR)/%.cpp
SRC_OGL = $(SRC_DIR_OGL)/%.c
APL_SRC_OGL = $(SRC_DIR_OGL)/%.m
OBJ_C	= $(OBJ_DIR_C)/%.o
OBJ_CPP	= $(OBJ_DIR_CPP)/%.o
OBJ_OGL = $(OBJ_DIR_OGL)/%.o

LIB = $(LIB_DIR)/opengl.a

OUT = $(OUT_DIR)/$(PROJECT_NAME)
#OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) 
#OBJSS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
#OBJSSS = $(patsubst $(LIB_DIR)/%.a, $(OBJ_DIR)/%.o, $(SRC))


all: $(OUT)

$(OBJ_C): $(SRC_C)
	@mkdir -p $(OBJ_DIR_C)
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(INC_DIR)
	
$(OBJ_CPP): $(SRC_CPP)
	@mkdir -p $(OBJ_DIR_CPP)
	$(CPP) $(CFLAGS) -c $^ -o $@ -I $(INC_DIR)

$(OBJ_OGL): $(SRC_OGL)
	@mkdir -p $(OBJ_DIR_OGL)
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(INC_DIR)

#$(OBJ_OGL): $(APL_SRC_OGL)
#	@mkdir -p $(OBJ_DIR_OGL)
#	$(CC) $(CFLAGS) -c $^ -o $@ -I $(INC_DIR)

$(LIB): $(OBJ_opengl)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $(LIB) $(OBJ_opengl)

$(OUT): $(OBJ_project) $(LIB)
	@mkdir -p $(OUT_DIR)
	$(CPP) $(OBJ_project) $(LIB) -o $(OUT)
	@echo "\033[0;32mgood to go\033[0m"

build/main.o: main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CPP) $(CFLAGS) -c $^ -o $@ -I $(INC_DIR)


test: build/main.o $(OBJ_project) $(LIB)
	@mkdir -p $(OUT_DIR)
	$(CPP) $(patsubst $(OBJ_DIR_CPP)/main.o, build/main.o, $(OBJ_project)) $(LIB) -o $(OUT)
	@echo "\033[0;32mgood to go\033[0m"


run:
	@mkdir -p build/images
	-./$(OUT)
#	cp test.bin test.bmp

clean:
	rm -f $(OBJ)

rmbuild:
	rm -f $(OUT)
.INTERMEDIATE: $(OBJ_project)