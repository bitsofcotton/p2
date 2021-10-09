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
/*
  const auto stat(7 * 7 * 7);
  const auto var(7);
*/
  const auto stat(3 * 3 * 3);
  const auto var(3);
        int  step(1);
  if(argc < 2)
    std::cerr << "catgp <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with catgp " << step << std::endl;
  // N.B. we need to predict with per 2^k ranges.
  //      the only one predictor with large enough k should work ok, but
  //      we emphasis the range near the point now.
  //      this is because the original matrix row average to be
  //      near the 0 vector nor noise only case.
  //      in that case, if original matrix size isn't 2^k, we can see
  //      some vector remains as a categorizable ones.
  //      the categorizer only categorizes them with var dimension, so
  //      predictor should returns obscure result, but it is a little
  //      continuous compared to original ones.
  vector<plin_t>  p;
  vector<patan_t> q;
  if(step < 0) {
    q.reserve(abs(step));
    for(int i = 0; i < abs(step); i ++) {
      const int ss(pow(num_t(int(2)), num_t(int(i))));
      q.emplace_back(patan_t(patan_pt(stat * ss, var, ss), ss));
    }
  } else {
    p.reserve(abs(step));
    for(int i = 0; i < abs(step); i ++) {
      const int ss(pow(num_t(int(2)), num_t(int(i))));
      p.emplace_back(plin_t(plin_pt(stat * ss, var, ss), ss));
    }
  }
  std::string s;
  num_t d(0);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    M = num_t(int(0));
    for(int i = 0; i < (step < 0 ? q.size() : p.size()); i ++)
      M += step < 0 ? q[i].next(d) : p[i].next(d);
    std::cout << D << ", " << M << std::endl << std::flush;
  }
  return 0;
}

