#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<queue>
#include<algorithm>
#include<sstream>

using namespace std;

const int maxn = 501;
const int maxm = 2501;
int q,m,n,s;
int degree[maxn];
pair<string, vector<int> > device[maxm];
vector<int> graph[maxn];
vector<int> top;
bool output[maxn];

bool toposort()
{
  queue<int> q;
  int num = 0;
  for(int i = 1; i <= n; i++)
  {
    if(degree[i] == 0)
      q.push(i);
  }
  while(!q.empty())
  {
    int t = q.front();
    q.pop();
    top.push_back(t);
    num++;
    for(int i = 0; i < graph[t].size(); i++)
    {
      int v = graph[t][i];
      degree[v]--;
      if(degree[v] == 0)
        q.push(v);
    }
  }
  if(num == n) return true;
  else return false;
}

void calculate(vector<int> v)
{
  for(int i = 0; i < top.size(); i++)
  {
    int u = top[i];
    string s = device[u].first;
    if(s == "NOT")
    {
      int t = device[u].second[0];
      output[u] = !(t > 0 ? output[t] : v[-t]);
    }
    else if(s == "AND")
    {
      output[u] = true;
      for(int j = 0; j < device[u].second.size(); j++)
      {
        int t = device[u].second[j];
        output[u] &= (t > 0 ? output[t] : v[-t]);
      }
    }
    else if(s == "OR")
    {
      output[u] = false;
      for(int j = 0; j < device[u].second.size(); j++)
      {
        int t = device[u].second[j];
        output[u] |= (t > 0 ? output[t] : v[-t]);
      }
    }
    else if(s == "XOR")
    {
      output[u] = false;
      for(int j = 0; j < device[u].second.size(); j++)
      {
        int t = device[u].second[j];
        output[u] ^= (t > 0 ? output[t] : v[-t]);
      }
    }
    else if(s == "NAND")
    {
      output[u] = true;
      for(int j = 0; j < device[u].second.size(); j++)
      {
        int t = device[u].second[j];
        output[u] &= (t > 0 ? output[t] : v[-t]);
      }
      output[u] = !output[u];
    }
    else
    {
      output[u] = false;
      for(int j = 0; j < device[u].second.size(); j++)
      {
        int t = device[u].second[j];
        output[u] |= (t > 0 ? output[t] : v[-t]);
      }
      output[u] = !output[u];
    }
  }
}

int main()
{
  scanf("%d",&q);
  while(q--)
  {
    scanf("%d%d",&m,&n);

    //清空graph,device,top,degree
    for(int i = 0; i < maxm; i++)
      device[i].second.clear();
    for(int i = 0; i < maxn; i++)
    {
      graph[i].clear();
      degree[i] = 0;
    }
    top.clear();  

    //建图
    for(int i = 1; i <= n; i++)
    {
      int k = 0;
      cin >> device[i].first >> k;
      while(k--)
      {
        string s = "";
        int t;
        cin >> s;
        stringstream ss;
        ss << s.substr(1);
        ss >> t;
        device[i].second.push_back(s[0] == 'O' ? t : -t);
        if(s[0] == 'O')
        {
          graph[t].push_back(i);
          degree[i]++; //记得记录入度
        }
      }
    }

    //读入s个输入的值
    scanf("%d",&s);
    vector<vector<int> > input(s, vector<int>(m+1));//通过构造函数构造二位变长数组
    for(int i = 0; i < s; i++)
    {
      for(int j = 1; j <= m; j++)
      {
        cin >> input[i][j];
      }
    }

    //拓扑排序
    bool loop = toposort();
    if(!loop)
      cout << "LOOP" << endl;

    //对s行输入逐行处理
    for(int i = 0; i < s; i++)
    {
      if(loop) calculate(input[i]);//求出所有的output
      int k = 0, tmp = 0;
      cin >> k;
      while(--k)
      {
        cin >> tmp;
        if(loop) cout << output[tmp] << " ";
      }
      cin >> tmp;
      if(loop) cout << output[tmp] << endl;
    }
  }
  return 0;
}

