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
  if (!isInvalidMapping(v)) {
    cerr << error_description(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
    exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
  }

  if (v.size() % 2 != 0 || v.size() > 26) {
    cerr << error_description(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
  }
  invalidIndexOrChar(v);


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
