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

template <typename T, typename feeder> class P23 {
public:
  inline P23() { ; }
  inline P23(const int& msize) { 
    assert(0 < msize);
    sh.resize(msize, T(t ^= t));
    Mh.resize(sh.size(), T(0));
    mh.resize(sh.size(), T(0));
    p = P012L<T, feeder>(6 * 6 * 6, 5);
  }
  inline ~P23() { ; }
  inline T next(const T& in) {
    T res(0);
    for(int i = 1; i < sh.size(); i ++) sh[i - 1] = move(sh[i]);
    sh[sh.size() - 1] = in;
    if(t ++ < sh.size()) return T(0);
    for(int i = 1; i < Mh.size(); i ++) Mh[i - 1] = move(Mh[i]);
    for(int i = 1; i < mh.size(); i ++) mh[i - 1] = move(mh[i]);
    const auto nxt(p.next(in - sh[0]));
    Mh[Mh.size() - 1] = nxt == T(0) ? T(0) : nxt + in;
    T denom(0);
    for(int i = 0; i < Mh.size(); i ++)
      if(Mh[i] != T(0)) {
        res += (Mh[i] - in) / T(i + 1);
        denom += T(1) / T(i + 1);
      }
    mh[mh.size() - 1] = denom == T(0) ? T(0) : res /= denom;
    for(int i = 0; i < mh.size() - 1; i ++)
      if(T(0) < mh[i] * (in - sh[i])) mh[i] = T(0);
      else res += mh[i];
    return res;
  }
  int t;
  vector<T> sh;
  vector<T> Mh;
  vector<T> mh;
  P012L<T, feeder> p;
};

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
  // N.B. original matrix size depends periods.
  int  msize(- 3);
  // N.B. entropy collection, if original is state period less, >0,
  //      otherwise, <0.
  int  collect(1);
  if(argc < 2)
    std::cerr << "catgq <msize>? <collect>?" << std::endl;
  if(1 < argc) msize   = std::atoi(argv[1]);
  if(2 < argc) collect = std::atoi(argv[2]);
  std::cerr << "continue with catgq " << msize << " " << collect << std::endl;
  P23<num_t, linearFeeder<num_t, idFeeder<num_t> > > p(abs(msize));
  P23<num_t, arctanFeeder<num_t, idFeeder<num_t> > > q(abs(msize));
  std::string s;
  num_t d(0);
  auto  D(d);
  auto  S(d);
  auto  SS(d);
  auto  M(d);
  int   t(0);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D += d;
    if(! ((t ++) % abs(collect))) {
      d = D;
      const auto E(d * M);
      M = msize < 0 ? q.next(S += d) : p.next(S += d);
      std::cout << E << ", " << M << ", " << d << ", " << S << ", " << (SS += E) << std::endl << std::flush;
      D = num_t(t ^= t);
    }
  }
  return 0;
}

