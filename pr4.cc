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
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include "lieonn.hh"
typedef myfloat num_t;

template <typename T> inline T logscale(const T& x) {
  return sgn<T>(x) * log(T(int(1)) + abs(x));
}

template <typename T> inline T expscale(const T& x) {
  return sgn<T>(x) * (exp(abs(x)) - T(int(1)) );
}

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  // N.B. This is for the stream truly random ones in our meaning.
  //      They're the condition tan((A:=\[...\])x)==\[x,y,z,w,0,...,0\]
  //      condition's A is truly random in any which layer we take invariants.
  //      This is: to take each A.row(0..3) as a stream we made A_0',...,A_3'
  //      also truly random recursive ones.
  //      We conclude such condition's A...'s singular value is unstable,
  //      so instead of get average of A.rows
  //      (the possibility of taking average is question), 
  //      we take some of the stream probably have better structures.
  //      In general case, this condition is invalid, however, the original
  //      f of the stream generator has better smaller size core and
  //      only prngs to timing hack, we get better result than plain prediction.
# define rr 4
  // N.B. Even in this case, the jammer can exists as: 4-step depend
  //      timing hacks. To avoid this condition, we need to specify skip
  //      with argv[1] and recursive apply this.
  // N.B. we should separate process because of arc4random seeding.
  // N.B. pr4 12 | pr4 8 | pr4 4 | pr4 can be one of a predictor integrate,
  //      however this needs large number of point to start prediction.
  //      pr4 3 | pr4 2 | pr4 1 | pr4 0 also can be one of a predictor such one.
  int skip(0);
  if(argc < 2) std::cerr << argv[0] << " <skip? : continue with ";
  if(1 < argc) skip = std::atoi(argv[1]);
  const auto minus(skip < 0 || (1 < argc && argv[1][0] == '-'));
  std::cerr << argv[0] << " " << (minus ? "-" : "") << abs(skip) << std::endl;
  // N.B. if there's prediction apply order algebra, it's up to 4 layers.
  //      also, we take arguments from p1, catgp default.
  PBond<num_t, P01<num_t> >   p0(P01<num_t>(4), 26);
  PBond<num_t, P012L<num_t> > q0(P012L<num_t>(4), 124);
  auto p1(p0);
  auto p2(p0);
  auto p3(p0);
  auto q1(q0);
  auto q2(q0);
  auto q3(q0);
  // N.B. we also assume p1-4th predicted stream has some of the continuous
  //      part.
  PBond<num_t, P0maxRank<num_t> > r(P0maxRank<num_t>(2), int(exp(num_t(2 * 2))) );
  std::string s;
  int   t0(0);
  auto  t1(t0);
  auto  t2(t0);
  auto  t3(t0);
  auto  ts(t0);
  auto  s0(t0);
  auto  s1(t0);
  auto  s2(t0);
  auto  s3(t0);
  num_t d(t0);
  auto  M0(d);
  auto  M1(d);
  auto  M2(d);
  auto  M3(d);
  auto  MM(d);
  auto  D0(d);
  auto  D1(d);
  auto  D2(d);
  auto  D3(d);
  auto  DM(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D0 += d;
    D1 += d * M0;
    D2 += d * M0 * M1;
    D3 += d * M0 * M1 * M2;
    DM += logscale<num_t>(logscale<num_t>(d * M0 * M1 * M2 * M3));
    if(! isfinite(DM)) DM = num_t(int(0));
#if defined(_JAM_)
    if(M0 * M1 * M2 * M3 * MM != num_t(int(0))) d = abs(d) * sgn<num_t>(arc4random_uniform(2) & 1 ? - M0 * M1 * M2 * M3 * MM : M0 * M1 * M2 * M3 * MM);
#else
    std::cout << d * M0 * M1 * M2 * M3 * MM << ", ";
#endif
    // N.B. Recursively apply predictions to stack of the timing point
    //      causes hard to jam out us, however, jam us out is not impossible.
    //      This is because the jammer also needs the longer length to get point
    //      differed to apply each prediction to root with each timing.
    // N.B. in fact, we need better internal state size for each arc4random
    //      calll, however, in short range, we don't need them.
    if(abs(skip) < ++ ts) {
      ts ^= ts;
      if(s0 < ++ t0) {
        M0 = minus ? q0.next(D0) : p0.next(D0);
        s0 = (t0 % 4 ? 4 - (t0 % 4) + t0 : t0) + arc4random_uniform(rr);
        D0 = num_t(int(0));
        if(s1 < ++ t1) {
          M1 = minus ? q1.next(D1) : p1.next(D1);
          s1 = (t1 % 4 ? 4 - (t1 % 4) + t1 : t1) + arc4random_uniform(rr);
          D1 = num_t(int(0));
          if(s2 < ++ t2) {
            M2 = minus ? q2.next(D2) : p2.next(D2);
            s2 = (t2 % 4 ? 4 - (t2 % 4) + t2 : t2) + arc4random_uniform(rr);
            D2 = num_t(int(0));
            if(s3 < ++ t3) {
              M3 = minus ? q3.next(D3) : p3.next(D3);
              MM = expscale<num_t>(expscale<num_t>(r.next(DM)));
              s3 = (t3 % 4 ? 4 - (t3 % 4) + t3 : t3) + arc4random_uniform(rr);
              D3 = DM = num_t(int(0));
            }
          }
        }
      }
    }
#if defined(_JAM_)
    std::cout << d << std::endl << std::flush;
#else
    std::cout << M0 * M1 * M2 * M3 * MM << std::endl << std::flush;
#endif
  }
  return 0;
}

