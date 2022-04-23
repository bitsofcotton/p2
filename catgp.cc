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
#include "../catg/catg.hh"
typedef P012L<num_t, idFeeder<num_t> > plin_t;
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
  int var(- 3);
  if(argc < 2) std::cerr << argv[0] << " <var>? : continue with ";
  if(1 < argc) var = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << var << std::endl;
  shrinkMatrix<num_t, plin_t> p;
  plin_t q;
  if(var < 0)
    q = plin_t(- var * var * var, - var);
  else
    p = shrinkMatrix<num_t, plin_t>(plin_t(var * var * var * var, var, var), var);
  std::string s;
  int   t;
  num_t d(t ^= t);
  auto  dd(d);
  auto  Mx(d);
  auto  M(d);
  auto  S(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    dd += d;
    if(++ t < 2 * var * var) {
      std::cout << D << ", " << M << ", " << (S += D) << std::endl << std::flush;
      continue;
    }
    Mx = max(Mx, abs(dd) * num_t(int(2)));
    std::cout << D << ", " << (M = max(- Mx, min(Mx, var < 0 ? q.next(dd) : p.next(dd) )) ) << ", " << (S += D) << std::endl << std::flush;
    dd = num_t(t ^= t);
  }
  return 0;
}

