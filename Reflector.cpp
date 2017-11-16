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
  if (!isInvalidMapping(v)) {
    cerr << error_description(INVALID_REFLECTOR_MAPPING);
    exit(INVALID_REFLECTOR_MAPPING);
  }

  if (v.size() != 26) {
    cerr << error_description(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
    exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
  }

  invalidIndexOrChar(v);

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

  return -1;// unable to reflected
}
