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
  idFeeder<num_t> in;
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
  shf.reserve(4);
  nshf.reserve(4);
  for(int i = 0; i < 4; i ++) {
    shf.emplace_back(i);
    nshf.emplace_back(i);
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(shf.begin(), shf.end(), engine);
    std::shuffle(nshf.begin(), nshf.end(), engine);
  }
  idFeeder<num_t> pi(3), po(3);
  std::string s;
  int   t(0);
  num_t d(t);
  auto  Mi(d);
  auto  Mo(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    auto pqt(pSlipJamQuad3(in.next(d), pipe, lastM, f0, f1, br, shf, nshf, t ++));
    std::cout << d * Mi << ", " << pqt.first * Mo << ", " << pqt.first << std::endl << std::flush;
    Mi = p0maxNext<num_t>(pi.next(d));
    Mo = p0maxNext<num_t>(po.next(pqt.first));
  }
  return 0;
}

