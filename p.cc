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
    M.resize(5, Mx0 = MM = T(int(0)));;
    Mx.resize(M.size(), MM);
    p0 = P0maxRank<T>(status);
    p1 = shrinkMatrix<T, P1I<T, idFeeder<T> > >(P1I<T, idFeeder<T> >(status, var1, var1), var1);
    p2 = shrinkMatrix<T, P012L<T, idFeeder<T> > >(P012L<T, idFeeder<T> >(status, var2, var2), var2);
    q  = idFeeder<T>(status);
  }
  inline ~P() { ; }
  inline const T& next(T d) {
    Mx0   = max(Mx0, abs(d));
    if(Mx0 == T(int(0)) || (d /= Mx0) == T(int(0)) || ! isfinite(d))
      return MM;
    M[0]  = max(- T(int(1)), min(T(int(1)), p0.next(d) / var0));
    M[1]  = max(- T(int(1)), min(T(int(1)), p1.next(d)));
    M[2]  = max(- T(int(1)), min(T(int(1)), p2.next(d)));
    {
      const auto& qq0(q.next(d));
      Mx[4] = max(abs(d), Mx[4]);
      if(q.full) {
        const int qs(sqrt(T(int(qq0.size()))));
        SimpleVector<T> q0(qs + 1);
        q0.O();
        for(int i = 0; i < qq0.size() - qs - 1; i ++) {
          auto qm0(SimpleVector<T>(qs).O().setVector(0, qq0.subVector(i, qs - 1)));
          qm0[qm0.size() - 1] = qm0[qm0.size() - 2];
          auto qm(makeProgramInvariant<T>(qm0));
          q0 += move(qm.first) *
            pow(qm.second, ceil(- log(SimpleMatrix<T>().epsilon())));
        }
        auto qm0(SimpleVector<T>(qs).O().setVector(0, qq0.subVector(qq0.size() - qs - 1, qs - 1)));
        qm0[qm0.size() - 1] = qm0[qm0.size() - 2];
        auto qm(makeProgramInvariant<T>(qm0));
        M[3] = revertProgramInvariant<T>(make_pair(
          - (q0.dot(qm.first) - q0[q0.size() - 2] *
               qm.first[qm.first.size() - 2]) / q0[q0.size() - 2],
             qm.second)) /
            pow(qm.second, ceil(- log(SimpleMatrix<T>().epsilon())));
        M[4] = qq0[0];
        for(int i = 1; i < qq0.size(); i ++) M[4] += qq0[i];
        M[4] = - M[4];
      }
    }
    MM = T(int(0));
    for(int i = 0; i < M.size(); i ++) if(isfinite(M[i])) {
      Mx[i] = max(Mx[i], abs(M[i]));
      if(Mx[i] != T(int(0))) MM += (M[i] /= Mx[i]);
    }
    return MM *= Mx0 / T(int(5));
  }
  P0maxRank<T> p0;
  shrinkMatrix<T, P1I<T, idFeeder<T> > > p1;
  shrinkMatrix<T, P012L<T, idFeeder<T> > > p2;
  idFeeder<T> q;
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
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  assert(0 < status);
  std::vector<P0DFT<num_t, P<num_t>, idFeeder<num_t> > > p;
  p.resize(3, P0DFT<num_t, P<num_t>, idFeeder<num_t> >(P<num_t>(status), int(sqrt(num_t(status)))));
  num_t d(int(0));
  auto  M0(d);
  auto  M1(d);
  auto  M(d);
  auto  S(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    M   = isfinite(d * M0 * M1) ? p[2].next(d * M0 * M1) : num_t(int(0));
    M1  = isfinite(d * M0)      ? p[1].next(d * M0)      : num_t(int(0));
    M0  = isfinite(d)           ? p[0].next(d)           : num_t(int(0));
    std::cout << D << ", " << (M *= M0 * M1)<< ", " << (S += D) << std::endl << std::flush;
  }
  return 0;
}

