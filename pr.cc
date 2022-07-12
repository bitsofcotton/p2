#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <random>
#include <algorithm>
#include <assert.h>
#include <sys/resource.h>

#include <p0/lieonn.hh>
typedef myfloat num_t;
#include <p0/p0.hh>
#include <p1/p1.hh>
#include <catg/catg.hh>

template <typename T> class P {
public:
  inline P() { ; }
  inline P(const int& status) {
    assert(0 < status);
    var0 = max(T(int(1)), T(int(exp(sqrt(log(T(status)))))) );
    const auto var1(max(T(int(2)), pow(T(status), T(int(1)) / T(int(3)))));
    const auto var2(max(T(int(2)), pow(T(status), T(int(1)) / T(int(4)))));
    M.resize(7, Mx0 = MM = T(int(0)));;
    Mx.resize(7, MM);
    p0 = P0maxRank<T>(status);
    p1 = shrinkMatrix<T, P1I<T, idFeeder<T> > >(P1I<T, idFeeder<T> >(status, var1, var1), var1);
    p2 = shrinkMatrix<T, P012L<T, idFeeder<T> > >(P012L<T, idFeeder<T> >(status, var2, var2), var2);
    q  = idFeeder<T>(status);
    q0 = SimpleVector<T>(status + 1).O();
  }
  inline ~P() { ; }
  inline const T& next(T d) {
    Mx0   = max(Mx0, abs(d));
    if(Mx0 == T(int(0)) || (d /= Mx0) == T(int(0)) || ! isfinite(d))
      return MM;
    Mx[0] = max(Mx[0], abs(d));
    M[0]  =  - d / Mx[0];
    M[1]  = max(- Mx[0], min(Mx[0], p1.next(d)));
    M[1] /= (Mx[1] = max(Mx[1], abs(M[1])));
    M[2]  = max(- Mx[0], min(Mx[0], p2.next(d)));
    M[2] /= (Mx[2] = max(Mx[2], abs(M[2])));
    M[3]  = p0.next(d) / var0;
    M[3] /= (Mx[3] = max(Mx[3], abs(M[3])));
    {
      auto qm(makeProgramInvariant<T>(q.next(d)));
      q0 += std::move(qm.first) * pow(qm.second, ceil(- log(SimpleMatrix<T>().epsilon())));
      auto qq(q);
      auto qqm(makeProgramInvariant<T>(qq.next(d)));
      M[4] = revertProgramInvariant<T>(make_pair(
        - (q0.dot(qqm.first) - q0[q0.size() - 2] *
             qqm.first[qqm.first.size() - 2]) / q0[q0.size() - 2],
           qqm.second)) /
          pow(qqm.second, ceil(- log(SimpleMatrix<T>().epsilon())));
    }
    M[4] /= (Mx[4] = max(Mx[4], abs(M[4])));
    M5   -= d;
    M[5]  = M5 / (Mx[5] = max(Mx[5], abs(M5)));
    M[6]  = T(int(1)) / T(int(2));
    MM    = T(int(0));
    for(int i = 0; i < M.size(); i ++) if(isfinite(M[i])) MM += M[i];
    return MM *= Mx0 / T(int(7));
  }
  P0maxRank<T> p0;
  shrinkMatrix<T, P1I<T, idFeeder<T> > > p1;
  shrinkMatrix<T, P012L<T, idFeeder<T> > > p2;
  idFeeder<T> q;
  SimpleVector<T> q0;
  T M5;
  T MM;
  T Mx0;
  T var0;
  vector<T> M;
  vector<T> Mx;
};

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::string s;
  int status(77);
  int method(0);
  int sum(1);
  int step(1);
  if(argc < 2) std::cerr << argv[0] << " <status>? <method>? <sum>? <step>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  if(2 < argc) method = std::atoi(argv[2]);
  if(3 < argc) sum    = std::atoi(argv[3]);
  if(4 < argc) step   = std::atoi(argv[4]);
  std::cerr << argv[0] << " " << status << " " << method << " " << sum << " " << step << std::endl;
  assert(0 < status);
  std::vector<P<num_t> > p;
  p.resize(3, P<num_t>(status));
  int   t;
  num_t d(t ^= t);
  auto  tt(t);
  auto  M0(d);
  auto  M1(d);
  auto  M(d);
  auto  S(d);
  std::random_device rd;
  std::mt19937_64 mt(rd());
  // cf. knuth_b for shuffle 128.
  std::shuffle_order_engine<std::linear_congruential_engine<unsigned int, 16807, 0, 2147483647>, 8> kb(rd());
  std::ranlux48 rl48(rd());
  while(true) {
    switch(method) {
    case 0:
      d += num_t(arc4random() & 0x7fffff) / (num_t(int(0x7fffff)) / num_t(int(2))) - num_t(int(1));
      break;
    case 1:
      d += num_t(int(mt()) & 0x7fffff) / (num_t(int(0x7fffff)) / num_t(int(2))) - num_t(int(1));
      break;
    case 2:
      d += num_t(int(kb()) & 0x7fffff) / (num_t(int(0x7fffff)) / num_t(int(2))) - num_t(int(1));
      break;
    case 3:
      d += num_t(int(rl48()) & 0x7fffff) / (num_t(int(0x7fffff)) / num_t(int(2))) - num_t(int(1));
      break;
    default:
      assert(0 && "Should not be reached.");
    }
    if(sum <= ++ t) {
      const auto D(d * M);
      M   = isfinite(d * M0 * M1) ? p[2].next(d * M0 * M1) : num_t(int(0));
      M1  = isfinite(d * M0)      ? p[1].next(d * M0)      : num_t(int(0));
      M0  = isfinite(d)           ? p[0].next(d)           : num_t(int(0));
      if(step <= ++ tt) {
        std::cout << D << ", " << (M *= M0 * M1)<< ", " << (S += D) << ", " << d << std::endl << std::flush;
        tt ^= tt;
      }
      d = num_t(t ^= t);
    }
  }
  return 0;
}

