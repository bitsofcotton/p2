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
  const auto stat(1331);
  const auto var(10);
        int  step(1);
  if(argc < 2)
    std::cerr << "catgp <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with catgp " << step << std::endl;
  shrinkMatrix<num_t, P012L<num_t, linearFeeder<num_t, idFeeder<num_t> > > > p(P012L<num_t, linearFeeder<num_t, idFeeder<num_t> > >(stat, var, abs(step)), abs(step));
  shrinkMatrix<num_t, P012L<num_t, arctanFeeder<num_t, idFeeder<num_t> > > > q(P012L<num_t, arctanFeeder<num_t, idFeeder<num_t> > >(stat, var, abs(step)), abs(step));
  std::string s;
  num_t d(0);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    std::cout << D << ", " << (M = step < 0 ? q.next(d) : p.next(d)) << std::endl << std::flush;
  }
  return 0;
}

