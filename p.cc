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
#include "p2.hh"

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::string s;
  int status(32);
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
  // N.B. We take PBlur for blurring prediction by status length.
  //      Making prediction twice with this might causes only the
  //      status the original stream have and only the input stream
  //      the argv[1] insist is the matter.
  //      However, even so, there even also exists the jammer to this predictor.
  //      When them, they might be observed as status out of reach or
  //      non lebesgue measurable condition or simple jamming downto half of the
  //      argv[1] status.
  //      In the theoretical reason, this is the only possible stability fix.
  // N.B. original PBlur is too heavy to run with large status length,
  //      we can remedy them by Ppad with argv[2] by decomposing status length.
  // N.B. rewrote Ppad for x -&gt; x^2 virtual replacement.
  Ppretry<num_t, Ppad<num_t, PBlur<num_t> > > p(Ppad<num_t, PBlur<num_t> >(PBlur<num_t>(abs(status)), abs(status), abs(status) * 3));
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

