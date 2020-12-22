CXX = g++
CFLAGS =
LDFLAGS =
 
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
 
OUTPUT = prog
 
all: $(OBJ)
	$(CXX) $(LDFLAGS) -o $(OUTPUT) $^
 
$(OBJ): %.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
 
 
.PHONY: clean mrproper
 
clean:
	rm -rf *.o
 
mrproper: clean
	rm -rf $(OUTPUT)
