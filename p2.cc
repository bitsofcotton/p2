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
#if defined(_FORK_)
#include <stdio.h>
#include <fcntl.h>
#include <sys/socket.h>
extern char* environ[];
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

static inline num_t fl(int x, int M) {
  return num_t(x) / num_t(M + 1);
}

template <typename T> static inline SimpleVector<T> s2sv(const string& s) {
  int cnt(1);
  for(int i = 0; i < s.size(); i ++) if(s[i] == ',') cnt ++;
  SimpleVector<T> d(cnt);
  int i, j;
  for(i = 0, j = 0; i < s.size(); i ++) {
    std::stringstream ins(s.substr(i, s.size() - i));
    ins >> d[j ++];
    for( ; s[i] != ',' && i < s.size(); i ++) ;
  }
  return d;
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
  if(argc < 2) goto usage;
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
      // N.B. rand < lower bound we estimate case isn't handled.
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
        std::cout << "," << fl(ud(er) % 0x2001 - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(mt) % 0x2001 - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(rl24) % 0x2001 - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(rl48) % 0x2001  - 0x1000, 0x1000) << ",";
        std::cout << fl(ud(kb) % 0x2001 - 0x1000, 0x1000);
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
  } case 'm': case 'M': case 'n': case 'N': {
    // N.B. also [complex(rand,rand)/abs(...), ...] series works better.
    //      with IDFT/DFT, this is the analogy of output index shuffling.
    // N.B. M command select large one of the matrix size on PRN generation.
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
      for(int i = 0; i < std::atoi(argv[2]); i ++) {
        for(int ii = 0, idx = 0; ii < s.size(); ii ++) {
          std::stringstream ins(s.substr(idx, s.size() - idx));
          ins >> d;
          for( ; idx < s.size() && s[idx] != ','; idx ++) ;
          idx ++;
          // N.B. rand < 0x2001 case isn't handled.
          switch(sw) {
            case '0':
#if defined(_ARCFOUR_)
             std::cout << (argv[1][0] == 'M' ? num_t(arc4random() & 1 ? 1 : - 1) * d : (fl(int(arc4random_uniform(0x2001)) - 0x1000, 0x1000) + d) / num_t(int(2)) );
#else
             std::cout << (argv[1][0] == 'M' ? num_t(random() & 1 ? 1 : - 1) * d : (fl(int(random() % 0x2001) - 0x1000, 0x1000) + d) / num_t(int(2)));
#endif
             break;
#if !defined(_OLDCPP_)
            case '1':
              std::cout << (argv[1][0] == 'M' ? num_t(ud(er) & 1 ? 1 : - 1) * d : (fl(ud(er) % 0x2001 - 0x1000, 0x1000) + d) / num_t(int(2)));
              break;
            case '2':
              std::cout << (argv[1][0] == 'M' ? num_t(ud(mt) & 1 ? 1 : - 1) * d : (fl(ud(mt) % 0x2001 - 0x1000, 0x1000) + d) / num_t(int(2)));
              break;
            case '3':
              std::cout << (argv[1][0] == 'M' ? num_t(ud(rl24) & 1 ? 1 : - 1) * d : (fl(ud(rl24) % 0x2001 - 0x1000, 0x1000) + d) / num_t(int(2)));
              break;
            case '4':
              std::cout << (argv[1][0] == 'M' ? num_t(ud(rl48) & 1 ? 1 : - 1) * d : (fl(ud(rl48) % 0x2001 - 0x1000, 0x1000) + d) / num_t(int(2)));
              break;
            case '5':
              std::cout << (argv[1][0] == 'M' ? num_t(ud(kb) & 1 ? 1 : - 1) * d : (fl(ud(kb) % 0x2001 - 0x1000, 0x1000) + d) / num_t(int(2)));
              break;
#endif
#if defined(_GETENTROPY_)
            case '6': {
              uint8_t rnd[4];
              for(int i = 0; i < 1600000 / 4; i ++)
                getentropy(rnd, sizeof rnd);
              std::cout << (argv[1][0] == 'M' ? num_t((uint32_t&)(*rnd) & 1 ? 1 : - 1) * d : (fl(((uint32_t&)(*rnd) % 0x2001) - 0x1000, 0x1000) + d) / num_t(int(2)));
              break;
            }
#endif
            default: goto usage;
          }
          if(s.size() <= idx) break;
          std::cout << ", ";
        }
        if(i < std::atoi(argv[2]) - 1 &&
          (argv[1][0] == 'm' || argv[1][0] == 'M') )
            std::cout << ", ";
        else
          std::cout << std::endl << std::flush;
      }
    }
    break;
  } case 'c': {
    int& length(t);
    int  basedim(0);
    if(2 < argc) length  = std::atoi(argv[2]);
    if(3 < argc) basedim = std::atoi(argv[3]);
    assert(0 <= length && 0 <= basedim);
    idFeeder<num_t> p(length);
    num_t d(t);
    num_t M(d);
    int   ctr(0);
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ins(s);
      ins >> d;
      std::cout << (argv[1][1] == '\0' ? d * M : d - M) << ", " << std::flush;
      std::cout << (M = unOffsetHalf<num_t>(p012next<num_t>(p.next(
        offsetHalf<num_t>(d)), basedim || length ?
          (basedim == 1 ? 0 : basedim) : int(sqrt(num_t(ctr ++))) )) ) <<
            std::endl << std::flush;
    }
    break;
  } case 'A': {
    int length(13 + 3 + 4 + 1);
    if(2 < argc && argv[2][0] == '-' && argv[2][1] == '\0') 
      length = - ((13 + 3 + 4 + 1) * 2 + 3 + 1);
    else if(2 < argc) length = std::atoi(argv[2]);
    cerr << "continue with: " << argv[0] << " " << argv[1] << " " << length << endl;
    idFeeder<SimpleVector<num_t> > p(length ? abs(length) : 0);
    SimpleVector<num_t> M;
    while(std::getline(std::cin, s, '\n')) {
      SimpleVector<num_t> d(s2sv<num_t>(s));
      if(M.size() < d.size()) {
        M.resize(d.size());
        M.O();
      }
      for(int i = 0; i < d.size(); i ++)
        std::cout << (argv[1][1] == '\0' ? d[i] * M[i] : d[i] - M[i]) << ", ";
      std::cout << std::flush;
      p.next(offsetHalf<num_t>(d));
      if(! p.full || p.res.size() <= 3) M.O();
      else M = unOffsetHalf<num_t>(length < 0 ?
        pGuaranteeMax<num_t, 1>(p.res, string("") ) :
          pGuarantee<num_t, 1>(p.res, string("") ) );
      for(int j = 0; j < M.size() - 1; j ++) std::cout << M[j] << ", ";
      std::cout << M[M.size() - 1] << std::endl << std::flush;
    }
    break;
  } case 'q': {
    int len(4);
    int step(1);
    if(2 < argc) len  = std::atoi(argv[2]);
    if(3 < argc) step = std::atoi(argv[3]);
    idFeeder<SimpleVector<num_t> > p(len);
    idFeeder<SimpleVector<num_t> > q(step);
    SimpleVector<num_t> d;
    SimpleVector<num_t> M;
    while(std::getline(std::cin, s, '\n')) {
      SimpleVector<num_t> d(s2sv<num_t>(s));
      if(M.size() < d.size()) {
        M.resize(d.size());
        M.O();
      }
      for(int i = 0; i < d.size(); i ++)
        std::cout << (argv[1][1] == '\0' ? M[i] * d[i] : d[i] - M[i]) << ", ";
      std::cout << std::flush;
      p.next(d);
      if(p.full) {
        const SimpleVector<num_t> ms(minsq<num_t>(p.res.size()));
        for(int i = 0; i < p.res[0].size(); i ++) {
          idFeeder<num_t> f(ms.size());
          for(int j = 0; j < ms.size(); j ++) f.next(p.res[j][i]);
          assert(f.full);
          M[i]  = num_t(int(0));
          for(int j = 0; j < ms.size(); j ++) M[i] += f.res[j];
          M[i] /= num_t(ms.size());
          M[i] += ms.dot(f.res);
        }
        q.next(M);
        if(q.full) M = q.res[0];
        else M.O();
      }
      for(int j = 0; j < M.size() - 1; j ++) std::cout << M[j] << ", ";
      std::cout << M[M.size() - 1] << std::endl << std::flush;
    }
    break;
  } case 'e': {
    string a3(3 < argc ? argv[3] : "0");
    std::stringstream ss(a3);
    int loop0(0);
    ss >> loop0;
    int loop(loop0);
    int t2(0);
    SimpleMatrix<num_t> A(std::atoi(argv[2]), std::atoi(argv[2]));
    SimpleVector<num_t> b(std::atoi(argv[2]));
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ss(s);
      ss >> b[(t ++) % b.size()];
      if(! (t %= b.size())) {
        if(! loop) {
          for(int i = 1; i < b.size(); i ++) b[0] += b[i];
          loop = abs(b[0] * num_t(int(16)));
          continue;
        }
        if(A.rows() <= t2) {
          for(int i = 0; i <= loop; i ++) {
            b = A * b;
            std::cout << b / sqrt(b.dot(b)) << std::flush;
          }
          loop = loop0;
          t2 = 0;
        } else A.row(t2 ++) = b;
      }
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
  } case 'P': case 'Y': {
    if(argv[1][1] == '-') {
      for(int i = 2; i < argc; i ++) {
        std::vector<SimpleMatrix<num_t> > bitimg;
        if(! loadp2or3<num_t>(bitimg, argv[i])) continue;
        for(int ii = 0; ii < bitimg.size(); ii ++)
          for(int jj = 0; jj < bitimg[ii].rows(); jj ++)
            for(int kk = 0; kk < bitimg[ii].cols(); kk ++)
              std::cout << (bitimg[ii](jj, kk) - num_t(int(1)) / num_t(int(2)))
                << ", ";
        std::cout << std::endl << std::flush;
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
          p[j].row(i) = binMargin<num_t>(offsetHalf<num_t>(w.subVector(
            j * p[0].cols() * p[0].rows() + i * p[0].cols(), p[0].cols())));
      if(! savep2or3<num_t>((std::string("rand_pgm-") + to_string(t ++) +
        std::string(argv[1][0] == 'Y' ? ".ppm" : ".pgm")).c_str(), p) ) {
        std::cerr << "failed to save." << std::endl;
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
  } case 'Z': case 'X': case 'v': {
    std::vector<std::string> buf;
    while(std::getline(std::cin, s, '\n')) buf.emplace_back(s);
    switch(argv[1][0]) {
    case 'v':
      for(int i = 0; i < buf.size(); i ++)
        std::cout << buf[buf.size() - i - 1] << std::endl;
      break;
    case 'X': case 'Z': {
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
      if(argv[1][0] == 'Z') {
        for(int i = 0; i < M.size(); i ++)
          if((M[i] = max(abs(M[i]), abs(m[i]))) == num_t(int(0)))
            M[i] = num_t(int(1));
        for(int i = 0; i < sbuf.size(); i ++) {
          for(int j = 0; j < sbuf[i].size() - 1; j ++)
            std::cout << (sbuf[i][j] / M[j]) << ", ";
          std::cout << (sbuf[i][sbuf[i].size() - 1] / M[sbuf[i].size() - 1]) << std::endl;
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
            (M[j] - m[j]) * num_t(int(2)) ) << std::endl;
        }
      }
      break;
    } default: goto usage;
    }
    break;
  } case 'x': case 'j': {
    while(std::getline(std::cin, s, '\n'))
      for(int i = 0; i < s.size(); i ++) {
        if(argv[1][0] == 'x') {
          if(s[i] == '0') std::cout << (- num_t(1)) << std::endl;
          else if(s[i] == '1') std::cout << num_t(1) << std::endl;
        } else {
          if('0' <= s[i] && s[i] <= '9')
            std::cout << (num_t(s[i] - '0') - num_t(int(15)) / num_t(int(2)))
              << std::endl;
          else if('a' <= s[i] && s[i] <= 'f')
            std::cout << (num_t(s[i] - 'a' + 10) - num_t(int(15)) /
              num_t(int(2)) ) << std::endl;
          else if('A' <= s[i] && s[i] <= 'F')
            std::cout << (num_t(s[i] - 'A' + 10) - num_t(int(15)) /
              num_t(int(2)) ) << std::endl;
        }
      }
    break;
  } case 'u': {
    t = 2 < argc ? std::atoi(argv[2]) : 1;
    while(std::getline(std::cin, s, '\n'))
      for(int j = 0; j < t; j ++) std::cout << s << std::endl;
    break;
  } case 'E': {
    num_t in(int(0));
    string a2(2 < argc ? argv[2] : "");
    std::stringstream ss(a2);
    int tt(0);
    ss >> tt;
    std::vector<idFeeder<num_t> > f;
    std::vector<std::vector<idFeeder<num_t> > > ff;
    if(argv[1][1] == '+') {
      f.resize(tt, idFeeder<num_t>(0));
      ff.resize(tt * tt, f);
    } else
      f.resize(tt, idFeeder<num_t>(tt * tt));
    num_t tt_width(num_t(int(2)) / num_t(int(tt)));
    while(std::getline(std::cin, s, '\n')) {
      std::stringstream ins(s);
      ins >> in;
      if(argv[1][1] == '+') {
        for(int i = 0; i < tt; i ++)
          if(tt_width * num_t(int(i)) - num_t(int(1)) <= in &&
             in < tt_width * num_t(int(i + 1)) - num_t(int(1)) )
            for(int ii = 0; ii < tt * tt; ii ++)
              ff[ii][i].next(in);
      } else {
        for(int i = 0; i < tt; i ++)
          if(tt_width * num_t(int(i)) - num_t(int(1)) <= in &&
             in < tt_width * num_t(int(i + 1)) - num_t(int(1)) )
            f[i].next(in);
          else f[i].next(f[i].res[f[i].res.size() - 1]);
      }
      if(argv[1][1] == '+') {
        std::vector<idFeeder<num_t> >& g(ff[0]);
        int Mtot(0);
        for(int i = 0; i < g.size(); i ++)
          Mtot = max(Mtot, int(g[i].res.size()));
        for(int i = 0; i < g.size(); i ++) {
          for(int j = 1; j < g[i].res.size(); j ++)
            g[i].res[0] += g[i].res[j];
          std::cout << (g[i].res.size() ?
            (argv[1][2] != '+' ? g[i].res[0] / num_t(int(g[i].res.size())) :
              g[i].res[0] * num_t(int(g[i].res.size())) / num_t(Mtot * Mtot) )
                : num_t(int(0)) ) << ", ";
        }
        std::cout << Mtot << std::endl << std::flush;
        f.resize(0);
        f.resize(abs(tt), idFeeder<num_t>(0));
        for(int j = 0; j < ff.size() - 1; j ++) ff[j] = move(ff[j + 1]);
        ff[ff.size() - 1] = f;
      } else {
        for(int i = 0; i < tt - 1; i ++) {
          num_t sect(int(0));
          for(int j = 0; j < f[i].res.size(); j ++) sect += f[i].res[j];
          std::cout << sect << ", ";
        }
        const int i(tt - 1);
        num_t sect(int(0));
        for(int j = 0; j < f[i].res.size(); j ++) sect += f[i].res[j];
        std::cout << sect << std::endl << std::flush;
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
      std::cout << s << std::endl << std::flush;
    }
    left.close();
    right.close();
    break;
#if defined(_FORK_)
#if !defined(_OLDCPP_) && defined(_PERSISTENT_)
# undef int
#endif
#define IOSYNC(fd) \
  { \
    int flags; \
    if((flags = fcntl((fd), F_GETFL)) == - 1) assert(0 && "F_GETFL"); \
    flags &= ~ O_NONBLOCK; \
    if(fcntl((fd), F_SETFL, flags) == - 1) assert(0 && "F_SETFL)"); \
  }
  } case 'H': case '@': {
    vector<int> sock;
    num_t M(int(0));
    while(std::getline(std::cin, s, '\n')) {
      int cnt(1);
      int idx(0), bidx(0);
      for(int i = 0; i < s.size(); i ++) if(s[i] == ',') cnt ++;
      while(sock.size() < cnt) {
        int sp[2];
        if(socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, sp) == - 1) return - 1;
        IOSYNC(sp[0]);
        IOSYNC(sp[1]);
        int pidf;
        if((pidf = fork()) == - 1) return - 1;
        if(pidf == 0) {
          // N.B. child process.
          close(sp[0]);
          dup2(sp[1], 0);
          dup2(sp[1], 1);
          char* myargv[4];
          myargv[0] = "sh";
          myargv[1] = "-c";
          myargv[2] = const_cast<char*>(argv[2]);
          myargv[3] = 0;
          execve("/bin/sh", myargv, environ);
          assert(0 && "SHOULD NOT BE REACHED");
        }
        close(sp[1]);
        sock.emplace_back(sp[0]);
      }
      vector<num_t> dd;
      dd.resize(min(int(sock.size()), cnt), num_t(int(0)));
      num_t D(int(0));
      for(int i = 0; i < min(int(sock.size()), cnt); i ++) {
        for( ; idx < s.size() && s[idx] != ','; idx ++) ;
        string ss(s.substr(bidx, (++ idx) - bidx) );
        bidx = idx;
        ss += string("\n");
        write(sock[i], ss.c_str(), ss.size());
        if(argv[1][0] == '@') {
          stringstream ins(ss);
          ins >> dd[i];
          D += dd[i];
        }
      }
      if(argv[1][0] == '@') {
        std::cout << M * D / num_t(cnt) / num_t(cnt);
        M = num_t(int(0));
      }
      for(int i = 0; i < min(int(sock.size()), cnt); i ++) {
        char buf[2];
        buf[1] = 0;
        if(argv[1][0] == 'H') {
          while(read(sock[i], buf, 1) && buf[0] != '\n')
            std::cout << buf[0];
          if(i < sock.size() - 1) std::cout << ", " << std::flush;
        } else {
          string sbuf;
          while(read(sock[i], buf, 1) && buf[0] != '\n') sbuf += string(buf);
          stringstream ins(sbuf);
          num_t d(int(0));
          ins >> d;
          M += d;
        }
      }
      std::cout << std::endl << std::flush;
    }
    // N.B. child will auto exit when stdin close.
    for(int i = 0; i < sock.size(); i ++) close(sock[i]);
  } case 'D': {
    vector<int> sock;
    sock.reserve(argc - 1);
    for(int i = 2; i < argc; i ++) {
      int sp[2];
      if(socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, sp) == - 1) return - 1;
      IOSYNC(sp[0]);
      IOSYNC(sp[1]);
      int pidf;
      if((pidf = fork()) == - 1) return - 1;
      if(pidf == 0) {
        // N.B. child process.
        close(sp[0]);
        dup2(sp[1], 0);
        dup2(sp[1], 1);
        char* myargv[4];
        myargv[0] = "sh";
        myargv[1] = "-c";
        myargv[2] = const_cast<char*>(argv[i]);
        myargv[3] = 0;
        execve("/bin/sh", myargv, environ);
        assert(0 && "SHOULD NOT BE REACHED");
      }
      close(sp[1]);
      sock.emplace_back(sp[0]);
    }
    while(std::getline(std::cin, s, '\n')) {
      s += string("\n");
      for(int i = 0; i < sock.size(); i ++)
        write(sock[i], s.c_str(), s.size());
      for(int i = 0; i < sock.size(); i ++) {
        char buf[1];
        while(read(sock[i], buf, 1) && buf[0] != '\n')
          std::cout << buf[0];
        if(i < sock.size() - 1) std::cout << ", " << std::flush;
      }
      std::cout << std::endl << std::flush;
    }
    // N.B. child will auto exit when stdin close.
    for(int i = 0; i < sock.size(); i ++) close(sock[i]);
    break;
  } case 'K': {
    int step(4);
    if(2 < argc) step = std::atoi(argv[2]);
    vector<int> sock;
    sock.reserve(step);
    for(int i = 0; i < step; i ++) {
      int sp[2];
      if(socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, sp) == - 1) return - 1;
      IOSYNC(sp[0]);
      IOSYNC(sp[1]);
      int pidf;
      if((pidf = fork()) == - 1) return - 1;
      if(pidf == 0) {
        // N.B. child process.
        close(sp[0]);
        dup2(sp[1], 0);
        dup2(sp[1], 1);
        char* myargv[4];
        myargv[0] = "sh";
        myargv[1] = "-c";
        myargv[2] = const_cast<char*>(argv[3]);
        myargv[3] = 0;
        execve("/bin/sh", myargv, environ);
        assert(0 && "SHOULD NOT BE REACHED");
      }
      close(sp[1]);
      sock.emplace_back(sp[0]);
    }
    while(std::getline(std::cin, s, '\n')) {
      s += string("\n");
      write(sock[(t ++) % step], s.c_str(), s.size());
      if(step <= t) {
        char buf[1];
        while(read(sock[t % step], buf, 1) && buf[0] != '\n')
          std::cout << buf[0];
        std::cout << std::endl << std::flush;
      }
    }
    // N.B. child will auto exit when stdin close.
    for(int i = 0; i < sock.size(); i ++) close(sock[i]);
    break;
#undef IOSYNC
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
#endif
#if defined(_ONEBINARY_)
  } case '0': {
    int& length(t);
    int  step(1);
    if(2 < argc) length = std::atoi(argv[2]);
    if(3 < argc) step   = std::atoi(argv[3]);
    const bool chain(argv[1][1] == 'c');
    #include "../p0/p0.cc"
    break;
  } case '1': {
    int& stat(t);
    int  step(1);
    if(2 < argc) stat = std::atoi(argv[2]);
    if(3 < argc) step = std::atoi(argv[3]);
    const bool chain(argv[1][1] == 'c');
    #include "../p1/pp3.cc"
    break;
#endif
  } default: {
    num_t bb(int(0));
    SimpleVector<num_t> b;
    std::vector<int> bf;
    std::vector<int> bg;
    idFeeder<SimpleVector<num_t> > bbb;
    string a2(2 < argc ? argv[2] : "");
    const int a02(std::atoi(2 < argc ? argv[2] : "0"));
    std::stringstream ss(a2);
    num_t tt(int(0));
    ss >> tt;
    while(std::getline(std::cin, s, '\n')) {
      SimpleVector<num_t> in(s2sv<num_t>(s));
      if(in.size() != b.size()) { b = in; b.O(); }
      switch(argv[1][0]) {
      case 'S':
        if(t < std::atoi(argv[2])) break;
        std::cout << s << std::endl;
        break;
      case 'd':
        for(int i = 0; i < b.size() - 1; i ++)
          std::cout << (in[i] - b[i]) << ", ";
        std::cout << (in[in.size() - 1] - b[b.size() - 1]) << std::endl;
        break;
      case 's':
        if(a02) {
          if(bbb.res.size() != a02 && a02 != 0)
            bbb = idFeeder<SimpleVector<num_t> >(a02);
          bbb.next(in);
          if(bbb.full) {
            SimpleVector<num_t> sum(bbb.res[0]);
            for(int i = 1; i < bbb.res.size(); i ++)
              sum += bbb.res[i];
            for(int i = 0; i < sum.size() - 1; i ++)
              std::cout << sum[i] << ", ";
            std::cout << sum[sum.size() - 1] << std::endl;
          } else {
            for(int i = 0; i < in.size() - 1; i ++)
              std::cout << num_t(int(0)) << ",";
            std::cout << num_t(int(0)) << std::endl;
          }
        } else {
          for(int i = 0; i < b.size() - 1; i ++)
            std::cout << (in[i] += b[i]) << ", ";
          std::cout << (in[in.size() - 1] += b[b.size() - 1]) << std::endl;
        }
        break;
      case 'i':
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (in[i] == num_t(int(0)) ?
            num_t(int(0)) : num_t(int(1)) / in[i]) << ", ";
        std::cout << (in[in.size() - 1] == num_t(int(0)) ?
          num_t(int(0)) : num_t(int(1)) / in[in.size() - 1]) << std::endl;
        break;
      case 'l':
        if(argv[1][1] == 'c') {
          for(int i = 0; i < in.size() - 2; i ++)
            std::cout << in[i] << ", ";
          std::cout << in[in.size() - 2] << std::endl;
        } else if(argv[1][1] == 'G') {
          for(int i = 0; i < in.size() / 2 - 1; i ++)
            std::cout << in[in.size() / 2 + i] << ", ";
          std::cout << in[in.size() - 1] << std::endl;
        } else if(argv[1][1] == 'H') {
          for(int i = 0; i < in.size() / 2 - 1; i ++)
            std::cout << in[i] << ", ";
          const int i(in.size() / 2 - 1);
          std::cout << (0 <= i ? in[i] : num_t(int(0))) << std::endl;
        } else {
          for(int i = 2; i < argc - 1; i ++)
            std::cout << (std::atoi(argv[i]) < in.size() ?
              in[std::atoi(argv[i])] : num_t(int(0)) ) << ", ";
          std::cout << (std::atoi(argv[argc - 1]) < in.size() ?
            in[std::atoi(argv[argc - 1])] : num_t(int(0)) ) << std::endl;
        }
        break;
      case 't': case 'a': {
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (argv[1][0] == 'a' ? abs(in[i]) : in[i] * tt) << ", ";
        std::cout << (argv[1][0] == 'a' ? abs(in[in.size() - 1]) :
          in[in.size() - 1] * tt) << std::endl;
        break;
      } case 'o': {
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (in[i] + tt) << ", ";
        std::cout << (in[in.size() - 1] + tt) << std::endl;
        break;
      } case 'k':
        if(t % std::atoi(argv[2])) break;
        std::cout << s << std::endl;
        break;
      case 'G':
        if(argv[1][1] == '+') {
          const int width(sqrt(num_t(in.size())));
          for(int i = width; i < in.size(); i ++) in[i % width] += in[i];
          for(int i = 0; i < width; i ++) std::cout << in[i] << ", ";
          std::cout << std::endl;
        } else {
          for(int i = 1; i < in.size(); i ++) in[0] += in[i];
          std::cout << (in[0] /= num_t(int(in.size()))) << std::endl;
        }
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
      } case 'w': {
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << (tt < abs(in[i] - b[i]) ? b[i] = in[i] : b[i]) << ", ";
        std::cout << (tt < abs(in[in.size() - 1] - b[b.size() - 1]) ?
          b[b.size() - 1] = in[in.size() - 1] : b[b.size() - 1]) << std::endl;
        break;
      } case 'b': {
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << sgn<num_t>(in[i]) << ", ";
        std::cout << sgn<num_t>(in[in.size() - 1]) << std::endl;
        break;
#if !defined(_OLDCPP_)
      } case 'F': {
#if defined(_FLOAT_BITS_) || defined(_PERSISTENT_)
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << double(in[i]) << ", ";
        std::cout << double(in[in.size() - 1]) << std::endl;
#else
        for(int i = 0; i < in.size() - 1; i ++) {
          SimpleFloat<unsigned int, DUInt<unsigned int, sizeof(unsigned int) * 8>, sizeof(unsigned int) * 8, int> f(int(in[i] * pow(myfloat(2), myfloat(tt)) ));
          std::cout << (f >>= tt) << ", ";
        }
        SimpleFloat<unsigned int, DUInt<unsigned int, sizeof(unsigned int) * 8>, sizeof(unsigned int) * 8, int> f(int(in[in.size() - 1] * pow(myfloat(2), myfloat(tt)) ));
        std::cout << (f >>= tt) << std::endl;
#endif
        break;
#endif
      } case 'I': {
        if(std::atoi(argv[2]) == 0) {
          if(b.size() < in.size()) b.entity.resize(in.size(), num_t(int(0)));
          SimpleVector<num_t> b2(b / num_t(max(int(1), t)));
          for(int i = 0; i < in.size() - 1; i ++)
            std::cout << (argv[1][1] == 'c' ? in[i] - b2[i] : b2[i] * in[i]) << ", ";
          const int i(in.size() - 1);
          std::cout << (argv[1][1] == 'c' ? in[i] - b2[i] : b2[i] * in[i]) << endl;
          for(int i = 0; i < in.size(); i ++)
            in[i] += b[i];
        } else {
          if(bbb.res.size() != std::atoi(argv[2]))
            bbb = idFeeder<SimpleVector<num_t> >(std::atoi(argv[2]));
          if(bbb.full) {
            b = bbb.res[0];
            for(int j = 1; j < bbb.res.size(); j ++) 
              b += bbb.res[j];
            b /= num_t(bbb.res.size());
            for(int i = 0; i < in.size() - 1; i ++)
              std::cout << (argv[1][1] == 'c' ? in[i] - b[i] : b[i] * in[i]) << ", ";
            const int i(in.size() - 1);
            std::cout << (argv[1][1] == 'c' ? in[i] - b[i] : b[i] * in[i]) << std::endl;
          } else {
            for(int i = 0; i < in.size() - 1; i ++)
              std::cout << num_t(int(0)) << ", ";
            std::cout << num_t(int(0)) << std::endl;
          }
          bbb.next(in);
        }
        break;
      } case 'O': {
        for(int i = 0; i < in.size() / 2 - 1; i ++)
          std::cout << (in[i + in.size() / 2] == num_t(int(0)) ? num_t(int(0))
            : (in[i] - in[i + in.size() / 2]) * (argv[1][1] == '+' ?
              num_t(int(1)) : in[i]) ) << ", ";
        const int i(in.size() / 2 - 1);
        std::cout << (in[i + in.size() / 2] == num_t(int(0)) ? num_t(int(0))
          : (in[i] - in[i + in.size() / 2]) * (argv[1][1] == '+' ?
            num_t(int(1)) : in[i]) ) << std::endl;
        break;
      } case 'J': {
        if(bf.size() != in.size()) bf.resize(in.size() / 2, int(1));
        for(int i = 0; i < in.size() / 2; i ++)
          if(tt < abs(b[i + in.size() / 2] + in[i + in.size() / 2]) ) {
            bf[i] = - bf[i];
            b[i + in.size() / 2]  = num_t(int(0));
          }
        for(int i = 0; i < in.size() / 2 - 1; i ++)
          std::cout << (sgn<num_t>(in[i] * in[i + in.size() / 2] * num_t(bf[i]))
            * in[i]) << ", ";
        const int i(in.size() / 2 - 1);
        std::cout << (sgn<num_t>(in[i] * in[i + in.size() / 2] * num_t(bf[i]))
          * in[i]) << std::endl;
        for(int i = 0; i < in.size() / 2; i ++)
          in[i + in.size() / 2] += b[i + in.size() / 2];
        break;
      } case 'V':
        for(int i = 0; i < in.size(); i ++) std::cout << in[i] << std::endl;
        break;
      case 'C': {
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << unOffsetHalf<num_t>(clipBin<num_t>(offsetHalf<num_t>(in[i]))) << ", ";
        const int i(in.size() - 1);
        std::cout << unOffsetHalf<num_t>(clipBin<num_t>(offsetHalf<num_t>(in[i]))) << std::endl;
        break;
      } case 'W': {
        const SimpleVector<num_t> avg((b + in) / num_t(int(2)));
        for(int i = 0; i < avg.size() - 1; i ++)
          std::cout << avg[i] << ", ";
        std::cout << avg[avg.size() - 1] << std::endl;
        for(int i = 0; i < in.size() - 1; i ++)
          std::cout << in[i] << ", ";
        std::cout << in[in.size() - 1] << std::endl;
        break;
      } case '/': {
        for(int i = 0; i < in.size() / 3 - 1; i ++)
          std::cout << (argv[1][1] == '+' ? num_t(int(1)) : in[i]) * ((in[i + in.size() / 3] + in[i + in.size() / 3 * 2]) / num_t(int(2)) - in[i]) << ", ";
        const int i(in.size() / 3 - 1);
        std::cout << (argv[1][1] == '+' ? num_t(int(1)) : in[i]) * ((in[i + in.size() / 3] + in[i + in.size() / 3 * 2]) / num_t(int(2)) - in[i]) << std::endl;
        break;
      } default: goto usage;
      }
      std::cout << std::flush;
      if(argv[1][0] != 'w') b = in;
      t ++;
    }
  } }
  return 0;
 usage:
  cerr << "Usage:" << endl;
  cerr << " *** reformation part (if the original series is hard enough) ***" << endl;
  cerr << "# take delta     on input stream" << endl << argv[0] << " d" << endl;
  cerr << "# take summation on input stream" << endl << argv[0] << " s <len>?" << endl;
  cerr << "# take skip      on input stream" << endl << argv[0] << " k <interval>" << endl;
  cerr << "# take skip head on input stream" << endl << argv[0] << " S <margin>" << endl;
  cerr << "# take reverse   on input stream" << endl << argv[0] << " v" << endl;
  cerr << "# pick {0,1} or [0-9a-f] str on input stream" << endl << argv[0] << " [xj]" << endl;
  cerr << "# take reform [-1,1] on input stream" << endl << argv[0] << " X" << endl;
  cerr << "# take reform [-1,1] on input stream without offset" << endl << argv[0] << " Z" << endl;
  cerr << "# take inverse   on input stream" << endl << argv[0] << " i" << endl;
  cerr << "# take picked column      on input stream (H for first half, G for last half, c for chop)" << endl << argv[0] << " l[cHG]? <col0index> ..." << endl;
  cerr << "# take difference affter math on input stream first half to last half" << endl << argv[0] << " O+?" << endl;
  cerr << "# take duplicate toeplitz on input stream" << endl << argv[0] << " z <column number>" << endl;
  cerr << "# take multiply each      on input stream" << endl << argv[0] << " t <ratio>" << endl;
  cerr << "# take offset   each      on input stream" << endl << argv[0] << " o <offset>" << endl;
  cerr << "# take absolute each      on input stream" << endl << argv[0] << " a" << endl;
  cerr << "# take sign     each      on input stream" << endl << argv[0] << " b" << endl;
  cerr << "# take trivial complement stream on input stream" << endl << argv[0] << " W" << endl;
  cerr << "# take sum columns each line on input stream (+ for output sqrt columns)" << endl << argv[0] << " G+?" << endl;
  cerr << "# take walk condition each on input stream" << endl << argv[0] << " w <range>" << endl;
  cerr << "# take column 0 horizontal cut output to each column (+ for strict average on the range, ++ for strict sum up)" << endl << argv[0] << " E <number>+?+?" << endl;
  cerr << "# take column 0 to harden PRNG part vector output" << endl << argv[0] << " e" << endl;
  cerr << "# take opposite type output string each on input stream" << endl << argv[0] << " F <bit number>" << endl;
  cerr << endl << " *** PRNG part ***" << endl;
  cerr << "# make [-1,1]   PRNG stream" << endl << argv[0] << " [rR]  <proto>" << endl;
  cerr << "# make {-1,0,1} PRNG stream" << endl << argv[0] << " [rR]b <proto>" << endl;
  cerr << "# make {-1,1}   PRNG stream" << endl << argv[0] << " [rR]B <proto>" << endl;
  cerr << "# blend [-1,1]  PRNG stream" << endl << argv[0] << " [mn]<proto> <number of output columns>" << endl;
  cerr << "# flip or not   PRNG stream" << endl << argv[0] << " [MN]<proto> <number of output columns>" << endl;
  cerr << endl << " *** predictor part ***" << endl;
