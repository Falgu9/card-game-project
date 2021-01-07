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
	rm -f -v *.o
	
mrproper: clean
	rm -f -v $(OUTPUT)

