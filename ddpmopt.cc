#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <random>
#include <assert.h>
#include <stdlib.h>

//#define int int64_t
#define int int32_t
#include "lieonn.hh"
typedef myfloat num_t;

using std::cout;
using std::cerr;
using std::endl;
using std::atoi;
using std::string;
using std::to_string;
using std::vector;
using std::sort;
using std::binary_search;
using std::make_pair;
using std::istringstream;

#include <stdlib.h>

#undef int
int main(int argc, const char* argv[]) {
//#define int int64_t
#define int int32_t
  const auto  sz(2);
  const auto& m(argv[1][0]);
  if(argc <= 1 || argv[1][1] != '\0') goto usage;
  cerr << "Coherent: sqrt(2): " << sqrt<num_t>(Complex<num_t>(num_t(2))) << endl;
  if(m == '-') {
    vector<SimpleVector<num_t> > L;
    std::string s;
    while(std::getline(std::cin, s, '\n')) {
      SimpleVector<num_t> l;
      std::stringstream ins(s);
      ins >> l;
      if(l.size() != sz * sz + 1) break;
      L.emplace_back(l / sqrt(l.dot(l)));
      l /= - num_t(l[3]);
      l[3] = num_t(int(0));
      L.emplace_back(l);
    }
    assert(L.size() && ! (L.size() & 1));
    for(int i0 = 2; i0 < argc; i0 ++) {
      cerr << i0 - 2 << " / " << argc - 2 << endl;
      vector<SimpleMatrix<num_t> > in;
      if(! loadp2or3<num_t>(in, argv[i0])) return - 1;
      if(in.size() != 3) {
        std::cerr << argv[i0] << " doesn't include 3 colors" << std::endl;
        continue;
      }
      vector<SimpleMatrix<num_t> > out;
      out.emplace_back(in[0]);
      out[0].O();
      for(int i = 0; i < in[0].rows(); i ++)
        for(int j = 0; j < in[0].cols(); j ++) {
          SimpleVector<num_t> work(4);
          for(int m = 0; m < in.size(); m ++)
            work[m] = in[m](i, j);
          work[3] = num_t(int(1)) / num_t(int(2));
          auto work2(makeProgramInvariant<num_t>(work, - num_t(int(1)), true).first);
          assert(work2.size() == L[0].size());
          int idx(0);
          for(int m = 2; m < L.size(); m += 2) {
            assert(L[m].size()   == work2.size());
            assert(L[idx].size() == work2.size());
            if(abs(L[idx].dot(work2)) <= abs(L[m].dot(work2)))
              idx = m;
          }
          auto last(sqrt(work.dot(work)));
          for(int ii = 0;
                  ii < 2 * int(- log(SimpleMatrix<num_t>().epsilon()) / log(num_t(int(2))) )
                  && sqrt(work.dot(work) * SimpleMatrix<num_t>().epsilon()) <
                       abs(work[3] - last); ii ++) {
            last = work[3];
            const auto work2(makeProgramInvariant<num_t>(work, - num_t(int(1)), true));
            work[3] = revertProgramInvariant<num_t>(make_pair(L[idx + 1].dot(work2.first) * sgn<num_t>(L[idx].dot(work2.first)), work2.second), true);
          }
          out[0](i, j) = work[3];
        }
      if(! savep2or3<num_t>((std::string(argv[i0]) + std::string(".pgm")).c_str(), out) )
        cerr << "failed to save." << endl;
    }
  } else if(m == '+') {
    vector<vector<SimpleMatrix<num_t> > > in;
    vector<SimpleMatrix<num_t> > out;
    assert(! ((argc - 2) & 1));
    in.resize((argc - 2) / 2);
    out.resize((argc - 2) / 2);
    int cnt(0);
    for(int i = 2; i < argc; i ++) {
      vector<SimpleMatrix<num_t> > work;
      if(! loadp2or3<num_t>(work, argv[i])) continue;
      if(! (i & 1)) {
        assert(work.size() == 1);
        out[i / 2 - 1] = move(work[0]);
        cnt += out[i / 2 - 1].rows() * out[i / 2 - 1].cols();
      } else {
        in[i / 2 - 1] = move(work);
        assert(in[i / 2 - 1].size() == 3);
        assert(out[i / 2 - 1].rows() == in[i / 2 - 1][0].rows() &&
               out[i / 2 - 1].cols() == in[i / 2 - 1][0].cols());
      }
    }
    assert(in.size() == out.size());
    vector<SimpleVector<num_t> > v;
    v.reserve(cnt);
    for(int i = 0; i < in.size(); i ++)
      for(int j = 0; j < out[i].rows(); j ++)
        for(int k = 0; k < out[i].cols(); k ++) {
          SimpleVector<num_t> work(4);
          for(int m = 0; m < 3; m ++)
            work[m] = in[i][m](j, k);
          work[3] = out[i](j, k);
          v.emplace_back(move(work));
        }
    const auto c(crush<num_t>(v));
    for(int i = 0; i < c.size(); i ++) {
      if(! c[i].first.size()) continue;
      auto vv(makeProgramInvariant<num_t>(c[i].first[0], - num_t(int(1)), true).first);
      for(int j = 1; j < c[i].first.size(); j ++)
        vv += makeProgramInvariant<num_t>(c[i].first[j], - num_t(int(1)), true).first;
      vv /= num_t(c[i].first.size());
      if(vv.dot(vv) != num_t(int(0))) cout << vv;
    }
    cout << endl;
  } else if(m == 'p') {
    vector<vector<SimpleMatrix<num_t> > > in;
    in.reserve(argc - 1);
    for(int i = 2; i < argc; i ++) {
      vector<SimpleMatrix<num_t> > work;
      if(! loadp2or3<num_t>(work, argv[i])) continue;
      in.emplace_back(work.size() == 3 ? rgb2xyz<num_t>(work) : move(work));
    }
    // N.B. with good spreaded input, we can suppose original as a 'T' command
    //      case.
    auto p(predMat<num_t>(in = normalize<num_t>(in)));
    if(! savep2or3<num_t>("predg.ppm",
        normalize<num_t>(p.first.size() == 3 ?
          xyz2rgb<num_t>(p.first) : p.first)) )
          cerr << "failed to save." << endl;
    if(! savep2or3<num_t>("predgc.ppm",
        normalize<num_t>(p.second.size() == 3 ?
          xyz2rgb<num_t>(p.second) : p.second)) )
          cerr << "failed to save." << endl;
  } else if(m == 'P') {
    // N.B. we need 4 of the different candidates for the results with
    //      same PRNG. if we're lucky enough, the raw predMat can returns
    //      reasonable 4.
    vector<vector<SimpleMatrix<num_t> > > in;
    in.reserve(argc - 1);
    for(int i = 2; i < argc; i ++) {
      vector<SimpleMatrix<num_t> > work;
      if(! loadp2or3<num_t>(work, argv[i])) continue;
      in.emplace_back(work.size() == 3 ? rgb2xyz<num_t>(work) : move(work));
    }
    in = normalize<num_t>(in);
    // N.B. we get better information on raw delta only. don't know why.
    //      but this is to make start of stream is white out input.
    // const auto sbuf(in[11]);
    // const auto lbuf(in[in.size() - 1])
    for(int i = 0; i < in.size() - 1; i ++)
      for(int j = 0; j < in[i].size(); j ++)
        in[i][j] = in[i + 1][j] - in[i][j];
    in.resize(in.size() - 1);
    for(int i = 0; i < in.size(); i ++)
      for(int j = 0; j < in[i].size(); j ++)
        for(int ii = 0; ii < in[i][j].rows(); ii ++)
          for(int jj = 0; jj < in[i][j].cols(); jj ++)
            in[i][j](ii, jj) = (in[i][j](ii, jj) + num_t(int(1))) / num_t(int(2));
    auto q(predMat<num_t>(in));
    for(int j = 0; j < q.first.size(); j ++) {
      for(int ii = 0; ii < q.first[j].rows(); ii ++)
        for(int jj = 0; jj < q.first[j].cols(); jj ++) {
          q.first[j](ii, jj)  =
            q.first[ j](ii, jj) * num_t(int(2)) - num_t(int(1));
          q.second[j](ii, jj) =
            q.second[j](ii, jj) * num_t(int(2)) - num_t(int(1));
        }
      q.second[j] = q.first[j] * num_t(int(2)) - q.second[j];
    }
    if(! savep2or3<num_t>("qredg.ppm",
        normalize<num_t>(q.first.size() == 3 ?
          xyz2rgb<num_t>(q.first) : q.first)) )
          cerr << "failed to save." << endl;
    if(! savep2or3<num_t>("qredgc.ppm",
        normalize<num_t>(q.second.size() == 3 ?
          xyz2rgb<num_t>(q.second) : q.second)) )
          cerr << "failed to save." << endl;
  } else if(m == 'w') {
    vector<vector<SimpleMatrix<num_t> > > in;
    in.reserve(argc - 2);
    for(int i = 2; i < argc; i ++) {
      vector<SimpleMatrix<num_t> > work;
      if(! loadp2or3<num_t>(work, argv[i])) continue;
      in.emplace_back(work.size() == 3 ? rgb2xyz<num_t>(work) : move(work));
    }
    in = normalize<num_t>(in);
    vector<SimpleVector<num_t> > work;
    work.resize(in.size());
    for(int i = 0; i < in.size(); i ++) {
      work[i].resize(in[i].size() * in[i][0].rows() * in[i][0].cols());
      for(int j = 0; j < in[i].size(); j ++)
        for(int k = 0; k < in[i][j].rows(); k ++)
          work[i].setVector(j * in[i][0].rows() * in[i][0].cols() +
            k * in[i][0].cols(), in[i][j].row(k));
    }
    auto vp(predv4<num_t, true>(work));
    pair<vector<SimpleMatrix<num_t> >, vector<SimpleMatrix<num_t> > > p;
    p.first.resize(in[0].size());
    p.second.resize(in[0].size());
    for(int i = 0; i < p.first.size(); i ++) {
      p.first[ i].resize(in[0][0].rows(), in[0][0].cols());
      p.second[i].resize(in[0][0].rows(), in[0][0].cols());
      for(int j = 0; j < p.first[i].rows(); j ++) {
        p.first[i].row(j) =
          vp.first.subVector(i * p.first[0].rows() * p.first[0].cols() +
            j * p.first[0].cols(), p.first[0].cols());
        p.second[i].row(j) =
          vp.second.subVector(i * p.second[0].rows() * p.second[0].cols() +
            j * p.second[0].cols(), p.second[0].cols());
      }
    }
    if(! savep2or3<num_t>("predgw.ppm",
      normalize<num_t>(p.first.size() == 3 ?
        xyz2rgb<num_t>(p.first) : p.first)) )
        cerr << "failed to save." << endl;
    if(! savep2or3<num_t>("predgwc.ppm",
      normalize<num_t>(p.second.size() == 3 ?
        xyz2rgb<num_t>(p.second) : p.second)) )
        cerr << "failed to save." << endl;
  } else if(m == 'q' || m == 'Q') {
    for(int i0 = 2; i0 < argc; i0 ++) {
      vector<SimpleMatrix<num_t> > work;
      if(! loadp2or3<num_t>(work, argv[i0])) continue;
      work = normalize<num_t>(work.size() == 3 ? rgb2xyz<num_t>(work) : work);
      vector<vector<SimpleVector<num_t> > > pwork;
      pwork.resize(work[0].rows());
      for(int i = 0; i < pwork.size(); i ++) {
        pwork[i].reserve(work.size());
        for(int j = 0; j < work.size(); j ++)
          pwork[i].emplace_back(work[j].row(i));
      }
      // N.B. same as 'p' cmd, we can suppose original as 'T' command input
      //      with long range but not in general.
      // N.B. 10 + 1 * 2 < work[0].rows() / step.
      const int ext(work[0].rows() / 12);
      vector<SimpleMatrix<num_t> > wwork(work.size(),
        SimpleMatrix<num_t>(work[0].rows() + ext, work[0].cols()).O());
      for(int j = 0; j < work.size(); j ++)
        wwork[j].setMatrix(0, 0, work[j]);
      auto wwork2(wwork);
      if(m == 'Q') {
        for(int i = 0; i < pwork.size() - 1; i ++)
          for(int j = 0; j < pwork[i].size(); j ++)
            pwork[i][j] = pwork[i + 1][j] - pwork[i][j];
        pwork.resize(pwork.size() - 1);
        for(int i = 0; i < pwork.size(); i ++)
          for(int j = 0; j < pwork[i].size(); j ++)
            for(int k = 0; k < pwork[i][j].size(); k ++)
              pwork[i][j][k] = (pwork[i][j][k] + num_t(int(1))) / num_t(int(2));
      }
      for(int i = 0; i < ext; i ++) {
        auto pwt(pwork);
        auto n(predVec<num_t>(pwt, i + 1));
        for(int j = 0; j < wwork.size(); j ++) {
          wwork[j].row( work[0].rows() + i) = move(n.first[j]);
          wwork2[j].row(work[0].rows() + i) = move(n.second[j]);
          if(m == 'Q') {
            // N.B. same as 'P' command, we make hypothesis prediction beginning
            //      is white outed one.
            wwork2[j] = wwork[j] * num_t(int(2)) - wwork2[j];
            for(int k = 0; k < wwork[j].cols(); k ++) {
              wwork[ j](work[0].rows() + i, k) =
                wwork[ j](work[0].rows() + i, k) * num_t(int(2)) -
                  num_t(int(1));
              wwork2[j](work[0].rows() + i, k) =
                wwork2[j](work[0].rows() + i, k) * num_t(int(2)) -
                  num_t(int(1));
            }
          }
        }
      }
      if(m == 'Q') {
        for(int i = 0; i < ext; i ++)
          for(int j = 0; j < wwork.size(); j ++) {
            wwork[j].row(work[0].rows() + i) +=
              wwork[j].row(work[0].rows() + i - 1);
            wwork2[j].row(work[0].rows() + i) +=
              wwork2[j].row(work[0].rows() + i - 1);
          }
        auto wworknpart(wwork);
        for(int j = 0; j < wwork.size(); j ++)
          wworknpart[j] = wwork[j].subMatrix(work[0].rows(), 0, ext, work[0].cols());
        wworknpart = normalize<num_t>(wworknpart);
        for(int j = 0; j < wwork.size(); j ++)
          wwork[j].setMatrix(work[0].rows(), 0, wworknpart[j]);
      }
      auto wwork2npart(wwork2);
      for(int j = 0; j < wwork2.size(); j ++)
        wwork2npart[j] = wwork2[j].subMatrix(work[0].rows(), 0, ext, work[0].cols());
      wwork2npart = normalize<num_t>(wwork2npart);
      for(int j = 0; j < wwork2.size(); j ++)
        wwork2[j].setMatrix(work[0].rows(), 0, wwork2npart[j]);
      if(! savep2or3<num_t>(m == 'q' ? argv[i0] :
        (string(argv[i0]) + string("-3.ppm")).c_str(),
        normalize<num_t>(wwork.size() == 3 ?
        xyz2rgb<num_t>(wwork) : wwork) ) )
          cerr << "failed to save." << endl;
      if(! savep2or3<num_t>(m == 'q' ?
        (string(argv[i0]) + string("-2.ppm")).c_str() :
        (string(argv[i0]) + string("-4.ppm")).c_str(),
        normalize<num_t>(wwork2.size() == 3 ?
          xyz2rgb<num_t>(wwork2) : wwork2) ) )
            cerr << "failed to save." << endl;
    }
  } else if(m == 'x' || m == 'y' || m == 'i' || m == 't') {
    vector<num_t> score;
    score.resize(argc + 1, num_t(int(0)));
    switch(argv[1][0]) {
    case 'x':
    case 'i':
      for(int i0 = 2; i0 < argc; i0 ++) {
        vector<SimpleMatrix<num_t> > work;
        P0maxRank<num_t> p;
        if(! loadp2or3<num_t>(work, argv[i0])) continue;
        for(int i = 0; i < work.size(); i ++)
          for(int ii = 0; ii < work[i].rows(); ii ++) {
            idFeeder<num_t> w(3);
            for(int jj = 0; jj < work[i].cols(); jj ++) {
              if(w.full) {
                const auto pp(p.next(w.res));
                score[i0] += (pp - work[i](ii, jj)) * (pp - work[i](ii, jj));
              } 
              w.next(work[i](ii, jj));
            }
          }
        if(argv[1][0] == 'x')
          score[i0] /= num_t(work[0].rows() * work[0].cols() * work.size());
      }
      if(argv[1][0] == 'x') break;
    case 'y':
      for(int i0 = 2; i0 < argc; i0 ++) {
        vector<SimpleMatrix<num_t> > work;
        P0maxRank<num_t> p;
        if(! loadp2or3<num_t>(work, argv[i0])) continue;
        for(int i = 0; i < work.size(); i ++)
          for(int jj = 0; jj < work[i].cols(); jj ++) {
            idFeeder<num_t> w(3);
            for(int ii = 0; ii < work[i].rows(); ii ++) {
              if(w.full) {
                const auto pp(p.next(w.res));
                score[i0] += (pp - work[i](ii, jj)) * (pp - work[i](ii, jj));
              } 
              w.next(work[i](ii, jj));
            }
          }
        score[i0] /= num_t(work[0].rows() * work[0].cols() * work.size());
      }
      break;
    case 't':
      {
        vector<vector<SimpleMatrix<num_t> > > b;
        b.resize(argc + 1);
        for(int i = 2; i < argc; i ++) {
          vector<SimpleMatrix<num_t> > work;
          if(! loadp2or3<num_t>(work, argv[i])) continue;
          b[i] = move(work);
          assert(b[i].size() == b[2].size() &&
            b[i][0].rows() == b[2][0].rows() &&
            b[i][0].cols() == b[2][0].cols());
        }
        P0maxRank<num_t> p;
        int cnt(0);
        for(int i = 0; i < b[2][0].rows(); i ++)
          for(int j = 0; j < b[2][0].cols(); j ++)
            for(int k = 0; k < b[2].size(); k ++) {
              idFeeder<num_t> w(3);
              for(int ii = 2; ii < b.size(); ii ++, cnt ++) {
                if(! b[ii].size()) continue;
                if(w.full) {
                  const auto pp(p.next(w.res));
                  score[0] += (pp - b[ii][k](i, j)) * (pp - b[ii][k](i, j));
                }
                w.next(b[ii][k](i, j));
              }
            }
        score[0] /= num_t(cnt);
      }
      break;
    }
    if(argv[1][0] == 'x' || argv[1][0] == 'y' || argv[1][0] == 'i')
      for(int i = 2; i < argc; i ++)
        cout << sqrt(score[i]) << ", " << argv[i] << endl;
    else
      cout << sqrt(score[0]) << ", whole image index" << endl;
    return 0;
  } else if(m == 'c') {
    vector<vector<SimpleMatrix<num_t> > > in;
    in.reserve(argc - 2 + 1);
    for(int i0 = 2; i0 < argc; i0 ++) {
      vector<SimpleMatrix<num_t> > work;
      if(! loadp2or3<num_t>(work, argv[i0])) continue;
      in.emplace_back(move(work));
      assert(in[0].size() == in[in.size() - 1].size() &&
             in[0][0].rows() == in[in.size() - 1][0].rows() &&
             in[0][0].cols() == in[in.size() - 1][0].cols() );
    }
    cerr << "y" << flush;
    auto jy(in);
    auto left(diff<num_t>(jy[0][0].rows()));
#if defined(_OPENMP)
#pragma omp parallel for schedule(static, 1)
#endif
    for(int i = 0; i < in.size(); i ++) {
      cerr << "." << flush;
      for(int j = 0; j < in[i].size(); j ++)
        jy[i][j] = left * in[i][j];
    }
    cerr << "x" << flush;
    auto jx(in);
    auto right(diff<num_t>(jy[0][0].cols()).transpose());
#if defined(_OPENMP)
#pragma omp parallel for schedule(static, 1)
#endif
    for(int i = 0; i < in.size(); i ++) {
      cerr << "." << flush;
      for(int j = 0; j < in[i].size(); j ++)
        jx[i][j] = in[i][j] * right;
    }
    cerr << "z" << flush;
    auto jz(in);
    auto middle(diff<num_t>(jz.size()));
    for(int i = 0; i < in[0].size(); i ++) {
#if defined(_OPENMP)
#pragma omp parallel for schedule(static, 1)
#endif
      for(int j = 0; j < in[0][0].rows(); j ++) {
        cerr << "." << flush;
        for(int k = 0; k < in[0][0].cols(); k ++) {
          SimpleVector<num_t> work(in.size());
          for(int m = 0; m < work.size(); m ++)
            work[m] = in[m][i](j, k);
          work = middle * work;
          for(int m = 0; m < work.size(); m ++)
            jz[m][i](j, k) = work[m];
        }
      }
    }
    cerr << endl << "eigen: " << flush;
    // [[1, 0, 0, jx], [0, 1, 0, jy], [0, 0, 1, jz], [jx, jy, jz, z]]
#if defined(_OPENMP)
#pragma omp parallel for schedule(static, 1)
#endif
    for(int i = 0; i < in.size(); i ++) {
      cerr << "." << flush;
      for(int j = 0; j < in[i].size(); j ++)
        for(int k = 0; k < in[i][j].rows(); k ++)
          for(int m = 0; m < in[i][j].cols(); m ++) {
            SimpleMatrix<num_t> work(4, 4);
            work.I();
            work(3, 0) = work(0, 3) = jx[i][j](k, m);
            work(3, 1) = work(1, 3) = jy[i][j](k, m);
            work(3, 2) = work(2, 3) = jz[i][j](k, m);
            work(3, 3) = work(3, 3) = in[i][j](k, m);
            in[i][j](k, m) = work.determinant();
          }
    }
    in = normalize<num_t>(in);
    for(int i = 0; i < in.size(); i ++)
      if(! savep2or3<num_t>((string(argv[i + 2]) + string("-c3.ppm")).c_str(), in[i]) )
        cerr << "failed to save." << endl;
  } else if(m == 'T') {
    vector<vector<SimpleMatrix<num_t> > > in;
    in.reserve(argc - 2 + 1);
    vector<SimpleMatrix<num_t> > p;
    vector<SimpleMatrix<num_t> > avg;
    vector<vector<SimpleMatrix<num_t> > > pc;
    for(int i0 = 2; i0 < argc; i0 ++) {
      vector<SimpleMatrix<num_t> > work;
      if(! loadp2or3<num_t>(work, argv[i0])) continue;
      if(pc.size()) {
        cout << " --- " << in.size() - 11 << " --- " << endl;
        for(int i = 0; i < pc.size(); i ++)
          for(int j = 0; j < pc[i].size(); j ++) {
            if(! i) avg[j] += work[j];
            const auto rr(p[0].rows() / pc[i][0].rows());
            const auto cc(p[0].cols() / pc[i][0].cols());
            for(int k = 0; k < pc[i][j].rows(); k ++)
              for(int n = 0; n < pc[i][j].cols(); n ++) {
                num_t workr(int(0));
                num_t orig(int(0));
                num_t origa(int(0));
                int   cnt(0);
                for(int kk = k * rr; kk < min(p[j].rows(), (k + 1) * rr); kk ++)
                  for(int nn = n * cc; nn < min(p[j].cols(), (n + 1) * cc);
                    nn ++, cnt ++) {
                    workr += p[j](kk, nn);
                    orig  += work[j](kk, nn);
                    origa += avg[j](kk, nn);
                  }
                if(cnt) {
                  workr /= num_t(cnt);
                  orig  /= num_t(cnt);
                  origa /= num_t(cnt);
                }
                // N.B. for stricter test but we don't need such a restriction:
                // workr = (sgn<num_t>(workr - num_t(int(1)) / num_t(int(2)) )
                //   + num_t(int(1)) ) / num_t(int(2));
                pc[i][j](k, n) += workr;
                cout << "g: " << abs(workr - orig) * num_t(int(2)) << endl;
                cout << "s: " << abs(pc[i][j](k, n) - origa) / num_t(in.size() - 11) * num_t(int(2)) << endl;
                cout << "w: " << abs(pc[i][j](k, n) - origa) * num_t(int(2)) << endl;
              }
            cout << endl;
          }
        cout << endl;
        // N.B. output can be checked as:
        //      tail -n ... < output | grep [gsw]: | cut -f 2 -d : |
        //        python3 p2/cr.py t 1 > outR
        //      with R.app, myv <- read.csv("outR")
        //                  hist(yv[,1],breaks=seq(0,...,length.out=...))
        // N.B. s: and w: are in the walk condition.
      }
      in.emplace_back(move(work));
      if(i0 == argc - 1) break;
      if(11 < in.size()) {
        auto in2(in);
        p = predMat<num_t>(in2 = normalize<num_t>(in2)).first;
        if(! pc.size()) {
          avg.resize(p.size());
          for(int j = 0; j < avg.size(); j ++)
            avg[j] = SimpleMatrix<num_t>(p[j].rows(), p[j].cols()).O();
          pc.emplace_back(avg);
          for(int i = 1;
            0 <= i && 1 < pc[i - 1][0].rows() && 1 < pc[i - 1][0].cols();
            i ++) {
            auto work(pc[i - 1]);
            for(int j = 0; j < work.size(); j ++)
              work[j] = SimpleMatrix<num_t>(work[j].rows() / 2,
                work[j].cols() / 2).O();
            pc.emplace_back(move(work));
          }
        }
      }
    }
  } else goto usage;
  cerr << "Done" << endl;
  return 0;
 usage:
  cerr << "Usage:" << endl;
  cerr << "# copy color structure" << endl;
  cerr << argv[0] << " + <in0out.pgm> <in0in.ppm> ... > cache.txt" << endl;
  cerr << "# apply color structure" << endl;
  cerr << argv[0] << " - <in0.ppm> ... < cache.txt" << endl;
  cerr << "# predict following image (each bit input)" << endl;
  cerr << argv[0] << " [pP] <in0.ppm> ..." << endl;
  cerr << "# predict with whole pixel context (each bit input)" << endl;
  cerr << argv[0] << " w <in0.ppm> <in0-4.ppm> ..." << endl;
  cerr << "# predict down scanlines. (each bit input)" << endl;
  cerr << argv[0] << " q <in0out.ppm> ..." << endl;
  cerr << "# show continuity" << endl;
  cerr << argv[0] << " [xyit] <in0.ppm> ..." << endl;
  cerr << "# some of the volume curvature like transform" << endl;
  cerr << argv[0] << " c <in0.ppm> ..." << endl;
  cerr << "# test input series of graphics predictable or not (each bit input)" << endl;
  cerr << argv[0] << " T <in0.ppm> ..." << endl;
  return - 1;
}

