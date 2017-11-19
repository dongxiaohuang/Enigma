#include <fstream>
#include <iostream>
#include <vector>
#include "Reflector.h"
#include "errors.h"
#include "helper.h"

using namespace std;

Reflector::Reflector(const char *config_filename) {
    FILENAME = config_filename;
    checkRf();
    ref_vec = getVector(v);
}

void Reflector::checkRf() {
    getStringVector(FILENAME, v);
    if (v.size() != 26) {
        if (v.size() % 2 == 0)
            cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
        else
            cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;

        exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    }
    if (!isInvalidMapping(v)) {
        cerr << error_description(INVALID_REFLECTOR_MAPPING);
        exit(INVALID_REFLECTOR_MAPPING);
    }

    switch (invalidIndexOrChar(v)) {
        case NON_NUMERIC_CHARACTER: {
            cerr << "Non-numeric character in reflector file reflector.rf" << endl;
            exit(NON_NUMERIC_CHARACTER);
        }
        case INVALID_INDEX: {
            cerr << error_description(INVALID_INDEX) << endl;
            exit(INVALID_INDEX);
        }
    }
}

int Reflector::start(int num) {
    for (unsigned i = 0; i < ref_vec.size(); ++i) {
        if (ref_vec[i] == num) {
            if (i % 2 == 0)
                return ref_vec[i + 1];
            else
                return ref_vec[i - 1];
        }

    }

    exit(-1);
}
