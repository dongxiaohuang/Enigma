#include "helper.h"
#include "errors.h"
#include "Enigma.h"
using namespace std;
int main(int argc, char** argv) {
  checkParameters(argc, argv);
  checkPos(argv[argc-1],argc);
  Enigma enigma(argc, argv);
  enigma.start();
  return NO_ERROR;
}
