#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
int const NUM_NEEDED_FILES = 4;// AN ENIGMA INPUT NEED 4 BASIC INPUT, NAMELY ./enigma; pb_file; rf_file; pos_file;
std::vector<int> getVectorInt(const char *filename);

std::vector<int> getVector(std::vector<string> v);

const char *error_description(int code);

char intToChar(int num);

bool isDigits(const std::string &str);

void getStringVector(const char *,
                     std::vector<string> &v); //if you use string you need to include<string> and using namespace std
bool isInvalidMapping(std::vector<string> v);

int invalidIndexOrChar(std::vector<string> v);

void checkPos(const char *filenam, int argc);

void isUpperCh(char);

void checkParameters(int argc, char **argv);

#endif
