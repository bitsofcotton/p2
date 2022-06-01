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
#include <random>
#include <assert.h>
#include <sys/resource.h>

/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
#include "../catg/lieonn.hh"
typedef myfloat num_t;
#include "../p0/p0.hh"
#include "../p1/p1.hh"
#include "../catg/catg.hh"
typedef P1I<num_t, idFeeder<num_t> > plin1_t;
typedef P012L<num_t, idFeeder<num_t> > plin2_t;
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
  int status(60);
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  assert(status);
  const auto var0(max(int(1), int(exp(sqrt(log(num_t(abs(status) * 2)))))));
  const int  var1(max(num_t(int(2)), pow(num_t(abs(status)), num_t(int(1)) / num_t(int(3))) ));
  const int  var2(max(num_t(int(2)), pow(num_t(abs(status)), num_t(int(1)) / num_t(int(4))) ));
  shrinkMatrix<num_t, plin2_t> p(plin2_t(abs(status), var2, var2), var2);
  shrinkMatrix<num_t, plin1_t> q(plin1_t(abs(status), var1, var1), var1);
  P0maxRank<num_t> r(abs(status) * 2, var0);
  auto  s(r);
  std::string str;
  num_t zero(int(0));
  auto  d(zero);
  auto  Mp(d);
  auto  Mq(d);
  auto  Mr(d);
  auto  Ms(d);
  auto  MMp(d);
  auto  MMq(d);
  auto  MMr(d);
  auto  MMs(d);
  auto  S(d);
  while(std::getline(std::cin, str, '\n')) {
    std::stringstream ins(str);
    ins >> d;
    const auto Dp(d * Mp);
    const auto Dq(d * Mp * Mq);
    const auto Dr(d * Mp * Mq * Mr);
    const auto D( d * Mp * Mq * Mr * Ms);
    MMp = max(MMp, abs(d ) * num_t(int(2)));
    MMq = max(MMq, abs(Dp) * num_t(int(2)));
    MMr = max(MMr, abs(Dq) * num_t(2 * var0));
    MMs = max(MMs, abs(Dr) * num_t(2 * var0));
    if(status < 0) { Mp = Mq = num_t(int(1)); }
    else {
      if(abs(Mp = max(- MMp, min(MMp, p.next(d ) )) ) == MMp)
        Mp = zero;
      if(Mp == zero || abs(Mq = max(- MMq, min(MMq, q.next(Dp) )) ) == MMq)
        Mq = zero;
    }
    if(Mq == zero || abs(Mr = max(- MMr, min(MMr, r.next(Dq)[0] )) ) == MMr)
      Mr = zero;
    if(Mr == zero || abs(Ms = max(- MMs, min(MMs, s.next(Dr)[0] )) ) == MMs)
      Ms = zero;
    std::cout << D << ", " << (Mp * Mq * Mr * Ms) << ", " << (S += D) << std::endl << std::flush;
  }
  return 0;
}

