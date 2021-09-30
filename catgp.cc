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
typedef P012L<num_t, linearFeeder<num_t, idFeeder<num_t> > > plin_pt;
typedef P012L<num_t, deltaFeeder<num_t, arctanFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > > patan_pt;
typedef shrinkMatrix<num_t, plin_pt>  plin_t;
typedef shrinkMatrix<num_t, patan_pt> patan_t;
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
  // N.B. we need original and pair-wise to denoise them.
  std::vector<plin_t>  p;
  std::vector<patan_t> q;
  p.reserve(2);
  q.reserve(2);
  for(int i = abs(step) - 1; i < abs(step) + 1; i ++)
    if(step < 0)
      q.emplace_back(patan_t(patan_pt(stat, var, int(pow(2, abs(i)))), int(pow(2, abs(i)))));
    else
      p.emplace_back(plin_t( plin_pt( stat, var, int(pow(2, abs(i)))), int(pow(2, abs(i)))));
  std::string s;
  num_t d(0);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    M = num_t(0);
    for(int i = 0; i < (step < 0 ? q.size() : p.size()); i ++)
      M += step < 0 ? q[i].next(d) : p[i].next(d);
    std::cout << D << ", " << M << std::endl << std::flush;
  }
  return 0;
}

