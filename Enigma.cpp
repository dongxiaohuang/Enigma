#include "Enigma.h"
#include "helper.h"
#include <iostream>

using namespace std;

Enigma::Enigma(int argc, char **argv) : plugboard(argv[1]), reflector(argv[2]) {
    if (argc >= 4) {
        number_of_rots = argc - NUM_NEEDED_FILES;
        pos_vec = getVectorInt(argv[argc - 1]);
    } else { number_of_rots = 0; }

    for (int i = 0; i <= number_of_rots - 1; ++i) {
        rots.push_back(new Rotors(argv[3 + i], pos_vec[i]));
    }
    cipher_nums = 0;// to indicate how many cipher inputed
}


void Enigma::start() {

    char ch;
    // clear previous result
    string inputstream;
    getline(cin, inputstream);
    for (unsigned ch_index = 0; ch_index < inputstream.length(); ch_index++) {
        ch = inputstream[ch_index];
        if (ch == ' ')
            continue;
        //CHECK IF IT IS UPPER CASE LETTER
        isUpperCh(ch);
        cipher_nums++;
        int rot_in;
        int rf_in;
        int pb_in;
        bool unReflected = true;
        pb_in = plugboard.start(ch);
        if (number_of_rots == 0) {
            rot_in = reflector.start(pb_in);
        } else {
            rot_in = rots[number_of_rots - 1]->start(pb_in, cipher_nums, unReflected);
            if (number_of_rots >= 2) {
                for (int i = 2; i <= number_of_rots; ++i) {
                    int && last_trigger_times = rots[number_of_rots - i + 1]->getTrigerRotateTimes(); // use rvalue reference
                    rot_in = rots[number_of_rots - i]->start(rot_in,
                                                             last_trigger_times,
                                                             unReflected);
                }
            }
            rf_in = reflector.start(rot_in);
            unReflected = false;
            rot_in = rots[0]->start(rf_in, rots[0]->getRotateTimes(), unReflected);
            if (number_of_rots >= 2) {
                for (int j = 1; j <= number_of_rots - 1; ++j) {
                    int && rotate_times = rots[j]->getRotateTimes();
                    rot_in = rots[j]->start(rot_in, rotate_times, unReflected);
                }
            }

        }
        char res_ch = intToChar(rot_in);
        pb_in = plugboard.start(res_ch);
        cout << intToChar(pb_in);
    }

}

Enigma::~Enigma() {
    for (int i = 0; i < number_of_rots; ++i) {
        delete rots[i];
    }
}
