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
#include <random>
#include <sys/resource.h>

/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
#include "lieonn.hh"
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
  int para(1);
  if(argc < 2) std::cerr << argv[0] << " <para>? : continue with ";
  if(1 < argc) para = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << para << std::endl;
  assert(0 < para);
  vector<pslip_t<num_t> > pslip;
  pslip.reserve(para *= 4);
  for(int i = 0; i < para; i ++) pslip.emplace_back(pslip_t<num_t>());
  std::string s;
  int   t(0);
  num_t d(t);
  vector<num_t> M;
  idFeeder<num_t> in;
  M.resize(4, d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    for(int i = 0; i < M.size(); i ++) std::cout << (M[i] *= d) << ", ";
    std::cout << std::flush;
    // N.B. M == 0 result means we better to kill some types of the
    //      jammers on the place if input isn't sparse.
    // N.B. however, this usualy only move the gulf point to after the original
    //      place in the meaning of predictors' one.
    // N.B. pSlipJamQuad3 each first call is not thread safe.
    M = pSlipJam443<num_t>(in.next(d), pslip, t ++);
    for(int i = 0; i < M.size(); i ++) std::cout << M[i] << ", ";
    std::cout << d << std::endl << std::flush;
  }
  return 0;
}

