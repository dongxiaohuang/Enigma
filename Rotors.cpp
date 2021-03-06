#include "Rotors.h"
#include "helper.h"
#include "errors.h"
#include <iostream>

using namespace std;

Rotors::Rotors(const char *filename, int pos_num) {
    FILENAME = filename;
    pos = pos_num;
    trigger_rotate_times = 0; // USED TO INDICATE THE TIMES OF ROTATE OF THE ROTORS EXPECT FOR RIGHT MOST ROTOR
    checkRt();
    rot_vec = getVector(v); // GET THE RAW CONFIGURE NUMBERS OF ROTOR FILE
    // GET NOTCH VECTOR AND MAPPING VECTOR
    while (rot_vec.size() > 26) {
        notch_vec.push_back(rot_vec[rot_vec.size() - 1]);// NOTCH VECTOR
        rot_vec.pop_back(); // MAPPING VECTOR
    }
}

int Rotors::start(int in_num, int rote_times, bool un_reflected) {
    int abs_in;
    int relative_in_num;
    int map_to_rel;
    int map_to_abs;
    abs_in = in_num;//INPUT OF ABSOLUTE POSITION
    in_num = (in_num + pos) % 26;// INPUT OF RELATIVE POSITION WHEN UN-ROTATED
    rotate_times = rote_times;
    relative_in_num = (in_num + rotate_times) % 26;// RELATIVE INPUT
    if (un_reflected) {
        // UNREFLECTED
        for (auto i:notch_vec) {//ITERATE THE NOTCH VECTOR
            // IF THE NOTCH HIT THE ABSOLUTE 'A' POSITION TRIGGER ONE TIME OF NEXT ROTOR TO ROTATE
            if ((rote_times + pos) % 26 == i)
                trigger_rotate_times++;
        }
        // MAPPING TO NUMBER IN RELATIVE POSITION
        map_to_rel = rot_vec[relative_in_num];
    } else {// WHEN REFLECTED
        // DE-MAPPING
        for (unsigned i = 0; i < rot_vec.size(); ++i) {
            if (rot_vec[i] == relative_in_num)
                map_to_rel = i;
        }
    }
    // CONVERT THE RELATIVE POSITION TO ABSOLUTE POSITION
    map_to_abs = (map_to_rel - relative_in_num + abs_in + 26) % 26;
    return map_to_abs;
}

void Rotors::checkRt() {
    getStringVector(FILENAME, v);
    std::vector<string> v_non_notch = v;
    if (v.size() > 26) {
        for (unsigned i = 26; i < v.size(); ++i) {
            v_non_notch.pop_back();
        }
    }
    // check invalid mapping
    for (unsigned i = 0; i < v_non_notch.size() - 1; ++i) {
        for (unsigned j = i + 1; j < v_non_notch.size(); ++j) {
            if (v_non_notch[i] == v_non_notch[j]) {
                cerr << "Invalid mapping of input " << j << " to output " << v_non_notch[j] << " (output "
                     << v_non_notch[j] << " is already mapped to from input " << i << ")" << endl;
                exit(INVALID_ROTOR_MAPPING);
            }
        }
    }


    if (v_non_notch.size() != 26) {
        if (v_non_notch.size() != 26)
            cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
        exit(INVALID_ROTOR_MAPPING);
    }
    // check finish
    switch (invalidIndexOrChar(v)) {
        case NON_NUMERIC_CHARACTER: {
            cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
            exit(NON_NUMERIC_CHARACTER);
        }
        case INVALID_INDEX: {
            cerr << error_description(INVALID_INDEX) << endl;
            exit(INVALID_INDEX);
        }
    }
}

int Rotors::getTrigerRotateTimes() {
    return trigger_rotate_times;

}

int Rotors::getRotateTimes() {
    return rotate_times;
}
