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
#include "../p0/p0.hh"

template <typename T> class P0123 {
public:
  inline P0123() { ; }
  inline P0123(const int& stat) { 
    sh.resize(abs(stat), T(0));
    Mh.resize(sh.size(), T(0));
    mh.resize(sh.size(), T(0));
    if((this->stat = stat) < 0) {
      p1.resize(sh.size() - 1, P012L<T, arctanFeeder<T, idFeeder<T> > >(6 * 6 * 6, 5));
      q1.resize(sh.size() - 1, P0<T, arctanFeeder<T, idFeeder<T> > >(25));
    } else {
      p0.resize(sh.size() - 1, P012L<T, linearFeeder<T, idFeeder<T> > >(6 * 6 * 6, 5));
      q0.resize(sh.size() - 1, P0<T, linearFeeder<T, idFeeder<T> > >(25));
    }
    bM = S = T(t ^= t);
  }
  inline ~P0123() { ; }
  inline T next(const T& in, const T& d) {
    for(int i = 1; i < sh.size(); i ++) sh[i - 1] = move(sh[i]);
    for(int i = 1; i < Mh.size(); i ++) Mh[i - 1] = move(Mh[i]);
    for(int i = 1; i < mh.size(); i ++) mh[i - 1] = move(mh[i]);
    sh[sh.size() - 1] = in;
    Mh[Mh.size() - 1] = (stat < 0 ? p1[t % p1.size()].next(in - sh[0]) : p0[t % p0.size()].next(in - sh[0])) + in;
    mh[mh.size() - 1] = T(0);
    for(int i = 0; i < Mh.size(); i ++)
      mh[mh.size() - 1] += Mh[i];
    mh[mh.size() - 1] /= T(Mh.size());
    if(t ++ < abs(stat) * 6 * 6 * 6) return T(0);
    S += d * bM < T(0) ? - sqrt(abs(d * bM)) : sqrt(abs(d * bM));
    const auto resq(stat < 0 ? q1[t % q1.size()].next(S) : q0[t % q0.size()].next(S));
    bM = T(0);
    T denom(0);
    for(int i = 0; i < mh.size(); i ++) {
      bM += (mh[i] - in) / T(mh.size() - i);
      denom += T(1) / T(mh.size() - i);
    }
    bM /= denom;
    return bM < T(0) ? - resq : resq;
  }
  vector<T> sh;
  vector<T> Mh;
  vector<T> mh;
  T   bM;
  T   S;
  int stat;
  int t;
  vector<P012L<T, linearFeeder<T, idFeeder<T> > > > p0;
  vector<P012L<T, arctanFeeder<T, idFeeder<T> > > > p1;
  vector<P0<T, linearFeeder<T, idFeeder<T> > > > q0;
  vector<P0<T, arctanFeeder<T, idFeeder<T> > > > q1;
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
  int  stat(- 3);
  if(argc < 2)
    std::cerr << "catgq <stat>?" << std::endl;
  if(1 < argc) stat = std::atoi(argv[1]);
  std::cerr << "continue with catgq " << stat << std::endl;
  P0123<num_t> p(stat);
  std::string s;
  num_t d(0);
  auto  S(d);
  auto  SS(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    M = p.next(S += d, d);
    std::cout << D << ", " << M << ", " << d << ", " << S << ", " << (SS += D) << std::endl << std::flush;
  }
  return 0;
}

