#include "helper.h"
#include "errors.h"
#include <iostream>
#include <algorithm>

using namespace std;

std::vector<int> getVectorInt(const char *filename) {
    ifstream file(filename);
    if (file.fail())
        cerr << "cannot open file" << filename << endl;
    string line;
    getline(file, line);
    istringstream iss(line);
    vector<int> v;
    int num;
    while (iss >> num) {
        v.push_back(num);
    }
    return v;
}

/* function to report the errors encountered in this program */
const char *error_description(int code) {
    switch (code) {
        case 1:
            return "INSUFFICIENT_NUMBER_OF_PARAMETERS";
        case 2:
            return "INVALID_INPUT_CHARACTER";
        case 3:
            return "INVALID_INDEX";
        case 4:
            return "NON_NUMERIC_CHARACTER";
        case 5:
            return "IMPOSSIBLE_PLUGBOARD_CONFIGURATION";
        case 6:
            return "INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS";
        case 7:
            return "INVALID_ROTOR_MAPPING";
        case 8:
            return "NO_ROTOR_STARTING_POSITION";
        case 9:
            return "INVALID_REFLECTOR_MAPPING";
        case 10:
            return "INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS";
        case 11:
            return "ERROR_OPENING_CONFIGURATION_FILE";

    }
    return "Unknown error";
}

char intToChar(int num) {
    char ch;
    ch = static_cast<char>(num + 'A');
    return ch;
}

bool is_digits(const std::string &str) {
    return all_of(str.begin(), str.end(), ::isdigit); // C++11
}


void getStringVector(const char *FILENAME, std::vector<string> &v) {
    ifstream ifstr(FILENAME);
    if (ifstr.fail()) {
        cerr << error_description(ERROR_OPENING_CONFIGURATION_FILE);
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }

    string line;
    getline(ifstr, line);
    std::istringstream iss(line);
    string n;
    while (iss >> n) {
        v.push_back(n);
    }
}

bool isInvalidMapping(std::vector<string> v) {
    for (unsigned i = 0; i < v.size() - 1; ++i) {
        for (unsigned j = i + 1; j < v.size(); ++j) {
            if (v[i] == v[j])
                return false;
        }
    }
    return true;
}

int invalidIndexOrChar(std::vector<string> v) {
    for (unsigned k = 0; k < v.size(); ++k) {
        if (!is_digits(v[k])) {
            return NON_NUMERIC_CHARACTER;
        }
        int num = atoi(v.at(k).c_str());
        if (num > 25 || num < 0) {
            return INVALID_INDEX;
        }
    }
    return -1;
}

// TODO: check
void checkPos(const char *filename, int argc) {
    // check if pos configue is valid or not
    std::vector<string> pos_vec_str;
    getStringVector(filename, pos_vec_str);
    switch (invalidIndexOrChar(pos_vec_str)) {
        case NON_NUMERIC_CHARACTER: {
            cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
            exit(NON_NUMERIC_CHARACTER);
        }
        case INVALID_INDEX: {
            cerr << error_description(INVALID_INDEX) << endl;
            exit(INVALID_INDEX);
        }
    }

    unsigned num_rots = argc - NUM_NEEDED_FILES;
    unsigned miss_pos_num = num_rots - pos_vec_str.size();
    if (miss_pos_num > 0) {
        for (unsigned i = pos_vec_str.size(); i <= num_rots - 1; ++i) {
            cerr << "No starting position for rotor <<i<< in rotor position file: rotor.pos" << endl;
        }
        exit(NO_ROTOR_STARTING_POSITION);
    }
}

std::vector<int> getVector(std::vector<string> v) {
    std::vector<int> intNumbers;
    for (unsigned i = 0; i < v.size(); i++) {
        int num = atoi(v.at(i).c_str());
        intNumbers.push_back(num);
    }
    return intNumbers;
}

void isUpperCh(char ch) {
    if (ch > 'Z' || ch < 'A') {
        cerr << ch << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
        exit(INVALID_INPUT_CHARACTER);
    }
}

void checkParameters(int argc, char **argv) {
    int enough_parameter_flag = 1;
    string filename;
    if (argc >= 3) {
        //check if contain pb file
        filename = argv[1];
        if (filename.find(".pb") == std::string::npos)
            enough_parameter_flag = 0;
        //check if contain rf file
        filename = argv[2];
        if (filename.find(".rf") == std::string::npos)
            enough_parameter_flag = 0;
        //check if contain pos file
        if (argc >= 4) {
            filename = argv[argc - 1];
            if (filename.find(".pos") == std::string::npos)
                enough_parameter_flag = 0;
        }
    } else
        enough_parameter_flag = 0;
    if (enough_parameter_flag == 0) {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }
}
