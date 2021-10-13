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
#include <sys/resource.h>

/*
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
*/
#include "../catg/lieonn.hh"
typedef myfloat num_t;
#include "../catg/catg.hh"
typedef P012L<num_t, linearFeeder<num_t, idFeeder<num_t> > > plin_t;
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
  const auto stat(3 * 3 * 3);
  const auto var(3);
        int  step(1);
  if(argc < 2)
    std::cerr << argv[0] << " <step>?" << std::endl;
  if(1 < argc) step = std::atoi(argv[1]);
  std::cerr << "continue with " << argv[0] << " " << step << std::endl;
  // N.B. we need to predict with the step that is larger than input stream.
  shrinkMatrix<num_t, plin_t> p(plin_t(stat * abs(step), var, abs(step)), step);
  std::string s;
  num_t d(0);
  auto  M(d);
  auto  S(d);
  struct rusage start, end;
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    getrusage(RUSAGE_SELF, &end);
    const auto tvsec( end.ru_utime.tv_sec  - start.ru_utime.tv_sec);
    const auto tvusec(end.ru_utime.tv_usec - start.ru_utime.tv_usec);
    getrusage(RUSAGE_SELF, &start);
    std::cout << D << ", " << (M = p.next(d)) << ", " << (S += D) << ", " << tvsec << ":" << tvusec << std::endl << std::flush;
  }
  return 0;
}