#if defined(_ONEBINARY_)
  cerr << "# predict with Riemann measureable condition (c for difference output)" << endl << argv[0] << " 0c? <arg>? <step>?" << endl;
  cerr << "# predict with untangle combination condition (c for difference output)" << endl << argv[0] << " 1c? <arg> <step>?" << endl;
#endif
  cerr << "# feed patternizable jammer input entropy (. for difference output)" << endl << argv[0] << " c.? <state> <n-markov>" << endl;
  cerr << "# trivial return to the average id. prediction (c for difference output)" << endl << argv[0] << " Ic? <len>" << endl;
  cerr << "# ddpmopt compatible prediction (. for difference output, states < 0 for LoEM unstable case)" << endl << argv[0] << " A.? <states>?" << endl;
  cerr << "# minimum square left hand side prediction (. for difference output)" << endl << argv[0] << " q.? <len>? <step?>" << endl;
  cerr << endl << " *** vector operation part ***" << endl;
  cerr << "# input serial stream to vector stream" << endl << argv[0] << " f <dimension>" << endl;
  cerr << "# input vector stream to serial stream" << endl << argv[0] << " h" << endl;
  cerr << "# input vector stream to pgm graphics output or its reverse" << endl << argv[0] << " [PY]-?" << endl;
  cerr << "# input vector stream to midi output" << endl << argv[0] << " Q" << endl;
