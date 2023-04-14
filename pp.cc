#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <assert.h>
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  std::string s;
  num_t d(int(0));
  auto  M(d);
  idFeeder<num_t> v(63);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    const auto& res(v.next(d));
    M = num_t(int(0));
    if(v.full)
      for(int i = 5; i < res.size(); i ++)
        M += Prange<num_t>(i).next(res.subVector(res.size() - i, i));
    std::cout << (M /= num_t(res.size() - 5)) << std::endl << std::flush;
  }
  return 0;
}

