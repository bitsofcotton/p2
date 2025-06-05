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

typedef struct {
  vector<idFeeder<num_t> > pipe;
  vector<vector<vector<num_t> > > lastM;
  vector<vector<idFeeder<num_t> > > f0;
  vector<vector<idFeeder<SimpleVector<num_t> > > > f1;
  vector<vector<num_t> > br;
  vector<int> shf;
  vector<int> nshf;
} pslip_t;

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
  // Construct initial instances.
  vector<pslip_t> pslip;
  {
    vector<idFeeder<num_t> > pipe;
    vector<vector<vector<num_t> > > lastM;
    vector<vector<idFeeder<num_t> > > f0;
    vector<vector<idFeeder<SimpleVector<num_t> > > > f1;
    vector<vector<num_t> > br;
    vector<int> shf;
    vector<int> nshf;
    pipe.resize(3 * 3 * 3 - 1);
    {
      vector<vector<num_t> > lM;
      vector<num_t> llM;
      llM.resize(1, num_t(int(0)));
      lM.reserve(4);
      lM.emplace_back(llM);
      lM.emplace_back(llM);
      llM.resize(6, num_t(int(0)));
      lM.emplace_back(llM);
      lM.emplace_back(llM);
      lastM.resize(27, lM);
    }
    {
      vector<idFeeder<num_t> > lf0;
      vector<idFeeder<SimpleVector<num_t> > > lf1;
      lf0.resize(6);
      lf1.resize(4);
      f0.resize(27, lf0);
      f1.resize(27, lf1);
    }
    {
      vector<num_t> lbr;
      lbr.resize(2, num_t(int(0)));
      br.resize(27, lbr);
    }
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    shf.reserve(4);
    for(int i = 0; i < 4; i ++) {
      shf.emplace_back(i);
      std::shuffle(shf.begin(), shf.end(), engine);
    }
    nshf = shf;
    pipe.resize(3 * 3 * 3 - 1);
    pslip_t ps0;
    ps0.pipe  = move(pipe);
    ps0.lastM = move(lastM);
    ps0.f0    = move(f0);
    ps0.f1    = move(f1);
    ps0.br    = move(br);
    ps0.shf   = move(shf);
    ps0.nshf  = move(nshf);
    pslip.resize(para, ps0);
    for(int j = 1; j < pslip.size(); j ++) {
      pslip[j].shf.resize(0);
      pslip[j].shf.reserve(4);
      for(int i = 0; i < 4; i ++) {
        pslip[j].shf.emplace_back(i);
        std::shuffle(pslip[j].shf.begin(), pslip[j].shf.end(), engine);
      }
      pslip[j].nshf = pslip[j].shf;
    }
  }
  // loop local variables and instances.
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

