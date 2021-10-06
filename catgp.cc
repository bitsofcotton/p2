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
  // N.B. we need original and pair-wise to denoise them.
  plin_t  p(plin_pt( stat * abs(step), var, abs(step)), abs(step));
  patan_t q(patan_pt(stat * abs(step), var, abs(step)), abs(step));
  std::string s;
  num_t d(0);
  std::vector<num_t> M;
  M.resize(abs(step), num_t(int(0)));
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M[0]);
    for(int i = 0; i < M.size() - 1; i ++) M[i] = move(M[i + 1]);
    std::cout << D << ", " << (M[M.size() - 1] = step < 0 ? q.next(d) : p.next(d)) << std::endl << std::flush;
    if(! isfinite(M[M.size() - 1])) M[M.size() - 1] = num_t(int(0));
  }
  return 0;
}

