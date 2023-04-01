#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <assert.h>
#include <sys/resource.h>

#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
#include <p0/lieonn.hh>
typedef myfloat num_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
  std::cout << std::setprecision(30);
  std::string s;
  std::cerr << argv[0] << std::endl;
  std::vector<PBond<num_t, Prange<num_t, deltaFeeder<num_t, idFeeder<num_t> >, deltaFeeder<num_t, cbrtFeeder<num_t, idFeeder<num_t> > > >, sumFeeder<num_t, idFeeder<num_t> >, invFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > > p;
  std::vector<PBond<num_t, Prange<num_t, idFeeder<num_t>, idFeeder<num_t> >, idFeeder<num_t>, deltaFeeder<num_t, invFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > > > q;
  p.emplace_back(PBond<num_t, Prange<num_t, deltaFeeder<num_t, idFeeder<num_t> >, deltaFeeder<num_t, cbrtFeeder<num_t, idFeeder<num_t> > > >, sumFeeder<num_t, idFeeder<num_t> >, invFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > >(Prange<num_t, deltaFeeder<num_t, idFeeder<num_t> >, deltaFeeder<num_t, cbrtFeeder<num_t, idFeeder<num_t> > > >(6), 1 + 3 + int(ceil(num_t(6 - 1) / (pow(num_t(6 + 1), num_t(int(2)) / num_t(int(3)) ) - pow(num_t(6), num_t(int(2)) / num_t(int(3)) ) )) ) ) );
  int   t;
  num_t d(t ^= t);
  auto  M(d);
  auto  MS(d);
  auto  S(d);
  std::vector<num_t> dd;
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    dd.emplace_back(d);
    if((MS = max(abs(S += d), MS)) != num_t(int(0)) M = S / MS;
    else M = num_t(int(0));
    int cnt(1);
    for(int i = 0; i < p.size(); i ++, cnt ++) {
      auto lastM(p[i].next(d));
      M += lastM;
      if(lastM != num_t(int(0)) && i == p.size() - 1) {
        p.emplace_back(PBond<num_t, Prange<num_t, deltaFeeder<num_t, idFeeder<num_t> >, deltaFeeder<num_t, cbrtFeeder<num_t, idFeeder<num_t> > > >, sumFeeder<num_t, idFeeder<num_t> >, invFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > >(Prange<num_t, deltaFeeder<num_t, idFeeder<num_t> >, deltaFeeder<num_t, cbrtFeeder<num_t, idFeeder<num_t> > > >(i + 7), 1 + 3 + int(ceil(num_t(i + 7 - 1) / (pow(num_t(i + 7 + 1), num_t(int(2)) / num_t(int(3)) ) - pow(num_t(i + 7), num_t(int(2)) / num_t(int(3)) ) )) ) ) );
        for(int j = 0; j < dd.size(); j ++)
          p[p.size() - 1].next(dd[j]);
        break;
      }
    }
    for(int i = 0; i < q.size(); i ++, cnt ++)
      M += q[i].next(d);
    if(6 <= t ++) {
      q.emplace_back(PBond<num_t, Prange<num_t, idFeeder<num_t>, idFeeder<num_t> >, idFeeder<num_t>, deltaFeeder<num_t, invFeeder<num_t, sumFeeder<num_t, idFeeder<num_t> > > > >(Prange<num_t, idFeeder<num_t>, idFeeder<num_t> >(t), t + 1));
      for(int i = 0; i < dd.size(); i ++)
        q[q.size() - 1].next(dd[i]);
    }
    std::cout << (M /= num_t(cnt)) << std::endl << std::flush;
  }
  return 0;
}

