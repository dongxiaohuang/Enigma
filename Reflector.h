#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <vector>
#include <string>

using namespace std;

class Reflector {
public:
    void checkRf();

    Reflector(const char *);

    int start(int);

private:
    const char *FILENAME;
    std::vector<int> ref_vec;
    std::vector<string> v;

};

#endif
