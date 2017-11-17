OBJ = helper.o Plugboard.o Reflector.o Rotors.o Enigma.o main.o
CXX = g++
CXXFLAGS = -Wall -g -MMD
EXE = enigma
$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -std=c++11 -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f *.o $(EXE) $(OBJ:.o=.d)
.PHONY:clean

