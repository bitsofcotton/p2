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

template <typename T> static inline std::vector<T> samplerecur(const vector<T>& d, const int& interval = 1024) {
  std::vector<T> res;
  res.reserve(d.size());
  for(int i = 0; i < d.size(); i ++) {
    vector<pair<T, T> > samples;
    samples.resize(interval);
#if defined(_OPENMP)
#pragma omp parallel for schedule(static, 1)
#endif
    for(int j = 0; j < interval; j ++) {
      const auto x(T(j * 2) / T(interval - 1) - T(int(1)));
      samples[j] = make_pair(abs(plainrecur(x, i + 1) - d[i]), x);
    }
    sort(samples.begin(), samples.end());
    res.emplace_back(samples[0].second);
  }
  return res;
}

template <typename T> static inline void next(std::vector<T>& d) {
  assert(d.size() == fp.size());
  for(int i = 0; i < fp.size(); i ++) {
    auto fpn(fp[i].res[fp[i].res.size() - 1]);
    for(int i = 1; i < fpn.size(); i ++)
      fpn[fpn.size() - i] = fpn[fpn.size() - i - 1];
    fpn[0] = (d[i] + num_t(int(1))) / num_t(int(2));
    fp[i].next(fpn);
    auto work(predv0<num_t, 0>(fp[i].res.entity, string(""), fp[i].res.entity.size()));
    fq[i].next(pseudoierfscale<num_t>((d[i] - Mp[i]) / num_t(int(2)) ));
    d[i]  = pseudoerfscale<num_t>((fq[i].res[fq[i].res.size() - 1] - Mq[i]) * num_t(int(2)) );
    Mp[i] = work[0] * num_t(int(2)) - num_t(int(1));
    Mq[i] = P0maxRank<num_t>().next(fq[i].res);
    if(i + 1 < d.size()) d[i + 1] = d[i];
  }
}

template <typename T> static inline std::vector<T> nextd(vector<T>& d) {
  next<T>(d);
  auto lMp(Mp);
  auto lMq(Mq);
  auto lfp(fp);
  auto lfq(fq);
  auto dd(d);
  dd[0] = T(int(0));
  next<T>(dd);
  const auto nsr(samplerecur<T>(dd));
  std::swap(Mp, lMp);
  std::swap(Mq, lMq);
  std::swap(fp, lfp);
  std::swap(fq, lfq);
  std::vector<T> res;
  res.reserve(d.size());
  const auto sr(samplerecur<T>(d));
  assert(nsr.size() == dd.size() && sr.size() == d.size() && d.size() == dd.size());
  for(int i = 0; i < d.size(); i ++)
    res.emplace_back(abs(nsr[i]) == num_t(int(1)) ? T(int(0)) : (abs(sr[i]) == num_t(int(1)) ? num_t(int(0)) : sr[i]) );
  return res;
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
  int feed(4);
  if(argc < 2) std::cerr << argv[0] << " <stat>? <feed>? : continue with ";
  if(1 < argc) stat  = std::atoi(argv[1]);
  if(2 < argc) feed  = std::atoi(argv[2]);
  std::cerr << argv[0] << " " << stat << " " << feed << std::endl;
  assert(8 <= stat && (1 == feed || 2 == feed || 4 == feed || 8 == feed));
  {
    idFeeder<SimpleVector<num_t> > workfp(stat);
    for(int i = 0; i < stat; i ++)
      workfp.next(SimpleVector<num_t>(feed).O());
    fp.resize(1, workfp);
  }
  fq.resize(1, idFeeder<num_t>(stat));
  Mp.resize(1, num_t(int(0)));
  Mq.resize(1, num_t(int(0)));
  auto  mfp(fp);
  auto  mfq(fq);
  auto  mMp(Mp);
  auto  mMq(Mq);
  auto  d(Mp);
  auto  md(d);
  num_t M(int(0));
  std::string s;
  for(int t = 1; std::getline(std::cin, s, '\n'); t ++) {
    std::stringstream ins(s);
    ins >> d[0];
    md[0] = - d[0];
    std::cout << (M == num_t(int(0)) ? M : d[0] - M) << ", " << d[0] - M << ", " << d[0] * M << ", ";
    auto MMp(nextd<num_t>(d));
    std::swap(Mp, mMp);
    std::swap(Mq, mMq);
    std::swap(fp, mfp);
    std::swap(fq, mfq);
    auto MMm(nextd<num_t>(md));
    std::swap(Mp, mMp);
    std::swap(Mq, mMq);
    std::swap(fp, mfp);
    std::swap(fq, mfq);
    for(int i = d.size() - 1; 0 <= i; i --) {
      M = (MMp[i] == num_t(int(0)) || MMm[i] == num_t(int(0)) ? num_t(int(0)) : (MMp[i] - MMm[i] < num_t(int(0)) ? (MMp[i] < - MMm[i] ? MMp[i] : - MMm[i]) : (- MMm[i] < MMp[i] ? - MMm[i] : MMp[i]) ));
      if(abs(M) == num_t(int(1)) ) M = num_t(int(0));
      if(M != num_t(int(0))) break;
    }
    std::cout << M << std::endl << std::flush;
    if(! (t % (stat * 2))) {
      idFeeder<SimpleVector<num_t> > workfp(stat);
      for(int i = 0; i < stat; i ++)
        workfp.next(SimpleVector<num_t>(feed).O());
      fp.emplace_back(workfp);
      mfp.emplace_back(workfp);
      fq.emplace_back(idFeeder<num_t>(stat));
      mfq.emplace_back(idFeeder<num_t>(stat));
      Mp.emplace_back(num_t(int(0)));
      Mq.emplace_back(num_t(int(0)));
      mMp.emplace_back(num_t(int(0)));
      mMq.emplace_back(num_t(int(0)));
      d.emplace_back(num_t(int(0)));
      md.emplace_back(num_t(int(0)));
    }
  }
  return 0;
}

