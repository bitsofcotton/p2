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
    M[2]  = p1.next(d);
    M[3]  = p2.next(d);
    if((Mx[1] = max(Mx[1], abs(M[1]))) != T(int(0))) M[1] /= Mx[1];
    if((Mx[2] = max(Mx[2], abs(M[2]))) != T(int(0))) M[2] /= Mx[2];
    if((Mx[3] = max(Mx[3], abs(M[3]))) != T(int(0))) M[3] /= Mx[3];
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
    return MM *= Mx0 / T(int(M.size() - 1));
  }
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

template <typename T, typename P> class Pmss {
public:
  inline Pmss() { ; }
  inline Pmss(P&& p, const int& len = 2) {
    this->p = p;
    r = q = idFeeder<T>(len);
  }
  inline ~Pmss() { ; }
  inline T next(const T& d) {
    const auto& msv(q.next(d));
    const auto  ms(msv.dot(mscache<T>(msv.size())));
    if(! q.full) return T(int(0));
    const auto& mssv(r.next(ms));
    return r.full ? p.next(d - ms) + ms : T(int(0));
  }
  P p;
  idFeeder<T> q;
  idFeeder<T> r;
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
  int status(77);
  if(argc < 2) std::cerr << argv[0] << " <status>? : continue with ";
  if(1 < argc) status = std::atoi(argv[1]);
  std::cerr << argv[0] << " " << status << std::endl;
  assert(status);
  // N.B. doing thirds on the stream causes (f(x), x, status) elimination.
  //      this is to make hypothesis () - structure itself is continuous.
  //      however, we can make also (f(x)) elimination also causes continuous
  //      () structures. There's differences between them the dimension
  //      original structure should have, however, if the original prediction is
  //      fair enough on counting prediction structure, we can bet only 1 dim.
  // N.B. Also, P0DFT eliminates causes number of the hyper torus whole,
  //      this is not needed in P0maxRank sub class because they treats
  //      better way them, also P1I, P012L because they treats any of the
  //      F_p register (non-)linear calculation.
  // N.B. We need PWalkBoth because there exists a_-1 is being attacked
  //      condition in laurent series. One of them are ok in that condition,
  //      If the attacker attacks both a_-1 and reverse(a_-1), half of the
  //      prediction fails in best effort, but whole of the case, one of the
  //      function estimation remains, so in whole in long range, it's ok
  //      in feeding one by one sliding window meaning.
  PWalkBoth<num_t, Pmss<num_t, P<num_t> > > p(Pmss<num_t, P<num_t> >(P<num_t>(abs(status)), abs(status)));
  auto  q(p);
  num_t d(int(0));
  auto  dd(d);
  auto  M(d);
  auto  Mc(d);
  auto  S(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    const auto D(d * M);
    if(status < 0) {
      // XXX: copy cat on 1 != const.
      const auto one(p.next(d) * q.next(num_t(int(1)) / d));
      std::cout << D << ", " << (M = (Mc = max(Mc, abs(one))) == num_t(int(0)) ? d : one / Mc * d) << ", " << (S += D) << std::endl << std::flush;
    } else
      std::cout << D << ", " << (M = p.next(d)) << ", " << (S += D) << std::endl << std::flush;
  }
  return 0;
}

