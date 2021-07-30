//93ms 3.359MB
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 21
#define M 10001

struct Time
{
  int y,m,d,h,min;
}s,t;

struct Crontab
{
  vector< pair< int,int> > Cron[5];
  string cmd;
}input[N];

struct Ans
{
  long long time;
  string cmd;
  int num;
  bool operator < (const Ans &a) const
  {
    return time == a.time ? (num < a.num) : (time < a.time);
  }
};
vector<Ans> ans;
Ans tmp_ans;

map<string,int> month
{
  {"jan",1},{"feb",2},{"mar",3},{"apr",4},{"may",5},{"jun",6},
  {"jul",7},{"aug",8},{"sep",9},{"oct",10},{"nov",11},{"dec",12}
};
map<string,int> week
{
  {"sun",0},{"mon",1},{"tue",2},{"wed",3},{"thu",4},{"fri",5},{"sat",6}
};

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int n;

//string转换为十进制数
int strtoint(string s)
{
  int ans = 0;
  for(int i = 0; i < s.size(); i++)
  {
    ans = ans *10 + s[i] - '0';
  }
  return ans;
}

//month和week的英文映射到数字
int strmap(int j, string s)
{
  map<string,int>::iterator it;
  if(j == 3)
  {
    it = month.find(s);
    if(it == month.end())//注意先判断是否存在key
      return -1;
    else
      return it->second;
  }
  else
  {
    it = week.find(s);
    if(it == week.end())//注意先判断是否存在key
      return -1;
    else
      return it->second;
  }
}

//读取配置规则
void read(Crontab &input)
{
  for(int j = 0; j < 5; j++)
  {
    char s[100] = {0};
    vector<string> tmp;
    scanf("%s",s);
    strlwr(s);//转换成小写，无需担心标点数字，只会转换大写字母
    char *p = strtok(s,",");
    while(p)
    {
      tmp.push_back(p);
      p = strtok(NULL, ",");
    }
    if(tmp[0] == "*")//任意字符的范围是[-1,-1]
      input.Cron[j].push_back(make_pair(-1,-1));
    else//否则可能是, -组合的数字字符段:1-3,jul-8
    {
      for(int k = 0; k < tmp.size(); k++)
      {
        int pos = tmp[k].find("-");
        string s1 = "", s2 = "";
        int v1 = -1,v2 = -1;
        if(pos == string::npos)//单个值
        {
          s1 = tmp[k];
          s2 = tmp[k];
        }
        else//-链接的头尾值
        {
          s1 = tmp[k].substr(0,pos);
          s2 = tmp[k].substr(pos+1);
        }
        if(j == 3 || j == 4)//month或者week映射成数字，若本身是数字则返回-1
        {
          v1 = strmap(j,s1);
          v2 = strmap(j,s2);
        }
        //只有map成功的v才有效，没有map(数字)或map失败(数字)都从s转换
        if(v1 == -1)v1 = strtoint(s1);
        if(v2 == -1)v2 = strtoint(s2);
        input.Cron[j].push_back(make_pair(v1,v2));
      }
    }
  }
  //读入command
  cin >> input.cmd;
}

//判断是否满足规则
bool in(int a, vector<pair<int,int> >v)
{
  if(v[0].first == -1)return true;//遇到*
  for(int i = 0; i < v.size(); i++)
  {
    if(a >= v[i].first && a <= v[i].second)
      return true;
  }
  return false;
}

//判断是否闰年
bool leap(int y)
{
  return (!(y % 400) || (!(y % 4) && (y % 100)));
}

//判断当前日期是第几周
int cal_week(int y, int m, int d)
{
  //1970-01-01 thu
  long long day = 0;
  for(int i = 1970; i < y; i++)
  {
    if(leap(i))
      day += 366;
    else
      day += 365;
  }
  for(int i = 1; i < m; i++)
  {
    day += days[i];
  }
  if(leap(y) && m > 2)
    day++;
  day += d - 1;
  return (day+4)%7;//注意被模数为正
}

//判断是否到达截止时间
bool end(int y, int m, int d, int h, int min, Time t)
{
  if(y < t.y) return false;
  if(m > t.m) return true;
  if(m < t.m) return false;
  if(d > t.d) return true;
  if(d < t.d) return false;
  if(h > t.h) return true;
  if(h < t.h) return false;
  if(min > t.min) return true;
  if(min < t.min) return false;
  return true;
}

//判断是否满足第num条匹配规则
void judge(Crontab &input, int num)
{
  int y = s.y, m = s.m, d = s.d, h = s.h, min = s.min;
  int day = 0;
  
  for(; y <= t.y; y++, m = 1)//第二年开始从1月开始算
  {
    for(; m <= 12; m++, d = 1)//第二个月从1号开始算
    {
      if(in(m,input.Cron[3]))
      {
        day = days[m];
        if(m == 2 && leap(y))
          day++;
        for(; d <= day; d++, h=0)//第二天从0h开始算
        {
          if(in(d,input.Cron[2]) && in(cal_week(y,m,d), input.Cron[4]))
            for(;h < 24; h++, min=0)//第二h从0min开始算
            {
              if(in(h,input.Cron[1]))
                for(; min < 60; min++)
                {
                  if(end(y,m,d,h,min,t))break;
                  if(in(min,input.Cron[0]))
                  {
                    //注意整数溢出的问题
                    long long a = (long long)y*100000000 + (long long)m*1000000 + (long long)d*10000 + (long long)h*100 + min;
                    tmp_ans.time = a;
                    tmp_ans.num = num;
                    tmp_ans.cmd = input.cmd;
                    ans.push_back(tmp_ans);
                  }
                }
            }
        }
      }
    }
  }
}



int main()
{
  scanf("%d",&n);
  //会自动处理前导0，若是00会保留一个0
  scanf("%4d%2d%2d%2d%2d",&s.y,&s.m,&s.d,&s.h,&s.min);
  scanf("%4d%2d%2d%2d%2d",&t.y,&t.m,&t.d,&t.h,&t.min);
  for(int i = 0; i < n; i++)
  {
    read(input[i]);
  }
  for(int i = 0; i < n; i++)
  {
    judge(input[i], i);
  }
  sort(ans.begin(), ans.end());
  for(int i = 0; i < ans.size(); i++)
  {
    printf("%lld ", ans[i].time);
    cout << ans[i].cmd << endl;
  }
  return 0;
}