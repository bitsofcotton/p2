#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <assert.h>

#if !defined(_FLOAT_BITS_)
  #include <complex>
  #include <cmath>
  using namespace std;
  typedef long double num_t;
#else
  #include "ifloat.hh"
  template <typename T> using complex = Complex<T>;
# if _FLOAT_BITS_ == 8
    typedef uint8_t myuint;
    typedef int8_t  myint;
    typedef SimpleFloat<myuint, uint16_t, 8, int64_t> num_t;
    #define mybits 8
# elif _FLOAT_BITS_ == 16
    typedef uint16_t myuint;
    typedef int16_t  myint;
    typedef SimpleFloat<myuint, uint32_t, 16, int64_t> num_t;
    #define mybits 16
# elif _FLOAT_BITS_ == 32
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
# elif _FLOAT_BITS_ == 256
    typedef DUInt<uint64_t, 64> uint128_t;
    typedef DUInt<uint128_t, 128> uint256_t;
    typedef Signed<uint256_t, 128> int256_t;
    typedef uint256_t myuint;
    typedef int256_t  myint;
    typedef SimpleFloat<myuint, DUInt<myuint, 256>, 256, int64_t> num_t;
    #define mybits 256
# else
#   error cannot handle float
# endif
#endif

#include "../catg/simplelin.hh"
#include "../catg/p0.hh"
#include "../catg/decompose.hh"
#include "../catg/catg.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::string s;
  assert(3 < argc);
  const auto  range(std::atoi(argv[1]));
  const num_t rslide(std::atof(argv[2]));
  const auto  intensity(- num_t(1) / num_t(2));
  std::vector<P012L<num_t> > p;
  for(int i = 0; i < argc; i ++)
    p.emplace_back(P012L<num_t>(abs(range), std::atoi(argv[2]), int(num_t(std::atoi(argv[2])) * rslide), intensity));
  num_t d(0);
  auto  S(d);
  auto  s0(d);
  auto  s1(d);
  auto  s2(d);
  auto  s3(d);
  auto  s4(d);
  auto  s5(d);
  auto  s6(d);
  int   t(- 1);
  int   tp(0);
  auto  tm(tp);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    const auto bd(d);
    std::stringstream ins(s);
    ins >> d;
    const auto delta(range < 0 ? atan(d - bd) : d - bd);
    if(d != bd) {
      if(bd != num_t(0) && M != num_t(0)) {
        tp ++; tm ++;
        s0 += range < 0 ? d - bd - tan(M) : delta - M;
        s1 += delta * M;
        s2 += delta * M * num_t(tp - tm);;
        s3 += (d - bd) * M;
        s4 += (d - bd) * M * num_t(tp - tm);;
        s5 += delta * M * num_t(tp);
        s6 -= delta * M * num_t(tm);
      }
      S += delta;
      M  = num_t(0);
      for(int i = 0; i < p.size(); i ++)
        M += p[i].next(S) - S;
      M /= num_t(p.size());
      if(! isfinite(M) || isnan(M)) M = num_t(0);
      if(0 < s5) s5 = num_t(tp = 0);
      if(0 < s6) s6 = num_t(tm = 0);
    }
    std::cout << M << ", " << (tp - tm) << ", " << s0 << ", " << s1 << ", " << s2 << ", " << s3 << ", " << s4 << std::endl << std::flush;
  }
  return 0;
}

