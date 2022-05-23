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
  const int var(max(num_t(int(2)), pow(num_t(abs(status)), num_t(int(1)) / num_t(int(status < 0 ? 3 : 4)))));
  shrinkMatrix<num_t, plin_t> p0, p1, p2;
  plin_t q0, q1, q2;
  if(status < 0) {
    q0 = plin_t(- status, var);
    q1 = plin_t(- status * 2, var);
    q2 = plin_t(- status * 3, var);
  } else {
    p0 = shrinkMatrix<num_t, plin_t>(plin_t(status, var, var), var);
    p1 = shrinkMatrix<num_t, plin_t>(plin_t(status * 2, var, var), var);
    p2 = shrinkMatrix<num_t, plin_t>(plin_t(status * 3, var, var), var);
  }
  std::string s;
  num_t d(int(0));
  auto  Mx(d);
  auto  M0(d);
  auto  M1(d);
  auto  M2(d);
  auto  MM(d);
  auto  S0(d);
  auto  S1(d);
  auto  S2(d);
  auto  SS(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D0(d * M0);
    const auto D1(d * M1);
    const auto D2(d * M2);
    const auto DD(d * MM);
    Mx = max(Mx, abs(d) * num_t(int(2)));
    std::cout << D0 << ", " << D1 << ", " << D2 << ", " << DD;
    std::cout << ", " << (M0 = max(- Mx, min(Mx, status < 0 ? q0.next(d) : p0.next(d) )) );
    std::cout << ", " << (M1 = max(- Mx, min(Mx, status < 0 ? q1.next(d) : p1.next(d) )) );
    std::cout << ", " << (M2 = max(- Mx, min(Mx, status < 0 ? q2.next(d) : p2.next(d) )) );
    std::cout << ", " << (MM = (M0 + M1 + M2) / num_t(int(3)));
    std::cout << ", " << (S0 += D0) << ", " << (S1 += D1);
    std::cout << ", " << (S2 += D2) << ", " << (SS += DD);
    std::cout << std::endl << std::flush;
  }
  return 0;
}

