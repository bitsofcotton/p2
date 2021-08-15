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
  num_t y(1);
  auto  bby(y);
  auto  z(y);
  int   t(0);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    const auto by(y);
    const auto bz(z);
    std::stringstream ins(s);
    ins >> d;
    // y * d = (d - bd - bbd) / d * y * d
    //   = (d - bd - bbd) * y
    y  *= (z = (d - bd - bbd) / d) / bz;
    // (-1)^n * ((d * y - bd * by) - -(bd * by - bbd * bby))
    // == (-1)^n * ((d - bd + bbd) * bby - bbd * bby)
    // == (-1)^n * (d - bd) * bby
    if(bbd != num_t(0))
      std::cout << num_t((t ++) & 1 ? 1 : - 1) * (d * y - bd * by) << std::endl;
    else
      std::cout << "0, 0" << std::endl;
    bbd = bd;
    bby = by;
  }
  return 0;
}

