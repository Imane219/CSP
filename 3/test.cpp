#include <iostream>
#include <sstream>
#include <regex>
#include <string>
using namespace std;

int main()
{
  string s;
  cin >> s;
  s = regex_replace(s,regex("\\.")," ");
  stringstream all;
  all << s;
  string tmp = "";
  all >> tmp;
  cout << tmp << endl;
  all >> tmp;
  cout << tmp << endl;
  tmp = "m";
  all >> tmp;
  cout << tmp << endl;
  return 0;
}