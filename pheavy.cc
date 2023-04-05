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
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include <p0/lieonn.hh>
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
  std::cerr << argv[0] << std::endl;
  // N.B. we make exhaust of the resources to continue prediction.
  //      this causes if the jammer exists on the input stream,
  //      exhaust of the memory nor calculation time causes
  //      some of the glitch to produce input stream.
  //      or, the system should crashes with remain no used memory.
  num_t d(int(0));
  auto  M(d);
  SimpleVector<num_t> v;
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    v.entity.emplace_back(d);
    std::cout << d * M << ", ";
    std::cout << (M = v.size() < 5 ? num_t(int(0)) : Prange<num_t>(v.size()).next(v)) << std::endl << std::flush;
  }
  return 0;
}

