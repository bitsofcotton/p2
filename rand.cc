#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include <random>
#include <sys/resource.h>

#include "../p0/lieonn.hh"
typedef myfloat num_t;
int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::random_device rd;
  std::mt19937_64 mt(rd());
  std::knuth_b    kb(rd());
  std::ranlux48   rl48(rd());
  // N.B. bitwise xor causes original matrix addition.
  //      this causes maximum of matrix size will be selected.
  //      smaller matrixes effects some of the result, but if the distribution
  //      isn't harmful and has non small orthogonal parts norm,
  //      they shouldn't harms.
  int b(0);
  while(true) {
    // N.B. knuth_b returns shorter size of RAND_MAX.
    std::cout <<
      (num_t(((int(rd()) ^ int(mt()) ^ int(kb()) ^ int(rl48())) >> 1)
              & 0x7fffff) / (num_t(int(0x7fffff)) / num_t(int(2)))
       - num_t(int(1))) << std::endl << std::flush;
/*
    // XXX: echo "" > h; sleep ...; rm -f h; to reseed.
    //      we should do with main getline, but we need mt or socket for them.
    ifstream h("./h");
    if(h.is_open() && ! b) {
      mt = std::mt19937_64(rd());
      kb = std::knuth_b(rd());
      rl48 = std::ranlux48(rd());
      std::cerr << "* reseed *" << std::endl;
      b = 1;
    } else if(! h.is_open() && b) b = 0;
    h.close();
*/
  }
  return 0;
}

