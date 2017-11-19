#ifndef ENIGMA_H
#define ENIGMA_H

#include "Reflector.h"
#include "Plugboard.h"
#include "Rotors.h"

#include <vector>

using namespace std;

class Enigma {
private:
    vector<Rotors *> rots; // TO STORE THE ROTORS AUTOMATICALLY
    Plugboard plugboard;
    Reflector reflector;
    int number_of_rots;
    std::vector<int> pos_vec;
    int cipher_nums;
public:
    Enigma(int argc, char **argv);

    void start();

    ~Enigma();

};

#endif
