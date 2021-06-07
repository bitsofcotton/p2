#include <random>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

int mmt(std::mt19937& mt, bool arc4 = false, int c = 3) {
  int res(0);
  for(int i = 0; i < c; i ++)
    res = arc4 ? arc4random() : mt();
  return res;
}

int main(int argc, char* argv[]) {
  assert(4 <= argc);
  std::random_device rnd;
  std::mt19937 mt(rnd());
  int t(0);
  while(true) {
    double s(0);
    if(std::atoi(argv[3])) {
      for(int i = 0; i < std::atoi(argv[3]); i ++) {
        double r(0);
        // XXX: this is not better random, we need sometimes re rand()
        //      better to get if larger than them.
        for(int j = 0; j < std::atoi(argv[3]); j ++)
          r += double((int)(mmt(mt, std::atoi(argv[1]), std::atoi(argv[2])) %
                              0x8000000) - 0x4000000 + double(1) / double(2)) *
               double((int)(mmt(mt, std::atoi(argv[1]), std::atoi(argv[2])) %
                              0x8000000) - 0x4000000 + double(1) / double(2));
        s += r * double((int)(mmt(mt, std::atoi(argv[1]), std::atoi(argv[2])) %
               0x8000000) - 0x4000000 + double(1) / double(2));
      }
      if((t ++) % 3 == 0) {
        if(0 <= s)
          std::cout <<   pow(  s, double(1) / double(3)) << std::endl;
        else
          std::cout << - pow(- s, double(1) / double(3)) << std::endl;
      }
    } else
      std::cout <<
        double((int)(mmt(mt, std::atoi(argv[1]), std::atoi(argv[2])) %
                       0x8000000) - 0x4000000 + double(1) / double(2)) << std::endl;
  }
  return 0;
}

