# CROSS_COMPILE = aarch64-linux-gnu-
# CXX = $(CROSS_COMPILE)g++
# LD = $(CROSS_COMPILE)ld
CXX = g++
CXXFLAGS = -std=c++11
OBJ = main.o 
SRC = main.cpp 
EXE = L2Program
all:$(EXE)
$(EXE):$(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)
$(OBJ):$?
	$(CXX) $(CXXFLAGS) -c $(SRC)
clean:
	rm -f $(EXE)
	rm -f $(OBJ)