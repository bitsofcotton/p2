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
  assert(4 < argc);
  const auto  range(std::atoi(argv[1]));
  const num_t rslide(std::atof(argv[3]));
  const auto  intensity(- num_t(1) / num_t(2));
  std::vector<std::vector<P012L<num_t> > > p;
  {
    std::vector<P012L<num_t> > pp;
    for(int i = 4; i < argc; i ++)
      pp.emplace_back(P012L<num_t>(abs(range), std::atoi(argv[i]), int(num_t(std::atoi(argv[i])) * rslide), intensity));
     p.resize(std::atoi(argv[2]), pp);
  }
  num_t d(0);
  auto  s0(d);
  auto  s1(d);
  auto  M0(d);
  std::vector<num_t> dd(p.size(), num_t(0));
  auto  rr(dd);
  auto  M(rr);
  {
    std::getline(std::cin, s, '\n');
    std::stringstream ins(s);
    ins >> dd[0];
    for(int i = 1; i < dd.size(); i ++)
      dd[i] = dd[0];
  }
  while(std::getline(std::cin, s, '\n')) {
    const auto bd0(d);
    std::stringstream ins(s);
    ins >> d;
    if(d != bd0) {
      if(bd0 != num_t(0) && M0 != num_t(0)) {
        s0 += (d - bd0) - M0;
        s1 += (d - bd0) * M0;
      }
      const auto bd(dd);
      for(int i = 0; i < p.size(); i ++) {
        dd[i] += (d - bd0) * abs(rr[i]);
        const auto bf(M[i] * (dd[i] - bd[i]));
        rr[i] += num_t(arc4random_uniform(0x10000) + arc4random_uniform(0x10000) - 0x8000 * 2) / num_t(0x8000);
        if(dd[i] != num_t(0)) {
          M[i] = num_t(0);
          for(int j = 0; j < p[i].size(); j ++)
            M[i] += p[i][j].next(dd[i]) - dd[i];
          M0  += (M[i] /= num_t(p[i].size())) * bf * abs(rr[i]);
        }
      }
      M0 /= num_t(p.size());
      if(! isfinite(M0) || isnan(M0)) M0 = num_t(0);
    }
    std::cout << M0 << ", " << s0 << ", " << s1 << std::endl << std::flush;
  }
  return 0;
}

