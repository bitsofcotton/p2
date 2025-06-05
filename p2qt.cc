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
  pslip.reserve(para);
  for(int i = 0; i < para; i ++) pslip.emplace_back(pslip_t<num_t>());
  std::string s;
  int   t(0);
  num_t d(t);
  auto  MM(d);
  vector<num_t> M;
  M.resize(pslip.size(), d);
  idFeeder<num_t> in;
  // XXX: needs volatile?
  pnextcacher<num_t>(3, 1);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << (MM *= d) << ", " << std::flush;
    // N.B. M == 0 result means we better to kill some types of the
    //      jammers on the place if input isn't sparse.
    // N.B. however, this usualy only move the gulf point to after the original
    //      place in the meaning of predictors' one.
    // N.B. pnext on first call is not thread safe.
    in.next(d);
    // XXX: needs volatile?
    pnextcacher<num_t>(t + 1, 1);
    // XXX: crashes with omp (mem operation region??).
#if defined(_OPENMP)
#pragma omp parallel for schedule(static,1)
#endif
    for(int i = 0; i < M.size(); i ++)
      M[i] = pSlipJamQuad3(in.res, pslip[i].pipe, pslip[i].lastM,
        pslip[i].f0, pslip[i].f1, pslip[i].br, pslip[i].shf, pslip[i].nshf, t);
    MM = M[0];
    for(int i = 1; i < M.size(); i ++) MM += M[i];
    std::cout << (MM /= num_t(M.size()) ) << std::endl << std::flush;
    t ++;
  }
  return 0;
}

