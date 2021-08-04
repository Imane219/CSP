//0ms 2.902MB
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <stack>
using namespace std;

#define N 101

map<string, string> mp[N];
int m,n;

string read_str()
{
  string s = "";
  char c = getchar();
  char pre = c;
  s += c;
  while(c = getchar())
  {
    if(c == '"')
    {
      if(pre == '\\')
        s[s.size()-1] = c;
      else
        break;
    }
    else if(c == '\\')
    {
      if(pre == '\\')
      {
        pre = 0;//注意此时'\\'是一个整体代表字符\，就算后面有"or\也不能再进行转义
        continue;
      }
      else
        s += c;
    }
    else
      s += c;
    pre = c;
  }
  return s;
}

void read_query(vector<string> &query)
{
  string s = "";
  cin >> s;
  s = regex_replace(s,regex("\\.")," ");
  stringstream all;
  all << s;
  string tmp = "";
  while(all >> tmp)//相当于strtok
  {
    query.push_back(tmp);
  }
}

int main()
{
  scanf("%d%d",&n,&m);
  getchar();
  stack<string> st;
  int index = 0;
  //读入json文件
  while(n)
  {
    char c = getchar();
    if(c == '{')
      st.push("{");
    else if(c == '\n')
      n--;
    else if(c == '"')
      st.push(read_str());
    else if(c == '}')
    {
      index++;
      while(st.top() != "{")
      {
        string value = st.top();
        st.pop();
        string key = st.top();
        st.pop();
        mp[index].insert(make_pair(key,value));
      }
      st.pop();//pop掉'{'
      if(st.size() > 0)
        st.push(string(index,' '));
    }
  }
  //读入m个查询
  while(m--)
  {
    vector<string> query;
    read_query(query);
    int j = index;
    for(int i = 0; i < query.size(); i++)
    {
      map<string,string>::iterator it = mp[j].find(query[i]);
      if(it == mp[j].end())
      {
        cout << "NOTEXIST" << endl;
        break;
      }
      else
      {
        if(i == query.size()-1)
        {
          if(it->second[0] == ' ')
          {
            cout << "OBJECT" << endl;
            break;
          }
          else
          {
            cout << "STRING " << it->second << endl;
            break;
          }
        }
        else
        {
          if(it->second[0] != ' ')//对字符串进行对象查询
          {
            cout << "NOTEXIST" << endl;
            break;
          }
          j = it->second.size();
        }
      }
    }
  }
  return 0;
}