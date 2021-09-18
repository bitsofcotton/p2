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
  inline P23(const int& stat) { 
    assert(0 < stat);
    sh.resize(stat, T(0));
    Mh.resize(sh.size(), T(0));
    mh.resize(sh.size(), T(0));
    p = P012L<T, feeder>(6 * 6 * 6, 5);
  }
  inline ~P23() { ; }
  inline T next(const T& in) {
    T res(0);
    for(int i = 1; i < sh.size(); i ++) sh[i - 1] = move(sh[i]);
    for(int i = 1; i < Mh.size(); i ++) Mh[i - 1] = move(Mh[i]);
    for(int i = 1; i < mh.size(); i ++) mh[i - 1] = move(mh[i]);
    Mh[Mh.size() - 1] = p.next(in - sh[0]) + (sh[sh.size() - 1] = in);
    T denom(0);
    for(int i = 0; i < Mh.size(); i ++) {
      res += (Mh[i] - in) / T(i + 1);
      denom += T(1) / T(i + 1);
    }
    mh[mh.size() - 1] = res /= denom;
    for(int i = 0; i < mh.size() - 1; i ++)
      if(T(0) < mh[i] * (in - sh[i])) mh[i] = T(0);
      else res += mh[i];
    return res;
  }
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
  int  stat(- 3);
  if(argc < 2)
    std::cerr << "catgq <stat>?" << std::endl;
  if(1 < argc) stat = std::atoi(argv[1]);
  std::cerr << "continue with catgq " << stat << std::endl;
  P23<num_t, linearFeeder<num_t, idFeeder<num_t> > > p(abs(stat));
  P23<num_t, arctanFeeder<num_t, idFeeder<num_t> > > q(abs(stat));
  std::string s;
  num_t d(0);
  auto  S(d);
  auto  SS(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    M = stat < 0 ? q.next(S += d) : p.next(S += d);
    std::cout << D << ", " << M << ", " << d << ", " << S << ", " << (SS += D) << std::endl << std::flush;
  }
  return 0;
}

