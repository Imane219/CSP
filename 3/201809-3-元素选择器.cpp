#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define N 101

struct Node
{
    string lable, id;
    int cnt;
}a[N];
int m, n;

//判断单个标签or属性是否检索的到
bool selector(int start, int& end, string s, int& cnt)
{
    for(int i = end-1; i >= 0; i--)
    {
        if(a[i].cnt < cnt)
        {
            cnt = a[i].cnt;//只有在同一棵树内才符合祖先定义
            end = i;
            if(a[i].lable == s || a[i].id == s)return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d%d",&n,&m);
    getchar();
    char c;
    //读入n行元素
    for(int i = 0; i < n; i++)
    {
        int cnt = 0, flag = 0;
        string lable = "", id = "";
        while((c = getchar()) != '\n')
        {
            if(c == '.')
            {
                cnt++;
                continue;
            }
            if(c == ' ')
            {
                flag = 1;
                continue;
            }
            if(flag == 1)
            {
                if(c != '\n')
                    id += c;
                else
                    flag = 0;
            }
            else
                lable += c;

        }
        transform(lable.begin(),lable.end(),lable.begin(),::tolower);//lable变小写存储
        a[i].cnt = cnt;
        a[i].id = id;
        a[i].lable = lable;
    }
    //查询m个选择器
    for(int i = 0; i < m; i++)
    {
        string s = "";
        vector<string> v;
        vector<int> ans;
        while((c = getchar()) != '\n')
        {
            if(c == ' ')
            {
                if(s[0] != '#')
                {
                    transform(s.begin(),s.end(),s.begin(),::tolower);
                }
                v.push_back(s);
                s = "";
            }
            else
            {
                s += c;
            }
        }
        if(s[0] != '#')
        {
            transform(s.begin(),s.end(),s.begin(),::tolower);
        }
        v.push_back(s);
        int len = v.size();
        //对每个存在于文档中的末级元素，若所有祖先满足则成功select
        for(int j = 0; j < n; j++)
        {
            if(a[j].id == v[len-1] || a[j].lable == v[len-1])
            {
                int end = j, cnt = a[j].cnt, k;
                for(k = len-2; k >= 0; k--)//判断祖先是否满足
                {
                    if(!selector(0,end,v[k],cnt))break;
                }
                if(k < 0)
                    ans.push_back(j+1);
            }
        }
        len = ans.size();
        printf("%d",len);
        for(int j = 0; j < len; j++)
        {
            printf(" %d", ans[j]);
        }
        putchar('\n');
    }
    return 0;
}