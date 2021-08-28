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
  int  stat(256);
  int  var(2);
  int  pw(1);
  if(argc < 2)
    std::cerr << "catgp <condition>? <var>? <pow>?" << std::endl;
  else {
    if(1 < argc) stat = std::atoi(argv[1]);
    if(2 < argc) var  = std::atoi(argv[2]);
    if(3 < argc) pw   = std::atoi(argv[3]);
  }
  std::cerr << "continue with catgp " << stat << " " << var << " " << pw << std::endl;
  P012L<num_t, linearFeeder<num_t, sumFeeder<num_t> > > p(abs(stat), var);
  P012L<num_t, arctanFeeder<num_t, sumFeeder<num_t> > > q(abs(stat), var);
  std::string s;
  num_t d(0);
  auto  M(d);
  auto  D(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D = d * M;
    M = stat < 0 ? q.next(d) : p.next(d);
    M = pw == 0 ? sgn<num_t>(M) : sgn<num_t>(M) * pow(abs(M), pw < 0 ? num_t(1) / num_t(abs(pw)) : num_t(pw));
    std::cout << D << ", " << M << ", " << d << std::endl << std::flush;
  }
  return 0;
}

