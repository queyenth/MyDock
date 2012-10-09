OBJ = main.o MyDock.o Icon.o
BIN = MyDock.exe
LIB = -lwinmm -lcomdlg32 -lgdi32 -mwindows
FLAGS = -O2 -DWIN32 -D_WINDOWS -mwindows

all: $(OBJ)
	g++ -o $(BIN) $(OBJ) $(LIB)

%.o: %.cpp
	g++ -c $< $(FLAGS)

clean:
	del $(BIN) $(OBJ)

main.o: main.cpp MyDock.hpp
MyDock.o: MyDock.cpp MyDock.hpp Icon.hpp
Icon.o: Icon.cpp Icon.hpp