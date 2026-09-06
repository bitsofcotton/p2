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
#if defined(_OPENMP)
#include <omp.h>
#endif
#if defined(_GETENTROPY_)
#include <unistd.h>
#endif

#if !defined(_OLDCPP_)
#include <random>
#if defined(_PERSISTENT_)
# if !defined(_FLOAT_BITS_)
#  define int ssize_t
# elif _FLOAT_BITS_ == 64
#  define int int32_t
# elif _FLOAT_BITS_ == 128
#  define int int64_t
# else
#  error Cannot handle PERSISTENT option
# endif
#endif
#endif

#include "lieonn.hh"
typedef myfloat num_t;
lieonn_t lieonn;

static inline num_t fl(int x, int M) {
  return (num_t(x % (2 * M + 1)) - num_t(M)) / num_t(M + 1);
}

#if !defined(_OLDCPP_) && defined(_PERSISTENT_)
# undef int
#endif
int main(int argc, const char* argv[]) {
#if !defined(_OLDCPP_) && defined(_PERSISTENT_)
# if !defined(_FLOAT_BITS_)
#  define int ssize_t
# elif _FLOAT_BITS_ == 64
#  define int int32_t
# elif _FLOAT_BITS_ == 128
#  define int int64_t
# else
#  error Cannot handle PERSISTENT option
# endif
#endif
  std::cout << std::setprecision(30);
  std::string s;
  int   t(0);
  lieonnStaticInit();
  if(argc < 2) goto usage;
  switch(argv[1][0]) {
  case 'r': case 'R': {
    // N.B. also [complex(rand,rand)/abs(...), ...] series works better.
    //      with IDFT/DFT, this is the analogy of output index shuffling.
#if !defined(_OLDCPP_)
    std::random_device r;
    std::default_random_engine er(r());
    std::mt19937 mt(r());
    std::ranlux24 rl24(r());
    std::ranlux48 rl48(r());
    std::knuth_b kb(r());
    std::uniform_int_distribution<int> ud(0, 0x2000);
#endif
    const char sw(2 < argc ? argv[2][0] : '0');
/*
#if defined(_ARCFOUR_)
    if(3 < argc) hardenR<num_t, arc4random, 512>(std::atoi(argv[3]));
#else
    if(3 < argc) hardenR<num_t, random, 32>(std::atoi(argv[3]));
#endif
*/
    const bool jflip(argv[1][0] == 'R');
    while(true) {
      // N.B. rand < 0x2001 case isn't handled.
      switch(sw) {
        case '0': {
#if defined(_ARCFOUR_)
         std::cout << (jflip ? num_t(arc4random() & 1 ? 1 : - 1) : fl(arc4random_uniform(0x2001), 0x1000) );
#else
         std::cout << (jflip ? num_t(random() & 1 ? 1 : - 1) : fl(random(), 0x1000) );
#endif
         break; }
#if !defined(_OLDCPP_)
        case '1':
          std::cout << (jflip ? num_t(ud(er) & 1 ? 1 : - 1) : fl(ud(er), 0x1000) );
          break;
        case '2':
          std::cout << (jflip ? num_t(ud(mt) & 1 ? 1 : - 1) : fl(ud(mt), 0x1000) );
          break;
        case '3':
          std::cout << (jflip ? num_t(ud(rl24) & 1 ? 1 : - 1) : fl(ud(rl24), 0x1000) );
          break;
        case '4':
          std::cout << (jflip ? num_t(ud(rl48) & 1 ? 1 : - 1) : fl(ud(rl48), 0x1000) );
          break;
        case '5':
          std::cout << (jflip ? num_t(ud(kb) & 1 ? 1 : - 1) : fl(ud(kb), 0x1000) );
          break;
#endif
#if defined(_GETENTROPY_)
        case '6': {
          uint8_t rnd[4];
          for(int i = 0; i < 1600000 / 4 / 512; i ++)
            getentropy(rnd, sizeof rnd);
          std::cout << (jflip ? num_t((uint32_t&)(*rnd) & 1 ? 1 : - 1) : fl((uint32_t&)(*rnd), 0x1000) );
          break;
        }
#endif
/*
        case '7':
#if defined(_ARCFOUR_)
          std::cout << (jflip ? num_t(hardenR<num_t, arc4random, 512>() & 1 ? 1 : - 1) : fl(hardenR<num_t, arc4random, 512>(), 0x1000) );
#else
          std::cout << (jflip ? num_t(hardenR<num_t, random, 32>() & 1 ? 1 : - 1) : fl(hardenR<num_t, random, 32>(), 0x1000) );
#endif
          break;
*/
        default: goto usage;
      }
      std::cout << endl;
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
        std::cout << w[i] << endl;
      std::cout << std::flush;
    }
    break;
  } case 'z': {
    while(std::getline(std::cin, s, '\n')) {
      SimpleVector<num_t> in(s2sv<num_t>(s));
      if(argv[1][1] == '\0')
        for(int i = 0; i < std::atoi(argv[2]); i ++)
          for(int j = 0; j < in.size(); j ++)
            std::cout << in[j] << ", " << std::flush;
      else if(argv[1][1] == '-')
        for(int i = 0; i < in.size() / std::atoi(argv[2]); i ++) {
          num_t x(in[i]);
          std::vector<num_t> buf;
          buf.reserve(std::atoi(argv[2]));
          for(int j = 1; j < std::atoi(argv[2]); j ++) {
            x += in[i + j * (in.size() / std::atoi(argv[2]))];
            buf.emplace_back(in[i + j * (in.size() / std::atoi(argv[2]))]);
          }
          sort(buf.begin(), buf.end());
          std::cout << (abs(x) == num_t(int(0)) ? buf[buf.size() / 2] : x) << ", " << std::flush;
        }
      std::cout << std::endl;
    }
    break;
  } case 'A': {
    int M(0);
    while(std::getline(std::cin, s, '\n')) {
      M = max(M, s2sv<num_t>(s).size());
      std::cout << s << std::endl;
    }
    for(int i = 0; i < M - 1; i ++) std::cout << num_t(int(1)) << ", ";
    std::cout << num_t(int(1)) << std::endl;
    break;
  } case 'P': case 'Y': {
    if(argv[1][1] == '-') {
      for(int i = 2; i < argc; i ++) {
        std::vector<SimpleMatrix<num_t> > bitimg;
        if(! loadp2or3<num_t>(bitimg, argv[i], false)) continue;
        for(int ii = 0; ii < bitimg.size(); ii ++)
          for(int jj = 0; jj < bitimg[ii].rows(); jj ++)
            for(int kk = 0; kk < bitimg[ii].cols(); kk ++)
              std::cout << unOffsetHalf<num_t>(bitimg[ii](jj, kk)) << ", ";
        std::cout << endl << std::flush;
      }
      break;
    }
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ss(s);
      SimpleVector<num_t> w;
      ss >> w;
      const int sq0(sqrt(num_t(argv[1][0] == 'Y' ? w.size() / 3 : w.size())));
      const int sq((sq0 + 1) * (sq0 + 1) == (argv[1][0] == 'Y' ? w.size() / 3 :
        w.size()) ? sq0 + 1 : sq0);
      vector<SimpleMatrix<num_t> > p;
      p.emplace_back(SimpleMatrix<num_t>(sq, sq));
      if(argv[1][0] == 'Y') {
        p.emplace_back(SimpleMatrix<num_t>(sq, sq));
        p.emplace_back(SimpleMatrix<num_t>(sq, sq));
      }
      for(int j = 0; j < p.size(); j ++)
        for(int i = 0; i < p[0].rows(); i ++)
          p[j].row(i) = offsetHalf<num_t>(w.subVector(
            j * p[0].cols() * p[0].rows() + i * p[0].cols(), p[0].cols()));
      if(! savep2or3<num_t>((std::string("rand_pgm-") + to_string(t ++) +
        std::string(argv[1][0] == 'Y' ? ".ppm" : ".pgm")).c_str(), p) ) {
        std::cerr << "failed to save." << endl;
        // if saveing file failed, safe to exit.
        break;
      }
    }
    break;
  } case 'Q': {
    char buf;
    // cf. thanks to https://github.com/yyagi8864/smfspec via google however
    //     we should have SMFv1 datasheet as a reference.
    std::cout << "MThd";
    // block lengtn
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x06)), sizeof(char));
    // SMFv1
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x01)), sizeof(char));
    // track number
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x02)), sizeof(char));
    // resolution
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x30)), sizeof(char));
    std::cout << "MTrk";
    // block length
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x0b)), sizeof(char));
    // tempo
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0xff)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x51)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x03)), sizeof(char));
    // 120
    std::cout.write(const_cast<const char*>(&(buf = 0x07)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0xa1)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x20)), sizeof(char));
    // end track
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0xff)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x2f)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout << "MTrk";
    std::vector<char> track;
    const char tbl0[] = {0, 2, 4, 5, 7, 9, 11};
    const char  base(60);
    SimpleVector<char> walk;
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ss(s);
      SimpleVector<num_t> w;
      ss >> w;
      if(walk.size() != w.size()) { walk.resize(w.size()); walk.O(); }
      vector<bool> absent;
      absent.resize(w.size(), false);
      for(int i = 0; i < w.size(); i ++) {
        if(w[i] < num_t(int(0))) {
          absent[i] = true;
          continue;
        }
        w[i]  = abs(w[i]);
        w[i] -= absfloor(w[i]);
        walk[i] += int(w[i] * num_t(int(36))) % 6 - 3;
        walk[i] %= sizeof(tbl0) / sizeof(char);
        // no delay track0 note on
        track.emplace_back(0x00);
        track.emplace_back(0x90);
        track.emplace_back(tbl0[walk[i]] + base);
        // velocity.
        track.emplace_back(0x7f);
      }
      for(int i = 0, ii = 0; i < w.size(); i ++) if(! absent[i]) {
        // delay 30
        track.emplace_back(ii ++ ? 0x00 : 0x30);
        // note off
        track.emplace_back(tbl0[walk[i]] + base);
        track.emplace_back(0x00);
      }
    }
    // block length
    const int length(4 + track.size());
    std::cout.write(const_cast<const char*>(&(buf = (length >> 24) & 0xff)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = (length >> 16) & 0xff)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = (length >>  8) & 0xff)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = length & 0xff)), sizeof(char));
    // std::cout.write(const_cast<const char*>(&(buf = 0x18)), sizeof(char));
    // program change
    /*
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0xc0)), sizeof(char));
    // cf. https://ja.wikipedia.org/wiki/General_MIDI
    //std::cout.write(const_cast<const char*>(&(buf = 117)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x75)), sizeof(char));
     */
    for(int i = 0; i < track.size(); i ++)
      std::cout.write(const_cast<const char*>(&track[i]), sizeof(char));
    // end track
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0xff)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x2f)), sizeof(char));
    std::cout.write(const_cast<const char*>(&(buf = 0x00)), sizeof(char));
    break;
  } case 'Z': case 'X': {
    std::vector<std::string> buf;
    while(std::getline(std::cin, s, '\n')) buf.emplace_back(s);
    std::vector<std::vector<num_t> > sbuf;
    std::vector<num_t> M;
    std::vector<num_t> m;
    sbuf.reserve(buf.size());
    for(int i = 0; i < buf.size(); i ++) {
      s = buf[i];
      int cnt(1);
      for(int i = 0; i < s.size(); i ++)
        if(s[i] == ',') cnt ++;
      std::vector<num_t> in;
      in.resize(cnt);
      for(int i = 0, j = 0; i < s.size(); i ++) {
        std::stringstream ins(s.substr(i, s.size() - i));
        ins >> in[j ++];
        for( ; s[i] != ',' && i < s.size(); i ++) ;
      }
      sbuf.emplace_back(move(in));
    }
    for(int i = 0; i < sbuf.size(); i ++) {
      if(M.size() < sbuf[i].size()) {
        M.resize(sbuf[i].size(), num_t(int(0)));
        m.resize(sbuf[i].size(), num_t(int(0)));
      }
      for(int j = 0; j < sbuf[i].size(); j ++) {
        M[j] = max(M[j], sbuf[i][j]);
        m[j] = min(m[j], sbuf[i][j]);
      }
    }
    if(argv[1][1] == '-') {
      num_t MM(M[0]);
      num_t mm(m[0]);
      for(int i = 0; i < M.size(); i ++) {
        MM = max(M[i], MM);
        mm = min(m[i], mm);
      }
      for(int i = 0; i < M.size(); i ++) {
        M[i] = MM;
        m[i] = mm;
      }
    }
    if(argv[1][0] == 'Z') {
      for(int i = 0; i < M.size(); i ++)
        if((M[i] = max(abs(M[i]), abs(m[i]))) == num_t(int(0)))
          M[i] = num_t(int(1));
      for(int i = 0; i < sbuf.size(); i ++) {
        for(int j = 0; j < sbuf[i].size() - 1; j ++)
          std::cout << (sbuf[i][j] / M[j]) << ", ";
        std::cout << (sbuf[i][sbuf[i].size() - 1] / M[sbuf[i].size() - 1]) << endl;
      }
      std::cout << std::flush;
    } else if(argv[1][0] == 'X') {
      for(int i = 0; i < M.size(); i ++)
        if(M[i] == m[i]) M[i] = m[i] + num_t(int(1));
      for(int i = 0; i < sbuf.size(); i ++) {
        for(int j = 0; j < sbuf[i].size() - 1; j ++)
          std::cout << ((sbuf[i][j] - (m[j] + M[j]) / num_t(int(2))) /
            (M[j] - m[j]) * num_t(int(2)) ) << ", ";
        const int j(sbuf[i].size() - 1);
        std::cout << ((sbuf[i][j] - (m[j] + M[j]) / num_t(int(2))) /
          (M[j] - m[j]) * num_t(int(2)) ) << endl;
      }
    }
    break;
  } case 'x': case 'j': {
    while(std::getline(std::cin, s, '\n'))
      for(int i = 0; i < s.size(); i ++) {
        if(argv[1][0] == 'x') {
          if(s[i] == '0') std::cout << (- num_t(1)) << endl;
          else if(s[i] == '1') std::cout << num_t(1) << endl;
        } else {
          if('0' <= s[i] && s[i] <= '9')
            std::cout << (num_t(s[i] - '0') - num_t(int(15)) / num_t(int(2)))
              << endl;
          else if('a' <= s[i] && s[i] <= 'f')
            std::cout << (num_t(s[i] - 'a' + 10) - num_t(int(15)) /
              num_t(int(2)) ) << endl;
          else if('A' <= s[i] && s[i] <= 'F')
            std::cout << (num_t(s[i] - 'A' + 10) - num_t(int(15)) /
              num_t(int(2)) ) << endl;
        }
      }
    break;
  } case 'L': {
    std::ifstream left(argv[2]);
    std::ifstream right(argv[3]);
    bool loop(true);
    while(1) {
      if(! std::getline(left,  s)) break;
      std::cout << s << ", ";
      if(! std::getline(right, s)) break;
      std::cout << s << endl << std::flush;
    }
    left.close();
    right.close();
    break;
  } case 'W': {
    std::string ss;
    while(std::getline(std::cin, s, '\n')) ss += s;
    const int len(argv[1][1] == '\*' ? int(num_t(ss.size()) / log(num_t(ss.size())) * log(num_t(int(2))) ) : loop22<num_t>() + infBase() * 2);
    for(int i = 0; i < len; i ++) {
      for(int j = 0; j < ss.size() / len; j ++) {
        unsigned char ch(ss[i * (ss.size() / len) + j]);
        for(int k = 0; k < 8; k ++, ch <<= 1)
          std::cout << (ch & 0x80 ? num_t(int(1)) : - num_t(int(1)) ) << ", ";
      }
      std::cout << std::endl;
    }
    break;
  } default: {
    SimpleVector<num_t> b;
    std::vector<int> bf;
    std::vector<int> bg;
    num_t tt(int(0));
    {
      std::stringstream ss(2 < argc ? argv[2] : "");
      ss >> tt;
    }
    while(std::getline(std::cin, s, '\n')) {
      SimpleVector<num_t> in(s2sv<num_t>(s));
      if(in.size() != b.size()) { b.entity.resize(in.size(), num_t(int(0)) ); }
      switch(argv[1][0]) {
      case 'S':
        if(t < std::atoi(argv[2])) break;
        std::cout << s << endl;
        break;
      case 'd':
        for(int i = 0; i < b.size() - 1; i ++)
          std::cout << (in[i] - b[i]) << ", ";
        std::cout << (in[in.size() - 1] - b[b.size() - 1]) << endl;
        break;
      case 's':
        for(int i = 0; i < b.size() - 1; i ++)
          std::cout << (in[i] += b[i]) << ", ";
        std::cout << (in[in.size() - 1] += b[b.size() - 1]) << endl;
        break;
      case 'l':
        if(argv[1][1] == 'c') {
          for(int i = 0; i < in.size() - 2; i ++)
            std::cout << in[i] << ", ";
          std::cout << in[in.size() - 2] << endl;
        } else if(argv[1][1] == 'H') {
          for(int i = 0; i < in.size() / 2 - 1; i ++)
            std::cout << in[i] << ", ";
          const int i(in.size() / 2 - 1);
          std::cout << (0 <= i ? in[i] : num_t(int(0))) << endl;
        } else {
          for(int i = 2; i < argc - 1; i ++)
            std::cout << (std::atoi(argv[i]) < in.size() ?
              in[std::atoi(argv[i])] : num_t(int(0)) ) << ", ";
          std::cout << (std::atoi(argv[argc - 1]) < in.size() ?
            in[std::atoi(argv[argc - 1])] : num_t(int(0)) ) << endl;
        }
        break;
      case 't': {
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << in[i] * tt << ", ";
        std::cout << in[in.size() - 1] * tt << endl;
        break;
      } case 'o': {
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << in[i] + tt << ", ";
        std::cout << in[in.size() - 1] + tt << endl;
        break;
      } case 'k':
        if(t % std::atoi(argv[2])) break;
        std::cout << s << endl;
        break;
      case 'G':
        for(int i = 1; i < in.size(); i ++) in[0] += in[i];
        std::cout << (in[0] /= num_t(int(in.size()))) << endl;
        break;
      case 'T': {
        if(bf.size() < in.size()) {
          bf.resize(in.size(), 0);
          bg.resize(in.size(), 0);
        }
        assert(bf.size() == in.size());
        for(int i = 0; i < in.size(); i ++)
          std::cout << (num_t(num_t(int(0)) < in[i] &&
            (in[i] < num_t(int(1)) || argv[1][1] == '+') ? ++ bf[i] : bf[i]) /
              num_t(max(int(1), in[i] == num_t(int(0)) ? bg[i] : ++ bg[i])) -
                num_t(int(1)) / num_t(int(2))) * num_t(int(2)) << ", " <<
                  bg[i] << ", ";
        std::cout << (t + 1) << endl;
        break;
#if !defined(_OLDCPP_)
      } case 'F': {
#if defined(_FLOAT_BITS_) || defined(_PERSISTENT_)
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << double(in[i]) << ", ";
        std::cout << double(in[in.size() - 1]) << endl;
#else
        for(int i = 0; i < in.size() - 1; i ++) {
          SimpleFloat<unsigned int, DUInt<unsigned int, sizeof(unsigned int) * 8>, sizeof(unsigned int) * 8, int> f(int(in[i] * pow(myfloat(2), myfloat(tt)) ));
          std::cout << (f >>= tt) << ", ";
        }
        SimpleFloat<unsigned int, DUInt<unsigned int, sizeof(unsigned int) * 8>, sizeof(unsigned int) * 8, int> f(int(in[in.size() - 1] * pow(myfloat(2), myfloat(tt)) ));
        std::cout << (f >>= tt) << endl;
#endif
        break;
#endif
      } case 'O': {
        for(int i = 0; i < in.size() / 2 - 1; i ++)
          std::cout << (in[i] + in[i + in.size() / 2]) * (argv[1][1] == '+' ?
            num_t(int(1)) : in[i + in.size() / 2]) << ", ";
        const int i(in.size() / 2 - 1);
        std::cout << (in[i] + in[i + in.size() / 2]) * (argv[1][1] == '+' ?
          num_t(int(1)) : in[i + in.size() / 2]) << endl;
        break;
      } case 'w': {
        for(int i = 0; i < in.size() / 8; i ++) {
          unsigned char w(0);
          for(int j = 0; j < 8; j ++) {
            w <<= 1;
            if(num_t(int(0)) <= in[i * 8 + j]) w ++;
          }
          std::cout << char(w) << flush;
        }
        std::cout << endl;
        break;
      } case 'a': {
        if(argv[1][1] == '-') {
          for(int i = 0; i < in.size() / 2 - 1; i ++)
            std::cout << (sgn<num_t>(in[i]) * in[i + in.size() / 2]) << ", ";
          const int i(in.size() / 2 - 1);
          std::cout << (sgn<num_t>(in[i]) * in[i + in.size() / 2]) << endl << flush;
          break;
        }
        // N.B. talk with gemini 2026/09 early, dual modal offset E[E[X],E[Y]].
        num_t E(int(0));
        num_t bE(int(1));
        while(SimpleMatrix<num_t>().epsilon() <= abs(E - bE)) {
          bE = E;
          for(int i = 0; i < in.size(); i ++) E += in[i];
          E /= num_t(in.size());
          num_t EL(int(0));
          num_t ER(int(0));
          int   cl(0);
          int   cr(0);
          for(int i = 0; i < in.size(); i ++)
            if(in[i] < E) { EL += in[i]; cl ++; }
            else { ER += in[i]; cr ++; }
          if(cl) EL /= num_t(cl);
          if(cr) ER /= num_t(cr);
          E = (EL + ER) / num_t(int(2));
        }
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (in[i] - E) << ", ";
        std::cout << (in[in.size() - 1] - E) << std::endl;
        break;
      } case 'V':
        for(int i = 0; i < in.size(); i ++) std::cout << in[i] << endl;
        break;
      default: goto usage;
      }
      std::cout << std::flush;
      b = in;
      t ++;
    }
  } }
  lieonnStaticDestroy();
  return 0;
 usage:
  lieonnStaticDestroy();
  cerr << "Usage:" << endl;
  cerr << " *** reformation part ***" << endl;
  cerr << "# take delta     on input stream" << endl << argv[0] << " d" << endl;
  cerr << "# take summation on input stream" << endl << argv[0] << " s" << endl;
  cerr << "# take skip      on input stream" << endl << argv[0] << " k <interval>" << endl;
  cerr << "# take skip head on input stream" << endl << argv[0] << " S <margin>" << endl;
  cerr << "# take reverse   on input stream" << endl << argv[0] << " v" << endl;
  cerr << "# pick {0,1} or [0-9a-f] str on input stream" << endl << argv[0] << " [xj]" << endl;
  cerr << "# take reform [-1,1] on input stream" << endl << argv[0] << " X-?" << endl;
  cerr << "# take reform [-1,1] on input stream without offset" << endl << argv[0] << " Z-?" << endl;
  cerr << "# take picked column      on input stream (H for first half, G for last half, c for chop)" << endl << argv[0] << " l[cHG]? <col0index> ..." << endl;
  cerr << "# take difference affter math on input stream first half to last half" << endl << argv[0] << " O+?" << endl;
  cerr << "# take duplicate          on input stream (- for invertion)" << endl << argv[0] << " z-? <column number>" << endl;
  cerr << "# take multiply each      on input stream" << endl << argv[0] << " t <ratio>" << endl;
  cerr << "# take offset   each      on input stream" << endl << argv[0] << " o <offset>" << endl;
  cerr << "# take opposite type output string each on input stream" << endl << argv[0] << " F <bit number>" << endl;
  cerr << "# offset from average with hypothesis input is dual modal." << endl << argv[0] << " a" << endl;
  cerr << endl << " *** PRNG part ***" << endl;
  cerr << "# make [-1,1] PRNG stream" << endl << argv[0] << " r <proto>" << endl;
  cerr << "# make {-1,1} PRNG stream" << endl << argv[0] << " R <proto>" << endl;
  cerr << endl << " *** vector operation part ***" << endl;
  cerr << "# input serial stream to vector stream" << endl << argv[0] << " f <dimension>" << endl;
  cerr << "# input vector stream to serial stream" << endl << argv[0] << " h" << endl;
  cerr << "# input vector stream to pgm graphics output or its reverse" << endl << argv[0] << " [PY]-?" << endl;
  cerr << "# input vector stream to midi output" << endl << argv[0] << " Q" << endl;
  cerr << endl << " *** other part ***" << endl;
  cerr << "# pair of files load into same line columns (use /dev/stdin if you need)" << endl << argv[0] << " L <left> <right>" << endl;
  cerr << "# show output statistics it's 0<x<1 (+ for 0<x)" << endl << argv[0] << " T+?" << endl;
  cerr << "# string2csv (* for masp chain)" << endl << argv[0] << " W*?" << endl;
  cerr << "# csv2string" << endl << argv[0] << " w" << endl;
  cerr << "# add all 1 csv footer" << endl << argv[0] << " A" << endl;
  cerr << "# csv to serialize only single column" << endl << argv[0] << " V" << endl;
  cerr << endl << " *** graphics test ***" << endl;
  cerr << argv[0] << " P- ... | " << argv[0] << " A | " << argv[0] << " lc | <predictors> | " << argv[0] << " a | " << argv[0] << " V | " << argv[0] << " Z | " << argv[0] << " f ... | " << argv[0] << " [PY]" << endl;
  cerr << " *** string test ***" << endl;
  cerr << "cat | " << argv[0] << " W | " << argv[0] << " A | " << argv[0] << " lc | <predictors> | " << argv[0] << " a | " << argv[0] << " w" << endl;
  cerr << " *** to hear some residue ***" << endl;
  cerr << argv[0] << " r ... | tee 0 | <predictors> > /dev/null" << endl;
  cerr << "catgr ... < 0 | grep -v nan | grep -v \"[ 0,  0,  0]\" | uniq | grep ] | p Q > out.mid" << endl;
  return - 1;
}

