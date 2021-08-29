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
  int  step(1);
  if(argc < 2)
    std::cerr << "catgp <condition>? <var>? <step>?" << std::endl;
  else {
    if(1 < argc) stat = std::atoi(argv[1]);
    if(2 < argc) var  = std::atoi(argv[2]);
    if(3 < argc) step = std::atoi(argv[3]);
  }
  std::cerr << "continue with catgp " << stat << " " << var << " " << step << std::endl;
  P012L<num_t, linearFeeder<num_t, idFeeder<num_t> > > p(abs(stat), var, step);
  P012L<num_t, arctanFeeder<num_t, idFeeder<num_t> > > q(abs(stat), var, step);
  std::string s;
  num_t d(0);
  auto  D(d);
  std::vector<num_t> M;
  M.resize(step, num_t(0));
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    D  = d * M[0];
    for(int i = 1; i < M.size(); i ++)
      M[i - 1] = M[i];
    M[M.size() - 1] = stat < 0 ? q.next(d) : p.next(d);
    std::cout << D << ", " << M[M.size() - 1] << ", " << d << std::endl << std::flush;
  }
  return 0;
}

