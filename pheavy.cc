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
#include <decompose/decompose.hh>

// N.B. prediction on some range do persistent.
template <typename T> class P {
public:
  inline P() { ; }
  inline P(const int& status) {
    assert(0 < status);
    const int var1(max(T(int(2)), pow(T(status), T(int(1)) / T(int(3)))));
    const int var2(max(T(int(2)), pow(T(status), T(int(1)) / T(int(4)))));
    M.resize(7, M5 = Mx0 = MM = T(int(0)));;
    Mx.resize(M.size(), MM);
    p0 = P0maxRank<T>(status);
    p1 = shrinkMatrix<T, P1I<T, idFeeder<T> > >(P1I<T, idFeeder<T> >(status, var1, var1), var1);
    p2 = shrinkMatrix<T, P012L<T, idFeeder<T> > >(P012L<T, idFeeder<T> >(status, var2, var2), var2);
    q  = idFeeder<T>(status);
    q0 = SimpleVector<T>(status + 1).O();
    f  = idFeeder<T>(status);
  }
  inline ~P() { ; }
  inline const T& next(T d) {
    Mx0   = max(Mx0, abs(d));
    if(Mx0 == T(int(0)) || (d /= Mx0) == T(int(0)) || ! isfinite(d))
      return MM;
    M[0]  = - d;
    M[1]  = p0.next(d);
    M[2]  = p1.next(d);
    M[3]  = p2.next(d);
    M[1] /= (Mx[1] = max(Mx[1], abs(M[1])));
    M[2] /= (Mx[2] = max(Mx[2], abs(M[2])));
    M[3] /= (Mx[3] = max(Mx[3], abs(M[3])));
    {
      auto qm(makeProgramInvariant<T>(q.next(d)));
      q0 += std::move(qm.first) * pow(qm.second, ceil(- log(SimpleMatrix<T>().epsilon())));
      auto qq(q);
      auto qqm(makeProgramInvariant<T>(qq.next(d)));
      M[4] = revertProgramInvariant<T>(make_pair(
        - (q0.dot(qqm.first) - q0[q0.size() - 2] *
             qqm.first[qqm.first.size() - 2]) / q0[q0.size() - 2] /
           T(int(q0.size())), qqm.second));
    }
    M5   -= d;
    M[4] /= (Mx[4] = max(Mx[4], abs(M[4])));
    M[5]  = M5 / (Mx[5] = max(Mx[5], abs(M5)));
    {
      const auto& ff(f.next(d));
      Mx[6] = max(abs(d), Mx[6]);
      if(f.full) {
        M[6] = ff[0];
        for(int i = 1; i < ff.size(); i ++) M[6] += ff[i];
        M[6] = (- M[6]) / (Mx[6] = max(Mx[6], abs(M[6])));
      }
    }
    MM = T(int(0));
    for(int i = 0; i < M.size(); i ++) if(isfinite(M[i])) MM += M[i];
    return MM *= Mx0 / T(int(M.size()));
  }
  P0maxRank<T> p0;
  shrinkMatrix<T, P1I<T, idFeeder<T> > > p1;
  shrinkMatrix<T, P012L<T, idFeeder<T> > > p2;
  idFeeder<T> q;
  SimpleVector<T> q0;
  idFeeder<T> f;
  T M5;
  T MM;
  T Mx0;
  vector<T> M;
  vector<T> Mx;
};

// In laurent series, we treat a_-1 as both side a_1 and a_-1 arithmetric avg.
template <typename T, typename P> class PWalkBoth {
public:
  inline PWalkBoth() { ; }
  inline PWalkBoth(P&& p) { S = T(int(0)); this->p = q = p; }
  inline ~PWalkBoth() { ; }
  inline T next(const T& d) {
    static const T zero(int(0));
    static const T one(int(1));
    static const T two(int(2));
    const auto bS(S);
    if((S += d) != zero && bS != zero) {
      const auto dd(one / S - one / bS);
            auto qd(q.next(dd));
      qd = qd == zero ? qd : one / (one / S + one / qd) - S;
      return (p.next(d) + (isfinite(qd) ? qd : zero)) / two;
    }
    return p.next(d);
  }
  T S;
  P p;
  P q;
};

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::string s;
  std::cerr << argv[0] << std::endl;
  // N.B. 2x ... 2x stack. increasingly heavy, no use if input long enough.
  //      however, if the jammer only see me, they will be confused if
  //      accuracy is enough. So reset each by the external script.
  std::vector<num_t> in;
  std::vector<PWalkBoth<num_t, P<num_t> > > p;
  p.emplace_back(P<num_t>(6));
  int   t;
  num_t d(t ^= t);
  auto  M(d);
  auto  S(d);
  ++ t;
  for(int n = 0; 0 <= n && std::getline(std::cin, s, '\n'); n ++) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    M = num_t(int(0));
    for(int i = 0; i < p.size(); i ++) M += p[i].next(d);
    in.emplace_back(d);
    if(((n / 6) >> t) & 1) {
      p.emplace_back(P<num_t>(6 << (t ++)));
      for(int i = 0; i < in.size() - 1; i ++)
        p[p.size() - 1].next(in[i]);
      M += p[p.size() - 1].next(d);
    }
    std::cout << D << ", " << (M /= num_t(int(p.size()))) << ", " << (S += D) << std::endl << std::flush;
  }
  return 0;
}

