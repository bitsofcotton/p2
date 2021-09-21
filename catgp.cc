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

/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
#include "../catg/lieonn.hh"
typedef myfloat num_t;
#include "../catg/catg.hh"
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
  // N.B. R^4 using index, so without index with symmetrize, R^6.
  //      we use const twice, so at last we use only R^5.
  const auto stat(6 * 6 * 6);
  const auto var(5);
        int  step(1);
  if(argc < 2)
    std::cerr << "catgp <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with catgp " << step << std::endl;
  P012L<num_t, linearFeeder<num_t, idFeeder<num_t> > > p(abs(stat) + abs(step), var, abs(step));
  P012L<num_t, arctanFeeder<num_t, idFeeder<num_t> > > q(abs(stat) + abs(step), var, abs(step));
  std::string s;
  num_t d(0);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << (step < 0 ? q.next(d) : p.next(d)) << std::endl << std::flush;
  }
  return 0;
}

