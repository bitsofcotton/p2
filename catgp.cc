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
  int  stat(1296);
  if(argc < 2)
    std::cerr << "catgp <condition>?" << std::endl;
  if(1 < argc) stat = std::atoi(argv[1]);
  stat = max(min(stat, int(1296)), - int(1296));
  const auto var(min(6, max(2, int(sqrt(sqrt(num_t(int(abs(stat)))))))));
  std::cerr << "continue with catgp " << stat << std::endl;
  P012L<num_t, linearFeeder<num_t, idFeeder<num_t> > > p(abs(stat), var);
  P012L<num_t, arctanFeeder<num_t, idFeeder<num_t> > > q(abs(stat), var);
  std::string s;
  num_t d(0);
  auto  D(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D  = d * M;
    M = stat < 0 ? q.next(d) : p.next(d);
    std::cout << D << ", " << M << ", " << d << std::endl << std::flush;
  }
  return 0;
}

