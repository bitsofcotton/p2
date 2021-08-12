#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>

#include "../catg/lieonn.hh"
typedef myfloat num_t;

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::string s;
  num_t d(0);
  auto  bbd(d);
  auto  D(d);
  num_t y(1);
  auto  bby(y);
  auto  z(y);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    const auto by(y);
    const auto bz(z);
    std::stringstream ins(s);
    ins >> d;
    // y++ * d++ = (d++ - bd++ - bbd++) / d++ * y * d++
    //   = (d++ - bd++ - bbd++) * y
    y  *= (z = (d - bd - bbd) / d) / bz;
    // (d * y + bd * by) - (bd * by - bbd * bby)
    // == (d - bd - bbd) * bby + bd * by - bd * by + bbd * bby
    // == (d - bd) * bby
    // OK:
    std::cout << (d * y + bd * by) << std::endl;
    // std::cout << (d - bd - bbd) * bby + bd * by << std::endl;
    // NG:
    // std::cout << (D += (d - bd) * bby) << std::endl;
    // test:
    // std::cout << (d - bd - bbd) * bby << ", " << d * y << std::endl;
    bbd = bd;
    bby = by;
  }
  return 0;
}