#if defined(_FORK_)
  cerr << endl << " *** multi process call part ***" << endl;
  cerr << "# do double prediction on same input" << endl << argv[0] << " D <command0> <command1>" << endl;
  cerr << "# do step prediction on same input" << endl << argv[0] << " K <step> <command>" << endl;
  cerr << "# do each of all column input prediction parallel, take output column 0." << endl << argv[0] << " H <command>" << endl;
  cerr << "# do each of all column input prediction parallel, take output column 0 as a prediction value, pred avg * input avg output." << endl << argv[0] << " @ <command>" << endl;
#endif
  cerr << endl << " *** other part ***" << endl;
  cerr << "# pair of files load into same line columns (use /dev/stdin if you need)" << endl << argv[0] << " L <left> <right>" << endl;
  cerr << "# show output statistics it's 0<x<1 (+ for 0<x)" << endl << argv[0] << " T+?" << endl;
  cerr << endl << " *** test case ***" << endl;
  cerr << "cat ... | " << argv[0] << " W | " << argv[0] << " d | " << argv[0] << " d | " << argv[0] << " t " << num_t(int(1)) / num_t(int(4)) << " | tee 0 | " << argv[0] << " Ac | " << argv[0] << " lH > 0+" << endl;
  cerr << argv[0] << " L 0 0+ | " << argv[0] << " s > 1-" << endl;
  cerr << argv[0] << " L 0 0+ | " << argv[0] << " s | " << argv[0] << " s > 1+" << endl;
  cerr << argv[0] << " s < 0 | " << argv[0] << " s > 00" << endl;
  cerr << argv[0] << " L 0 0+ | " << argv[0] << " s | " << argv[0] << " s | " << argv[0] << " O | " << argv[0] << " 0 1 | " << argv[0] << " S 1 | " << argv[0] << " k 2 | " << argv[0] << " lH" << endl;
  cerr << argv[0] << " L 00 1+ 1- | " << argv[0] << " / | " << argv[0] << " 0 1 | " << argv[0] << " k 2 | " << argv[0] << " lH" << endl;
  cerr << endl << " *** graphics test ***" << endl;
  cerr << "yes " << num_t(int(1)) / num_t(int(2)) << " | " << argv[0] << " f ... | head -n 1 | " << argv[0] << " [PY] && mv rand_pgm-0.p[gp]m dummy.p[gp]m" << endl;
  cerr << argv[0] << " P- ... dummy.p[gp]m ... dummy.p[gp]m | tee 0 | <difference-predictor> > 1" << endl; 
  cerr << argv[0] << " L 0 1 | " << argv[0] << " O+ | " << argv[0] << " V | " << argv[0] << " X | " << argv[0] << " f ... | " << argv[0] << " [PY]" << endl;
  cerr << endl << " *** to hear some residue ***" << endl;
  cerr << argv[0] << " r | " << argv[0] << " l 0 | tee 0 | <predictor-tobe-loopback>" << endl;
  cerr << "catgr 3 < 0 | " << argv[0] << " e 3 | " << argv[0] << " h | " << argv[0] << " t ... | " << argv[0] << " f 3 | grep -v nan | grep -v \"[ 0,  0,  0]\" | uniq | grep ] | p Q > out.mid" << endl;
  cerr << endl << " *** predictor notation ***" << endl;
  cerr << "# Once we implement simple enough single predictor, they causes fixed LoEM applied code exists causes jammer intention justified causes the first hypothesis we believe as a universal invariant breaks." << endl;
  cerr << "# We are embryonic believing such a condition however as soon as we upload our code the predictor break we experience, this is more than 20 times or so since around a decade ago." << endl;
  return - 1;
}

