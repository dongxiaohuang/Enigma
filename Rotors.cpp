#include "Rotors.h"
#include "helper.h"
#include "errors.h"
#include <iostream>

using namespace std;

Rotors::Rotors(const char *filename, int pos_num) {
  FILENAME = filename;
  pos = pos_num;
  trigger_rotate_times = 0;
  checkRt();
  rot_vec = getVector(v);
  while (rot_vec.size() > 26) {
    notch_vec.push_back(rot_vec[rot_vec.size() - 1]);
    rot_vec.pop_back();
  }
}

int Rotors::start(int  in_num, int rote_times, bool un_reflected) {
  int abs_in;
  int relative_in_num;
  int map_to_rel;
  int map_to_abs;
  abs_in = in_num;
  in_num = (in_num + pos) % 26;
  rotate_times = rote_times;
  relative_in_num = (in_num + rotate_times) % 26;
  if (un_reflected) {
    for (unsigned i = 0; i < notch_vec.size(); ++i) {
      if ((rote_times + pos) % 26 == notch_vec[i])
	trigger_rotate_times++;
    }

    map_to_rel = rot_vec[relative_in_num];
  } else {
    for (unsigned i = 0; i < rot_vec.size(); ++i) {
      if (rot_vec[i] == relative_in_num)
	map_to_rel = i;
    }
  }
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
  if (!isInvalidMapping(v_non_notch) || v_non_notch.size() != 26) {
    cerr << error_description(INVALID_ROTOR_MAPPING);
    exit(INVALID_ROTOR_MAPPING);
  }

  invalidIndexOrChar(v);
}

int Rotors::getTrigerRotateTimes() {
  return trigger_rotate_times;

}

int Rotors::getRotateTimes() {
  return rotate_times;
}
