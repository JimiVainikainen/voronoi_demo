OBJS = app.cpp
CXX = g++
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
INCLUDE_FLAGS = -I src/include
LIB_FLAGS = -L src/lib

all: $(OBJS)
	$(CXX) $(INCLUDE_FLAGS) $(LIB_FLAGS) $(OBJS) -o Application  $(LINKER_FLAGS)
main:
	$(CXX) $(INCLUDE_FLAGS) $(LIB_FLAGS) -o main main.cpp $(LINKER_FLAGS)
