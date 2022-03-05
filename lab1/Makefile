CROSS_COMPILE = aarch64-linux-gnu-
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
CXXFLAGS = -std=c++11
OBJ = main.o circular_sector.o ellipse.o sort.o triangle.o
SRC = main.cpp circular_sector.cpp ellipse.cpp sort.cpp triangle.cpp
EXE = tx2_exe
all:$(EXE)
$(EXE):$(OBJ)
	$(CXX) -o $(EXE) $(OBJ)
$(OBJ):$(SRC)
	$(CXX) -c $(SRC)
clean:
	rm -f $(EXE)
	rm -f $(OBJ)