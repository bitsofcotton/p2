#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <assert.h>

#if !defined(_FLOAT_BITS_)
  #include <complex>
  #include <cmath>
  using namespace std;
  typedef long double num_t;
  #include <limits>
#else
  #include "ifloat.hh"
  template <typename T> using complex = Complex<T>;
# if _FLOAT_BITS_ == 32
    typedef uint32_t myuint;
    typedef int32_t  myint;
    typedef SimpleFloat<myuint, uint64_t, 32, int64_t> num_t;
    #define mybits 32
# elif _FLOAT_BITS_ == 64
    typedef uint64_t myuint;
    typedef int64_t  myint;
    typedef SimpleFloat<myuint, DUInt<myuint, 64>, 64, int64_t> num_t;
    #define mybits 64
# elif _FLOAT_BITS_ == 128
    typedef DUInt<uint64_t, 64> uint128_t;
    typedef Signed<uint128_t, 128> int128_t;
    typedef uint128_t myuint;
    typedef int128_t  myint;
    typedef SimpleFloat<myuint, DUInt<myuint, 128>, 128, int64_t> num_t;
    #define mybits 128
# else
#   error cannot handle float
# endif
#endif

#include "../p1/simplelin.hh"
#include "../p0/p0.hh"
#include "../p1/p1.hh"
#include "../catg/decompose.hh"
#include "../catg/catg.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  int  vrange(- 12);
  int  ignore(- 4);
  int  eslen(0);
  int  stat(2000);
  int  slide(1500);
  auto intensity(- num_t(1) / num_t(2));
  if(argc < 3) {
    std::cerr << "p012 <variable> <ignore> <extra> <stat> <slide> <cut>?" << std::endl;
    std::cerr << "continue with p012 " << vrange << " " << ignore << " " << eslen << " " << stat << " " << slide << " " << intensity << std::endl << std::flush;
  } else {
    vrange = std::atoi(argv[1]);
    ignore = std::atoi(argv[2]);
    if(3 < argc) eslen = std::atoi(argv[3]);
    if(4 < argc) stat  = std::atoi(argv[4]);
    if(5 < argc) slide = std::atoi(argv[5]);
    if(6 < argc) intensity = std::atof(argv[6]);
  }
  const auto origin(vrange < 0 ? atan2(num_t(1), num_t(1)) * num_t(4) + num_t(1) : num_t(0));
  assert(0 <= eslen);
  P0B<num_t> p(abs(vrange));
  P1I<num_t> q(eslen + abs(ignore), abs(vrange));
  SimpleVector<num_t> v(abs(vrange));
  Decompose<num_t>    dec(v.size());
  std::vector<SimpleVector<num_t> > va;
  std::vector<SimpleVector<num_t> > pp;
  va.reserve(stat);
  std::string s;
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  s4(d);
  auto  s5(d);
  auto  s6(d);
  int   tp(0);
  auto  tm(tp);
  int   t(- 1);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    const auto delta(vrange < 0 ? atan(d - bd) : d - bd);
    if(d != bd) {
      if(bd != num_t(0) && M != num_t(0)) {
        tp ++; tm ++;
        s0 += vrange < 0 ? d - bd - tan(M) : delta - M;
        s1 += delta * M;
        s2 += delta * M * num_t(tp - tm);
        s3 += (d - bd) * M;
        s4 += (d - bd) * M * num_t(tp - tm);
        s5 += delta * M * num_t(tp);
        s6 -= delta * M * num_t(tm);
      } else if(M == num_t(0)) std::cerr << "!" << std::flush;
      M = p.next(delta) + q.next(delta, - ignore, origin);
      if(t ++ < v.size()) {
        v[t % v.size()] = d;
        M /= num_t(2);
        continue;
      }
      v[v.size() - 1] = d;
      const auto vvv(dec.next(v));
      va.emplace_back(vvv / sqrt(vvv.dot(vvv)));
      for(int i = 0; i < v.size() - 1; i ++)
        v[i] = v[i + 1];
      v[v.size() - 2] = d;
      if(stat <= va.size()) {
        const auto cat(crush<num_t>(va, v.size(), intensity, - 1, true));
        pp = std::vector<SimpleVector<num_t> >();
        pp.reserve(cat.size());
        for(int i = 0; i < cat.size(); i ++) {
          pp.emplace_back(cat[i].first[0].first);
          for(int j = 1; j < cat[i].first.size(); j ++)
            pp[i] += cat[i].first[j].first;
          pp[i] /= sqrt(pp[i].dot(pp[i]));
        }
        const auto va0(va);
        va = std::vector<SimpleVector<num_t> >();
        va.reserve(va0.size());
        for(int i = 0; i < slide; i ++)
          va.emplace_back(va0[i - slide + va0.size()]);
      }
      num_t MM(0);
      auto  Mn(MM);
      for(int i = 0; i < pp.size(); i ++) {
        const auto& p(pp[i]);
        const auto  vdp(dec.next(v).dot(p));
        const auto  ldlt(p[p.size() - 1] - p[p.size() - 2]);
        if(! isfinite(vdp)) continue;
        if(MM <= abs(vdp) && ldlt != num_t(0)) {
          MM = abs(vdp);
          Mn = ldlt * vdp;
        }
      }
      M = (M + Mn) / num_t(3);
      if(! isfinite(M) || isnan(M)) M = num_t(0);
      if(0 < s5) s5 = num_t(tp = 0);
      if(0 < s6) s6 = num_t(tm = 0);
    }
    std::cout << M << ", " << (tp - tm) << ", " << s0 << ", " << s1 << ", " << s2 << ", " << s3 << ", " << s4 << std::endl << std::flush;
  }
  return 0;
}

