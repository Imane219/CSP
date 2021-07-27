#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 101

struct Rule
{
    string name;
    vector<string> rule;
    bool end;
}r[N];
int m,n;
bool url_end = false;//记录当前匹配的url的尾部是否有'/'

//读入匹配规则
void read(int i)
{
    char str[N] = {0};
    string name;
    scanf("%s",str);
    int len = strlen(str);
    if(str[len-1] == '/')r[i].end = true;
    else r[i].end = false;
    cin >> name;
    r[i].name = name;
    char *p = strtok(str,"/");
    while(p)
    {
        r[i].rule.push_back(p);
        p = strtok(NULL,"/");
    }
}

//读入url
bool read_url(vector<string> &url)
{
    char c;
    string s = "";
    int flag = 1;

    getchar();//读走开头'/'
    while((c = getchar()) != '\n')
    {
        if(c == '/')
        {
            url.push_back(s);
            s = "";
            flag = 1;
        }
        else if((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0')
                || c == '-' || c == '_' || c =='.')//判断合法字符
        {
            s += c;
            flag = 0;
        }
        else
        {
            while((c = getchar()) != '\n');
            return false;
        }
    }
    if(!s.empty())
    {
        url.push_back(s);
    }
    if(flag == 1)
        url_end = true;
    else
        url_end = false;
    return true;
}

//判断是否全是数字
bool isnum(string s)
{
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

//匹配
void compare(vector<string> url, vector<string>& ans)
{
    int i;
    for(i = 0; i < n; i++)//n条规则逐条匹配
    {
        int j,k;
        ans.clear();
        for(j = 0, k = 0; j < r[i].rule.size() && k < url.size();)//j用于跟踪规则，k用于跟踪url
        {
            string s = r[i].rule[j];
            if(s == "<int>")
            {
                if(!isnum(url[k]))break;
                int pos = 0;
                while(url[k][pos] == '0' && pos < url[k].size() - 1)pos++;
                ans.push_back(url[k].substr(pos));
                j++,k++;
            }
            else if(s == "<str>")
            {
                ans.push_back(url[k]);
                j++,k++;
            }
            else if(s == "<path>")
            {
                string tmp = "";
                while(k < url.size())
                {
                    tmp += "/";
                    tmp += url[k++];
                }
                tmp = tmp.substr(1);
                if(url_end == true)
                    tmp += "/";
                ans.push_back(tmp);
                j++;
            }
            else
            {
                if(s != url[k])break;
                j++,k++;
            }
        }
        if(j == r[i].rule.size() && k == url.size() && url_end == r[i].end)//注意条件
        {
            break;
        }
    }
    if(i == n)
    {
        printf("404\n");
    }
    else
    {
        cout << r[i].name;
        for(int j = 0; j < ans.size(); j++)
        {
            cout << " " << ans[j];
        }
        cout << endl;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    getchar();
    for(int i = 0; i < n; i++)
    {
        read(i);
        getchar();
    }
    for(int i = 0; i < m; i++)
    {
        vector<string> url, ans;
        if(!read_url(url))
        {
            printf("404\n");
            continue;
        }
        compare(url,ans);
    }
    return 0;
}