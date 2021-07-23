//281ms 15.05mb
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

struct IP
{
    string ip;
    int len;
    bool operator <(const IP& a)const
    {
        return ip == a.ip ? (len < a.len) : (ip < a.ip);
    }
};
list<IP> l;
IP aip;
list<IP>::iterator it1, it2;
long n;

//将十进制数值转换成二进制串
string itos(int val)
{
    string tmp = "00000000";
    int i;
    for (i = 7; i >= 0 && val; i--)
    {
        tmp[i] = val % 2 + '0';
        val /= 2;
    }
    return tmp;
}

//读入ip前缀
void read()
{
    while (n--)
    {
        char c;
        string tip = "";
        int val = 0, k = 0, flag = 0;
        while ((c = getchar()) != '\n')
        {
            if (c == '.')
            {
                tip += itos(val);
                val = 0;
                k++;
            }
            else if (c == '/')
            {
                tip += itos(val);
                val = 0;
                flag = 1;
            }
            else
            {
                val *= 10;
                val += c - '0';
            }
        }
        int len = flag ? val : (k + 1) * 8;
        if (!flag)
            tip += itos(val);
        int i;
        for (i = k; i < 3; i++)
        {
            tip += "00000000";
        }
        aip.ip = tip;
        aip.len = len;
        l.push_back(aip);
    }
}

//从小到大合并
void merge1()
{
    int i;
    for (it1 = l.begin(); it1 != l.end();)
    {
        it2 = it1;
        it2++;
        if (it2 == l.end())
            break;
        for (i = 0; i < it1->len; i++)
        {
            if (it1->ip[i] != it2->ip[i])
                break;
        }
        if (i == it1->len)
            l.erase(it2);
        else
            it1++;
    }
}

//同级合并
void merge2()
{
    int i, len;
    for (it1 = l.begin(); it1 != l.end(); )
    {
        it2 = it1;
        it2++;
        if (it2 == l.end())
            break;
        len = it1->len;
        if (len == it2->len)
        {
            for (i = 0; i < len - 1; i++)
            {
                if (it1->ip[i] != it2->ip[i])
                    break;
            }
            if (i == len - 1)
            {
                l.erase(it2);
                (it1->len)--;
                if (it1 != l.begin())
                    it1--;
            }
            else
                it1++;
        }
        else
            it1++;
    }
}

int main()
{
    int val = 0;
    scanf("%ld", &n);
    getchar();
    read();
    l.sort();
    merge1();
    merge2();
    for (it1 = l.begin(); it1 != l.end(); it1++)
    {
        for (int i = 0; i < 32; i += 8)
        {
            val = 0;
            for (int j = i; j < i + 8; j++)
            {
                val = val * 2 + it1->ip[j] - '0';
            }
            printf("%d", val);
            if (i != 24)
                putchar('.');
        }
        printf("/%d\n", it1->len);
    }
    return 0;
}
