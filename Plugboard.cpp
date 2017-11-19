#include "Plugboard.h"
#include "helper.h"
#include "errors.h"
#include <iostream>

using namespace std;

Plugboard::Plugboard(const char *config_filename) {
    FILENAME = config_filename;
    checkpg();
    vector1 = getVector(v);
}

void Plugboard::checkpg() {
    getStringVector(FILENAME, v);
    if (v.size() != 0) {

        if (v.size() % 2 != 0 || v.size() > 26) {
            cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
            exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
        }

        if (!isInvalidMapping(v)) {
            cerr << error_description(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
            exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
        }

        switch (invalidIndexOrChar(v)) {
            case NON_NUMERIC_CHARACTER: {
                cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
                exit(NON_NUMERIC_CHARACTER);
            }
            case INVALID_INDEX: {
                cerr << error_description(INVALID_INDEX) << endl;
                exit(INVALID_INDEX);
            }
        }



    }


}

int Plugboard::start(char ch) {

    int char_index = ch - 'A';
    for (unsigned i = 0; i < vector1.size(); ++i) {
        if (char_index == vector1[i]) {
            if (i % 2 == 0)
                return vector1[i + 1];
            else
                return vector1[i - 1];
        }

    }
    return char_index;
}
