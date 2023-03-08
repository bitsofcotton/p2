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
typedef P012L<num_t, idFeeder<num_t> > plin_t;
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
  int status(20);
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  assert(0 < status);
  const int var(max(num_t(int(2)), pow(num_t(status), num_t(int(1)) / num_t(int(4)))));
  shrinkMatrix<num_t, plin_t> p(plin_t(status, var, var), var);
  std::string s;
  num_t d(int(0));
  auto  Mx(d);
  auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    Mx = max(Mx, abs(d) * num_t(int(2)));
    std::cout << (M = max(- Mx, min(Mx, p.next(d) )) ) << std::endl << std::flush;
  }
  return 0;
}

