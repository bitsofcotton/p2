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
#include <sys/resource.h>

/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
#include "../catg/lieonn.hh"
typedef myfloat num_t;
/*
#if defined(_FLOAT_BITS_)
#undef int
#endif
*/
int main(int argc, const char* argv[]) {
/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
  std::cout << std::setprecision(30);
  int method(0);
  if(argc <= 1) std::cerr << argv[0] << " <method>? : continue with ";
  if(1 < argc) method = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << method << std::endl;
  num_t d(int(0));
  while(true) {
    switch(method) {
    case 0:
      d = num_t(int(arc4random_uniform(0x80001))) / num_t(int(0x40000)) - num_t(int(1));
      break;
    default:
      assert(0 && "Should not be reached.");
    }
    std::cout << d << std::endl;
  }
  return 0;
}

