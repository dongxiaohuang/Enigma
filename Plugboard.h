#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <vector>
#include <string>

using namespace std;

class Plugboard {
 public:
  void checkpg();

  int start(char);

  Plugboard(const char *filename);

 private:
  const char *FILENAME;
  std::vector<int> vector1;
  std::vector<string> v;
};

#endif
