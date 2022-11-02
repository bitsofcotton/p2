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

#include "../catg/lieonn.hh"
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
  while(true)
    std::cout <<
      (num_t((int(arc4random()) ^ int(mt()) ^ int(kb()) ^ int(rl48()))
              & 0x7fffffff) / (num_t(int(0x7fffffff)) / num_t(int(2)))
       - num_t(int(1))) << std::endl << std::flush;
  return 0;
}

