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
#include <stdint.h>
#if defined(_GETENTROPY_)
#include <unistd.h>
#endif

#if !defined(_OLDCPP_)
#include <random>
#define int int32_t
//#define int int64_t
#endif

#include "lieonn.hh"
typedef myfloat num_t;

static inline num_t fl(int x, int M) {
  return num_t(x) / num_t(M + 1);
}

#if !defined(_OLDCPP_)
#undef int
#endif
int main(int argc, const char* argv[]) {
#if !defined(_OLDCPP_)
#define int int32_t
//#define int int64_t
#endif
  assert(1 < argc);
  std::cout << std::setprecision(30);
  std::string s;
  int   t(0);
  switch(argv[1][0]) {
  case 'r': case 'R': {
#if !defined(_OLDCPP_)
    std::random_device r;
    std::default_random_engine er(r());
    std::mt19937 mt(r());
    std::ranlux24 rl24(r());
    std::ranlux48 rl48(r());
    std::knuth_b kb(r());
    std::uniform_int_distribution<int> ud(0, 0x2000);
#endif
    while(true) {
      if(argv[1][1] == 'b') {
#if defined(_ARCFOUR_)
        std::cout << num_t(int(arc4random_uniform(3)) - 1);
#else
        std::cout << num_t(int(random() % 3) - 1);
#endif
#if !defined(_OLDCPP_)
        std::cout << "," << num_t(ud(er) % 3 - 1) << ",";
        std::cout << num_t(ud(mt) % 3 - 1) << ",";
        std::cout << num_t(ud(rl24) % 3 - 1) << ",";
        std::cout << num_t(ud(rl48) % 3 - 1) << ",";
        std::cout << num_t(ud(kb) % 3 - 1);
#endif
#if defined(_GETENTROPY_)
        if(argv[1][0] == 'R') {
          uint8_t rnd[4];
          for(int i = 0; i < 1600000 / 4; i ++)
            getentropy(rnd, sizeof rnd);
          std::cout << "," << num_t(((int32_t&)(*rnd) % 3) - 1);
        }
#endif
      } else if(argv[1][1] == 'B') {
#if defined(_ARCFOUR_)
        std::cout << num_t(int(arc4random() & 1)) * num_t(int(2)) - num_t(int(1));
#else
        std::cout << num_t(int(random() & 1)) * num_t(int(2)) - num_t(int(1));
#endif
#if !defined(_OLDCPP_)
        std::cout << "," << num_t(ud(er) & 1) * num_t(int(2)) - num_t(int(1)) << ",";
        std::cout << num_t(ud(mt) & 1) * num_t(int(2)) - num_t(int(1)) << ",";
        std::cout << num_t(ud(rl24) & 1) * num_t(int(2)) - num_t(int(1)) << ",";
        std::cout << num_t(ud(rl48) & 1) * num_t(int(2)) - num_t(int(1)) << ",";
        std::cout << num_t(ud(kb) & 1) * num_t(int(2)) - num_t(int(1));
#endif
#if defined(_GETENTROPY_)
        if(argv[1][0] == 'R') {
          uint8_t rnd[4];
          for(int i = 0; i < 1600000 / 4; i ++)
            getentropy(rnd, sizeof rnd);
          std::cout << "," << num_t(((int32_t&)(*rnd) & 1) - 1) * num_t(int(2)) - num_t(int(1));
        }
#endif
      } else {
#if defined(_ARCFOUR_)
        std::cout << fl(int(arc4random_uniform(0x2001)) - 0x1000, 0x1000);
#else
        std::cout << fl(int(random() % 0x2001) - 0x1000, 0x1000);
#endif
#if !defined(_OLDCPP_)
        std::cout << "," << fl(ud(er) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(mt) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(rl24) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(rl48) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(kb) - 0x1000, 0x1000);
#endif
#if defined(_GETENTROPY_)
        if(argv[1][0] == 'R') {
          uint8_t rnd[4];
          for(int i = 0; i < 1600000 / 4; i ++)
            getentropy(rnd, sizeof rnd);
          // XXX: [-1,1[ case, we in fact need: [-1,1].
          std::cout << "," << fl(((uint32_t&)(*rnd) & 0x1fff) - 0x1000, 0x1000);
        }
#endif
      }
      std::cout << std::endl << std::flush;
    }
    break;
  } case 'm': {
#if !defined(_OLDCPP_)
    std::random_device r;
    std::default_random_engine er(r());
    std::mt19937 mt(r());
    std::ranlux24 rl24(r());
    std::ranlux48 rl48(r());
    std::knuth_b kb(r());
    std::uniform_int_distribution<int> ud(0, 0x2000);
#endif
    const char& sw(argv[1][1]);
    num_t d(t);
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ins(s);
      ins >> d;
      for(int i = 0; i < std::atoi(argv[2]); i ++) {
        switch(sw) {
          case '0':
#if defined(_ARCFOUR_)
            std::cout << (fl(int(arc4random_uniform(0x2001)) - 0x1000, 0x1000) + d) / num_t(int(2));
#else
            std::cout << (fl(int(random() % 0x2001) - 0x1000, 0x1000) + d) / num_t(int(2));
#endif
            break;
#if !defined(_OLDCPP_)
          case '1':
            std::cout << (fl(ud(er) - 0x1000, 0x1000) + d) / num_t(int(2));
            break;
          case '2':
            std::cout << (fl(ud(mt) - 0x1000, 0x1000) + d) / num_t(int(2));
            break;
          case '3':
            std::cout << (fl(ud(rl24) - 0x1000, 0x1000) + d) / num_t(int(2));
            break;
          case '4':
            std::cout << (fl(ud(rl48) - 0x1000, 0x1000) + d) / num_t(int(2));
            break;
          case '5':
            std::cout << (fl(ud(kb) - 0x1000, 0x1000) + d) / num_t(int(2));
            break;
#endif
#if defined(_GETENTROPY_)
          case '6': {
            uint8_t rnd[4];
            for(int i = 0; i < 1600000 / 4; i ++)
              getentropy(rnd, sizeof rnd);
            // XXX: [-1,1[ case, we in fact need: [-1,1].
            std::cout << (fl(((uint32_t&)(*rnd) & 0x1fff) - 0x1000, 0x1000) + d) / num_t(int(2));
            break;
          }
#endif
          default: assert(0 && "no such command");
        }
        if(i < std::atoi(argv[2]) - 1)
          std::cout << ", ";
        else
          std::cout << std::endl << std::flush;
      }
    }
    break;
  } case 'j': {
    pslip_t<num_t> pslip(argv[1][1] == '+' ? 7 : 0);
    num_t d(t);
    num_t M(d);
    idFeeder<num_t> in(argv[1][1] == '+' ? 7 : 0);
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ins(s);
      ins >> d;
      std::cout << (M *= d) << ", " << std::flush;
      std::cout <<
        (M = pSlipGulf0short<num_t>(in.next(d), pslip, t ++) ) <<
          ", " << d << std::endl << std::flush;
    }
    break;
  } case 'c': case 'C': {
    int& length(t);
    if(2 < argc) length = std::atoi(argv[2]);
    idFeeder<num_t> p(length);
    num_t d(t);
    num_t M(d);
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ins(s);
      ins >> d;
      std::cout << (argv[1][0] == 'C' ? d - M : d * M) << ", " << std::flush;
      std::cout << (M = p012next<num_t>(p.next(d)) ) << std::endl << std::flush;
    }
    break;
  } case 'f': {
    SimpleVector<num_t> b(std::atoi(argv[2]));
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ss(s);
      ss >> b[(t ++) % b.size()];
      if(! (t %= b.size())) std::cout << b;
      std::cout << std::flush;
    }
    break;
  } case 'h': {
    while(std::getline(std::cin, s, '\n')) {
      if(! s.size() || s[s.size() - 1] != ']') continue;
      s += string("\n");
      std::stringstream ss(s);
      SimpleVector<num_t> w;
      ss >> w;
      for(int i = 0; i < w.size(); i ++)
        std::cout << w[i] << std::endl;
      std::cout << std::flush;
    }
    break;
  } case 'z': {
    SimpleVector<num_t> b(std::atoi(argv[2]));
    b.O();
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ss(s);
      ss >> b[b.size() - 1];
      for(int i = b.size() - 1; 0 < i; i --)
        std::cout << b[i] << ", ";
      std::cout << b[0] << std::endl << std::flush;
      for(int i = 0; i < b.size() - 1; i ++)
        b[i] = b[i + 1];
    }
    break;
  } case 'P': {
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ss(s);
      SimpleVector<num_t> w;
      ss >> w;
      const int sq(sqrt(num_t(w.size())));
      vector<SimpleMatrix<num_t> > p;
      p.emplace_back(SimpleMatrix<num_t>(sq, sq));
      for(int i = 0; i < p[0].rows(); i ++)
        p[0].row(i) = binMargin<num_t>(offsetHalf<num_t>(w.subVector(i * p[0].cols(), p[0].cols())));
      if(! savep2or3<num_t>((std::string("rand_pgm-") + to_string(t ++) + std::string(".pgm")).c_str(), p) ) {
        std::cerr << "failed to save." << std::endl;
        // if saveing file failed, safe to exit.
        break;
      }
    }
    break;
