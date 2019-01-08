# the compiler: gcc for C program, define as g++ for C++
CC = g++

# Open GL flags:
# 	-lglut
#	-lGL
#	-lGLU
GLFLAGS	= -lglut -lGL -lGLU

# compiler flags:
#	-g    adds debugging information to the executable file
#	-Wall turns on most, but not all, compiler warnings
#	-c into and an object file (.o file)
CFLAGS  = -c -g -Wall --std=c++11

LDFLAGS =



# docs = https://www.gnu.org/software/make/manual/make.html
# some compilation flags = https://web.engr.oregonstate.edu/~rubinma/Mines_274/Content/Slides/05_compilation.pdf
# helper = http://www.opennet.ru/docs/RUS/gnumake/#Multi-config_multi-dirs
# the build target executable:
SRC_DIR = source
SOURCES = $(addsuffix .cpp, main scene octahedron)
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cpp=.o))

#SRCH_WILDCARDS = $(addsuffix /*.cpp,$(SRC_DIR))

EXECUTABLE = $(OBJ_DIR)/work.a

DIRS = $(SRC_DIR) $(OBJ_DIR)
MKDIR = mkdir -p



.PHONY: all clean do start

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@ $(GLFLAGS)

VPATH = $(SRC_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(addprefix -I,$(SRC_DIR)) $< -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

do: all
	./$(EXECUTABLE)

start:
	$(MKDIR) $(DIRS)
