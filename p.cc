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
#include "lieonn.hh"
typedef myfloat num_t;

#if defined(_FLOAT_BITS_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if defined(_FLOAT_BITS_)
#define int int64_t
#endif
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
  // N.B. rewrote Ppad for x -&gt; x^(2/3) virtual replacement.
  // N.B. even we work with 2 of the range, they causes also vulnerable to
  //      least common multiply period timing attack.
  // N.B. however, lcm rapidly increase if we specify multiple of the argv.
  //      so we should pass argv as to be (pred len) < (argv[1]) ... (argv[n]),
  //      argv[k]!=argv[m] (k != m)
  // N.B. any of the predictors has its jammer, so we can say we did best if
  //      once produced prediction and its input, then, repredict with
  //      same input, antoher argument is seems better one.
  // XXX: 2^2^6 : 2^7^2 causes R^11 reduce R^6 causes 7*7-1 == 48.
  // N.B. if each input has 1 bit information, the dimension which have only
  //      deterministic is smaller than 4 points, add const., we get 5 dimension
  //      for only slightly have non deterministic composites.
  //      otherwise, if each variable point has a separatable information,
  //      we get 5 dimension for slightly, add const., we get 6 dimension for
  //      non-commutatives, also, 11 dimension for commutatives.
  // XXX: however, if the input points cannot get separated, or dimension
  //      larger than them causes same in the meaning of combinations on
  //      certain {f}, mare condition continues.
  assert(1 < argc && (argv[1][0] == '+' || argv[1][0] == '-'));
  std::cerr << argv[0] << " " << (argv[1][0] == '-' ? "-" : "+") << std::endl;
  PBond<num_t, P0maxRank<num_t> > p(P0maxRank<num_t>(), argv[1][0] == '-' ? 3 : 7);
  PBond<num_t, P1I<num_t> > q(P1I<num_t>(argv[1][0] == '-' ? 1 : 3), argv[1][0] == '-' ? 3 : 15);
  std::cout << std::setprecision(30);
  std::string s;
  num_t d(int(0)); auto  M(d);
  while(std::getline(std::cin, s, '\n')) {
    std::stringstream ins(s);
    ins >> d;
    std::cout << d * M << ", ";
    std::cout << (M = (p.next(d) + q.next(d)) / num_t(int(2))) << std::endl << std::flush;
  }
  return 0;
}

