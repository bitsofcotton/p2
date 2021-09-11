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
    Mh.resize(abs(recur), T(0));
    mh.resize(abs(recur), T(0));
    if((this->recur = recur) < 0) {
      p1 = P012L<T, arctanFeeder<T, idFeeder<T> > >(625 * 2, 5);
      q1 = P0<T, arctanFeeder<T, sumFeeder<T, idFeeder<T> > > >(25);
    } else {
      p0 = P012L<T, linearFeeder<T, idFeeder<T> > >(625 * 2, 5);
      q0 = P0<T, linearFeeder<T, sumFeeder<T, idFeeder<T> > > >(25);
    }
  }
  inline ~P0123() { ; }
  inline T next(const T& in, const T& d) {
    for(int i = 1; i < sh.size(); i ++) sh[i - 1] = move(sh[i]);
    sh[sh.size() - 1] = in;
    const auto resq(recur < 0 ? q1.next(d * bM) : q0.next(d * bM));
    for(int i = 1; i < Mh.size(); i ++) Mh[i - 1] = move(Mh[i]);
    Mh[Mh.size() - 1] = recur < 0 ? p1.next(in - sh[0]) : p0.next(in - sh[0]);
    for(int i = 1; i < mh.size(); i ++) mh[i - 1] = move(mh[i]);
    mh[mh.size() - 1] = T(0);
    for(int i = 0; i < Mh.size(); i ++)
      mh[mh.size() - 1] += Mh[i];
    mh[mh.size() - 1] /= T(Mh.size());
    bM = T(0);
    T denom(0);
    for(int i = 0; i < mh.size(); i ++) {
      bM += (mh[i] - in) / T(mh.size() - i);
      denom += T(1) / T(mh.size() - i);
    }
    return resq * (bM /= denom);
  }
  vector<T> sh;
  vector<T> Mh;
  vector<T> mh;
  T   bM;
  int recur;
  P012L<T, linearFeeder<T, idFeeder<T> > > p0;
  P012L<T, arctanFeeder<T, idFeeder<T> > > p1;
  P0<T, linearFeeder<T, sumFeeder<T, idFeeder<T> > > > q0;
  P0<T, arctanFeeder<T, sumFeeder<T, idFeeder<T> > > > q1;
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
  // N.B. wikipedia 陪審員定理
  //   (2 - sqrt(2) - .5) * c1 + .5 == percent.
  //   c1 = sqrt(2n + 1) / sqrt(pi) * (1 + 1/ 16n^2 + O(n^-3))
  // c1 = (percent - .5) / (1.5 - sqrt(2))
  //    ~ sqrt(2n + 1) / sqrt(pi)
  // <=> n == (((percent - .5) / (1.5 - sqrt(2)))^2 * pi - 1) / 2
  const int n((pow((num_t(abs(percent)) / num_t(100) - num_t(1) / num_t(2)) / (num_t(3) / num_t(2) - sqrt(num_t(2))), num_t(2)) * atan(num_t(1)) * num_t(4) - num_t(1)) / num_t(2));
  std::cerr << "continue with catgq " << percent << "%% uses: " << n << std::endl;
  std::vector<P0123<num_t> > p;
  p.reserve(n);
  for(int i = 2; i < n + 2; i ++)
    p.emplace_back(P0123<num_t>(percent < 0 ? - i : i));
  std::string s;
  num_t d(0);
  auto  D(d);
  auto  S(d);
  auto  M(d);
  auto  SS(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D  = d * M;
    M = num_t(0);
    for(int i = 0; i < p.size(); i ++)
      M += p[i].next(S += d, d);
    std::cout << D << ", " << M << ", " << d << ", " << S << ", " << (SS += D) << std::endl << std::flush;
  }
  return 0;
}