#if defined(_ONEBINARY_)
  } case '0': {
    int& length(t);
    if(2 < argc) length = std::atoi(argv[2]);
    const bool chain(argv[1][1] == 'c');
    #include "../p0/p0.cc"
  } case '1': {
    int& stat(t);
    if(2 < argc) stat = std::atoi(argv[2]);
    const bool chain(argv[1][1] == 'c');
    #include "../p1/pp3.cc"
#endif
  } default: {
    std::vector<num_t> b;
    std::vector<int> bf;
    while(std::getline(std::cin, s, '\n')) {
      int cnt(1);
      for(int i = 0; i < s.size(); i ++)
        if(s[i] == ',') cnt ++;
      std::vector<num_t> in;
      in.resize(cnt);
      int i, j;
      for(i = 0, j = 0; i < s.size(); i ++) {
        std::stringstream ins(s.substr(i, s.size() - i));
        ins >> in[j ++];
        for( ; s[i] != ',' && i < s.size(); i ++) ;
      }
      if(argv[1][0] == 'Q') {
        const num_t& d(in[0]);
        vector<num_t> M;
        M.reserve(in.size() - 1);
        for(int i = 1; i < in.size(); i ++)
          M.emplace_back(d == num_t(int(0)) ? d : in[i] / d);
        if(M.size() == b.size()) {
          const pair<num_t, num_t> res(pSubesube<num_t>(d, make_pair(M, b), t ++));
          std::cout << res.first << ", " << res.second << std::endl << std::flush;
        } else
          std::cout << num_t(int(0)) << ", " << num_t(int(0)) << std::endl << std::flush;
        b = move(M);
        continue;
      }
      switch(argv[1][0]) {
      case 'S':
        if(t < std::atoi(argv[2])) break;
        std::cout << s << std::endl;
        break;
      case 'd':
        if(in.size() != b.size()) break;
        for(int i = 0; i < b.size() - 1; i ++)
          std::cout << (in[i] - b[i]) << ", ";
        std::cout << (in[in.size() - 1] - b[b.size() - 1]) << std::endl;
        break;
      case 's':
        if(in.size() != b.size()) break;
        for(int i = 0; i < b.size() - 1; i ++)
          std::cout << (b[i] += in[i]) << ", ";
        std::cout << (b[b.size() - 1] += in[in.size() - 1]) << std::endl;
        break;
      case 'i':
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (in[i] == num_t(int(0)) ?
            num_t(int(0)) : num_t(int(1)) / in[i]) << ", ";
        std::cout << (in[in.size() - 1] == num_t(int(0)) ?
          num_t(int(0)) : num_t(int(1)) / in[in.size() - 1]) << std::endl;
        break;
      case 'l':
        for(int i = 2; i < argc - 1; i ++)
          std::cout << in[std::atoi(argv[i])] << ", ";
        std::cout << in[std::atoi(argv[argc - 1])] << std::endl;
        break;
      case 't': case 'a': {
        string a2(2 < argc ? argv[2] : "");
        std::stringstream ss(a2);
        num_t tt(int(0));
        ss >> tt;
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (argv[1][0] == 'a' ? abs(in[i]) : in[i] * tt) << ", ";
        std::cout << (argv[1][0] == 'a' ? abs(in[in.size() - 1]) :
          in[in.size() - 1] * tt) << std::endl;
        break;
      } case 'k':
        if(t % std::atoi(argv[2])) break;
        std::cout << s << std::endl;
        break;
      case 'G': {
        for(int i = 1; i < in.size(); i ++) in[0] += in[i];
        std::cout << in[0] << std::endl;
        break;
      } case 'T': {
        if(bf.size() < in.size()) bf.resize(in.size(), 0);
        assert(bf.size() == in.size());
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (num_t(int(0)) <= in[i] && in[i] < num_t(int(1)) ?
            bf[i] : ++ bf[i]) << ", ";
        std::cout << (num_t(int(0)) <= in[in.size() - 1] &&
          in[in.size() - 1] < num_t(int(1)) ?
            bf[in.size() - 1] : ++ bf[in.size() - 1]) << ", " <<
              (++ t) << std::endl;
        break;
      } default:
        assert(0 && "no such command.");
      }
      std::cout << std::flush;
      if(argv[1][0] != 's' || !b.size()) b = in;
      t ++;
    }
  } }
  return 0;
}

