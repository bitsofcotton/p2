#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include <stdint.h>
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;

template <typename T> static inline T pseudoerfscale(const T& x) {
  return sgn<T>(x) == T(int(0)) ? x : sgn<T>(x) * exp(- x * x);
}

template <typename T> static inline T pseudoierfscale(const T& y) {
  return sgn<T>(y) == T(int(0)) ? y : sgn<T>(y) * sqrt(abs(- log(abs(y))));
}

std::vector<num_t> Mp;
std::vector<num_t> Mq;
std::vector<idFeeder<SimpleVector<num_t> > > fp;
std::vector<idFeeder<num_t> > fq;

template <typename T> static inline T plainrecur(T x, const int& r) {
  for(int i = 0; i < r; i ++) {
    x = pseudoierfscale<T>((x - Mp[i]) / T(int(2)) );
    x = pseudoerfscale< T>((x - Mq[i]) * T(int(2)) );
  }
  return x;
}

template <typename T> static inline T samplerecur(const int& r, const T& d, const int& interval = 1024) {
  vector<pair<T, T> > samples;
  samples.resize(interval);
#if defined(_OPENMP)
#pragma omp parallel for schedule(static, 1)
#endif
  for(int i = 0; i < interval; i ++) {
    const auto x(T(i * 2) / T(interval - 1) - T(int(1)));
    samples[i] = make_pair(abs(plainrecur(x, r) - d), x);
  }
  sort(samples.begin(), samples.end());
  return samples[0].second;
}

template <typename T> static inline void next(T& d) {
  for(int i = 0; i < fp.size(); i ++) {
    auto fpn(fp[i].res[fp[i].res.size() - 1]);
    for(int i = 1; i < fpn.size(); i ++)
      fpn[fpn.size() - i] = fpn[fpn.size() - i - 1];
    fpn[0] = (d + num_t(int(1))) / num_t(int(2));
    fp[i].next(fpn);
    auto work(predv0<num_t, 0>(fp[i].res.entity, string(""), fp[i].res.entity.size()));
    fq[i].next(pseudoierfscale<num_t>((d - Mp[i]) / num_t(int(2)) ));
    d = pseudoerfscale<num_t>((fq[i].res[fq[i].res.size() - 1] - Mq[i]) * num_t(int(2)) );
    Mp[i] = work[0] * num_t(int(2)) - num_t(int(1));
    Mq[i] = P0maxRank<num_t>().next(fq[i].res);
  }
}

template <typename T> static inline T nextd(T& d) {
  next<T>(d);
  auto lMp(Mp);
  auto lMq(Mq);
  auto lfp(fp);
  auto lfq(fq);
  T    dd(int(0));
  next<T>(dd);
  const auto flag(abs(samplerecur<T>(Mp.size(), dd)) == T(int(1)) );
  std::swap(Mp, lMp);
  std::swap(Mq, lMq);
  std::swap(fp, lfp);
  std::swap(fq, lfq);
  auto M(flag ? T(int(0)) : samplerecur<T>(Mp.size(), d));
  return abs(M) == num_t(int(1)) ? num_t(int(0)) : M;
}


#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  int stat(80);
  int recur(6);
  int feed(4);
  if(argc < 2) std::cerr << argv[0] << " <stat>? <recur>? <feed>? : continue with ";
  if(1 < argc) stat  = std::atoi(argv[1]);
  if(2 < argc) recur = std::atoi(argv[2]);
  if(3 < argc) feed  = std::atoi(argv[3]);
  std::cerr << argv[0] << " " << stat << " " << recur << " " << feed << std::endl;
  assert(8 <= stat && 1 <= recur && 1 <= feed);
  {
    idFeeder<SimpleVector<num_t> > workfp(stat);
    for(int i = 0; i < stat; i ++)
      workfp.next(SimpleVector<num_t>(feed).O());
    fp.resize(recur, workfp);
  }
  fq.resize(recur, idFeeder<num_t>(stat));
  Mp.resize(recur, num_t(int(0)));
  Mq.resize(recur, num_t(int(0)));
  assert(fp.size() == fq.size() && fq.size() == Mp.size() && Mp.size() == Mq.size());
  num_t d(int(0));
  auto  bd(d);
  auto  bmd(d);
  auto  M(d);
  auto  Mp(d);
  auto  Mm(d);
  std::string s;
  auto  mMp(Mp);
  auto  mMq(Mq);
  auto  mfp(fp);
  auto  mfq(fq);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << (M == num_t(int(0)) ? M : d - M) << ", " << d - M << ", " << d * M << ", ";
    auto md(- d);
    Mp = nextd<num_t>(d);
    std::swap(Mp, mMp);
    std::swap(Mq, mMq);
    std::swap(fp, mfp);
    std::swap(fq, mfq);
    Mm = nextd<num_t>(md);
    std::swap(Mp, mMp);
    std::swap(Mq, mMq);
    std::swap(fp, mfp);
    std::swap(fq, mfq);
    // std::cout << Mp << ", " << Mm << ", " << (M = (Mp == num_t(int(0)) || Mm == num_t(int(0)) ? num_t(int(0)) : (Mp - Mm < num_t(int(0)) ? (Mp < - Mm ? Mp : - Mm) : (- Mm < Mp ? Mp : - Mm)) )) << ", " << d - bd << ", " << md - bmd << std::endl << std::flush;
    std::cout << Mp << ", " << Mm << ", " << (M = (Mp == num_t(int(0)) || Mm == num_t(int(0)) ? num_t(int(0)) : (Mp - Mm < num_t(int(0)) ? (Mp < - Mm ? - Mm : Mp) : (- Mm < Mp ? - Mm : Mp)) )) << ", " << d - bd << ", " << md - bmd << std::endl << std::flush;
    bd  = d;
    bmd = md;
  }
  return 0;
}

