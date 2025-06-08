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
#include <sys/resource.h>
#if defined(_GETENTROPY_)
#include <unistd.h>
#endif

#include <random>

#include "lieonn.hh"
typedef myfloat num_t;

static inline num_t fl(int x, int M) {
  return num_t(x) / num_t(M + 1);
}

int main(int argc, const char* argv[]) {
  assert(1 < argc);
  std::cout << std::setprecision(30);
  std::random_device r;
  std::default_random_engine er(r());
  std::mt19937 mt(r());
  std::ranlux24 rl24(r());
  std::ranlux48 rl48(r());
  std::knuth_b kb(r());
  std::uniform_int_distribution<int> ud(0, 0x2000);
  std::string s;
  if(argv[1][0] == 'r' || argv[1][0] == 'R')
    while(true) {
      if(argv[1][1] == 'b') {
        // XXX: ud(...) <= 2 case is not handled.
        std::cout << num_t(int(arc4random_uniform(3)) - 1) << ",";
        std::cout << num_t(ud(er) % 3 - 1) << ",";
        std::cout << num_t(ud(mt) % 3 - 1) << ",";
        std::cout << num_t(ud(rl24) % 3 - 1) << ",";
        std::cout << num_t(ud(rl48) % 3 - 1) << ",";
        std::cout << num_t(ud(kb) % 3 - 1);
#if defined(_GETENTROPY_)
        if(argv[1][0] == 'R') {
          uint8_t rnd[4];
          for(int i = 0; i < 1600000 / 4; i ++)
            getentropy(rnd, sizeof rnd);
          std::cout << "," << num_t(((int32_t&)(*rnd) % 3) - 1);
        }
#endif
      } else {
        std::cout << fl(int(arc4random_uniform(0x2001)) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(er) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(mt) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(rl24) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(rl48) - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(kb) - 0x1000, 0x1000);
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
  else if(argv[1][0] == 'f') {
    SimpleVector<num_t> b(std::atoi(argv[2]));
    int t(0);
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ss(s);
      ss >> b[(t ++) % b.size()];
      if(! (t %= b.size())) std::cout << b;
      std::cout << std::flush;
    }
  } else if(argv[1][0] == 'h') {
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
  } else if(argv[1][0] == 'z') {
    SimpleVector<num_t> b(std::atoi(argv[2]));
    b.O();
    int t(0);
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ss(s);
      ss >> b[b.size() - 1];
      for(int i = b.size() - 1; 0 < i; i --)
        std::cout << b[i] << ", ";
      std::cout << b[0] << std::endl << std::flush;
      for(int i = 0; i < b.size() - 1; i ++)
        b[i] = b[i + 1];
    }
  } else {
    int t(0);
    std::vector<num_t> b;
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
        const auto& d(in[0]);
        vector<num_t> M;
        M.reserve(in.size() - 1);
        for(int i = 1; i < in.size(); i ++)
          M.emplace_back(d == num_t(int(0)) ? d : in[i] / d);
        if(M.size() == b.size()) {
          const auto res(pSubesube<num_t>(d, make_pair(M, b), t ++));
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
      case 't': {
        string a2(argv[2]);
        std::stringstream ss(a2);
        num_t tt(int(0));
        ss >> tt;
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (in[i] * tt) << ", ";
        std::cout << (in[in.size() - 1] * tt) << std::endl;
        break;
      } case 'k':
        if(t % std::atoi(argv[2])) break;
        std::cout << s << std::endl;
        break;
      case 'G': {
        for(int i = 1; i < in.size(); i ++) in[0] += in[i];
        std::cout << in[0] << std::endl;
        break;
      } deafult:
        assert(0 && "no such command.");
      }
      std::cout << std::flush;
      if(argv[1][0] != 's' || !b.size()) b = in;
      t ++;
    }
  }
  return 0;
}

