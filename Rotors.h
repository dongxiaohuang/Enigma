#ifndef ROTORS_H
#define ROTORS_H

#include <vector>
#include <string>

using namespace std;

class Rotors {
public:
    void checkRt();

    Rotors(const char *filename, int pos);

    int start(int, int, bool);

    int getTrigerRotateTimes();

    int getRotateTimes();

private:
    const char *FILENAME;
    vector<int> rot_vec;
    vector<string> v;
    vector<int> notch_vec;
    int pos;
    int rotate_times;
    int trigger_rotate_times;
};

#endif
