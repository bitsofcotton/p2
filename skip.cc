#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
  std::string s;
  int t(0);
  for( ; std::getline(std::cin, s, '\n'); t ++)
    if(! (t % std::atoi(argv[1]))) {
      std::string buf;
      int start(0);
      int end(s.size());
      int cnt(0);
      for( ; start < s.size(); start ++)
        if(std::atoi(argv[2]) <= cnt)
          break;
        else if(s[start] == ',') cnt ++;
      for(end = start; end < s.size(); end ++)
        if(s[end] == ',') break;
      std::cout << s.substr(start, end) << std::endl;
    }
  return 0;
}

