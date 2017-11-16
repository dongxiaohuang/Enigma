OBJ = helper.o Plugboard.o Reflector.o Rotors.o Enigma.o main.o

enigma: $(OBJ)
	g++ $(OBJ) -o enigma

%.o: %.cpp
	g++ -std=c++11 -Wall -g -c $<

main.o: helper.h errors.h Enigma.h

Plugboard.o: Plugboard.h helper.h errors.h

helper.o: helper.h

Reflector.o: Reflector.h

Rotors.o: Rotors.h

Enigma.o: Reflector.h Plugboard.h Enigma.h Rotors.h

clean:
	rm -f *.o enigma $(OBJ:.o=.d)

