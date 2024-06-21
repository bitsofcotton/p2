#include <cstdio>
#include <iostream>
#include <iomanip>
#include <random>

int main(int argc, const char* argv[]) {
  std::cout << std::setprecision(30);
  std::random_device r;
  std::default_random_engine er(r());
  std::mt19937 mt(r());
  std::ranlux24 rl24(r());
  std::ranlux48 rl48(r());
  std::knuth_b kb(r());
  std::uniform_int_distribution<int> ud(0, 0x2000);
  while(true) {
    std::cout << (int(arc4random_uniform(0x2001)) - 0x1000) << ",";
    std::cout << (ud(er) - 0x1000) << ",";
    std::cout << (ud(mt) - 0x1000) << ",";
    std::cout << (ud(rl24) - 0x1000) << ",";
    std::cout << (ud(rl48) - 0x1000) << ",";
    std::cout << (ud(kb) - 0x1000) << std::endl << std::flush;
  }
  return 0;
}

