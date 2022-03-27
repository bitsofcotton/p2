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
typedef P012L<num_t, deltaFeeder<num_t, arctanFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > > patan_t;
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
        int  look(1);
  if(argc < 2) std::cerr << argv[0] << " <step>? <look>? : continue with ";
  if(1 < argc) step = std::atoi(argv[1]);
  if(2 < argc) look = std::atoi(argv[2]);
  std::cerr << argv[0] << " " << step << " " << look << std::endl;
  shrinkMatrix<num_t, plin_t> p;
  plin_t q;
  shrinkMatrix<num_t, patan_t> pp;
  patan_t qq;
  if(look < 0) {
    if(step < 0)
      qq = patan_t(abs(step * step * step), abs(step), abs(look));
    else
      pp = shrinkMatrix<num_t, patan_t>(patan_t(stat * abs(step), var, abs(step) + abs(look)), abs(step));
  } else {
    if(step < 0)
      q = plin_t(abs(step * step * step), abs(step), abs(look));
    else
      p = shrinkMatrix<num_t, plin_t>(plin_t(stat * abs(step), var, abs(step) + abs(look)), abs(step));
  }
  std::string s;
  num_t d(0);
  auto  Mx(d);
  std::vector<num_t> M;
  M.resize(abs(look), d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M[0]);
    for(int i = 0; i < M.size() - 1; i ++) M[i] = std::move(M[i + 1]);
    if(Mx < abs(d)) Mx = abs(d) * num_t(int(2));
    std::cout << D << ", " << (M[M.size() - 1] = max(- Mx, min(Mx, look < 0 ? (step < 0 ? qq.next(d) : pp.next(d)) : (step < 0 ? q.next(d) : p.next(d)) )) / (Mx != num_t(int(0)) ? Mx : num_t(int(1)))) << std::endl << std::flush;
  }
  return 0;
}

