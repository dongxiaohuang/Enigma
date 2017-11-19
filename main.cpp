#include "helper.h"
#include "errors.h"
#include "Enigma.h"

using namespace std;

int main(int argc, char **argv) {
        //CHECK IF THE PARAMETER FOR THE FILES NEEDED IS COMPLETED
    checkParameters(argc, argv);
    if (argc >= 4) {
        //IF THERE EXIST ROTORS THEN THERE MUST BE POSITION FILE AND IT SHOULD BE CHECK
        checkPos(argv[argc - 1], argc);
    }
    Enigma enigma(argc, argv);
    enigma.start();
    return NO_ERROR;
}
