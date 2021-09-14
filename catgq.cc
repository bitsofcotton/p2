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
  inline P0123(const int& recur) { 
    sh.resize(abs(recur), T(0));
    Mh.resize(sh.size(), T(0));
    mh.resize(sh.size(), T(0));
    if((this->recur = recur) < 0) {
      p1.resize(sh.size(), P012L<T, arctanFeeder<T, idFeeder<T> > >(pow(6, 4), 5));
      q1.resize(sh.size(), P0<T, arctanFeeder<T, idFeeder<T> > >(25));
    } else {
      p0.resize(sh.size(), P012L<T, linearFeeder<T, idFeeder<T> > >(pow(6, 4), 5));
      q0.resize(sh.size(), P0<T, linearFeeder<T, idFeeder<T> > >(25));
    }
    bM = S = T(t ^= t);
  }
  inline ~P0123() { ; }
  inline T next(const T& in, const T& d) {
    for(int i = 1; i < sh.size(); i ++) sh[i - 1] = move(sh[i]);
    for(int i = 1; i < Mh.size(); i ++) Mh[i - 1] = move(Mh[i]);
    for(int i = 1; i < mh.size(); i ++) mh[i - 1] = move(mh[i]);
    sh[sh.size() - 1] = in;
    Mh[Mh.size() - 1] = (recur < 0 ? p1[t % p1.size()].next(in - sh[0]) : p0[t % p0.size()].next(in - sh[0])) + in;
    mh[mh.size() - 1] = T(0);
    for(int i = 0; i < Mh.size(); i ++)
      mh[mh.size() - 1] += Mh[i];
    mh[mh.size() - 1] /= T(Mh.size());
    S += d * bM < T(0) ? - sqrt(abs(d * bM)) : sqrt(abs(d * bM));
    const auto resq(recur < 0 ? q1[t % q1.size()].next(S) : q0[t % q0.size()].next(S));
    bM = T(0);
    T denom(0);
    for(int i = 0; i < mh.size(); i ++) {
      bM += (mh[i] - in) / T(mh.size() - i);
      denom += T(1) / T(mh.size() - i);
    }
    bM /= denom;
    t ++;
    return bM < T(0) ? - resq : resq;
  }
  vector<T> sh;
  vector<T> Mh;
  vector<T> mh;
  T   bM;
  T   S;
  int recur;
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
  int  percent(95);
  if(argc < 2)
    std::cerr << "catgq <percent>?" << std::endl;
  if(1 < argc) percent = std::atoi(argv[1]);
  // N.B. wikipedia Condorcet's jury theorem.
  //   (2 - sqrt(2) - .5) * c1 + .5 ~ percent.
  //   c1 = sqrt(2n + 1) / sqrt(pi) * (1 + 1/ 16n^2 + O(n^-3))
  // c1 = (percent - .5) / (1.5 - sqrt(2))
  //    ~ sqrt(2n + 1) / sqrt(pi)
  // <=> n == (((percent - .5) / (1.5 - sqrt(2)))^2 * pi - 1) / 2
  const auto n(max(int((pow((num_t(abs(percent)) / num_t(100) - num_t(1) / num_t(2)) / (num_t(3) / num_t(2) - sqrt(num_t(2))), num_t(2)) * atan(num_t(1)) * num_t(4) - num_t(1)) / num_t(2)), int(1)));
  std::cerr << "continue with catgq " << percent << "\% uses: " << n << std::endl;
  std::vector<P0123<num_t> > p;
  p.reserve(n);
  for(int i = 2; i < n + 2; i ++)
    p.emplace_back(P0123<num_t>(percent < 0 ? - i :  i));
  std::string s;
  num_t d(0);
  auto  D(d);
  auto  S(d);
  auto  SS(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D  = d * M;
    M  = p[0].next(S += d, d);
    for(int i = 1; i < p.size(); i ++)
      M += p[i].next(S, d);
    std::cout << D << ", " << (M /= num_t(p.size())) << ", " << d << ", " << S << ", " << (SS += D) << std::endl << std::flush;
  }
  return 0;
}

