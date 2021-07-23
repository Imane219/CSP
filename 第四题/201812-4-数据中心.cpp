//140ms 4.039MB
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXM 100001
struct Edge
{
	unsigned int u, v;
	long t;
	bool operator < (const Edge& a)const
	{
		return t < a.t;
	}
}e[MAXM];
unsigned int f[MAXM];

//初始化并查集
void init(unsigned int n)
{
	unsigned int i;
	for (i = 0; i < n; i++)
	{
		f[i] = i;
	}
}

//查找根节点，路径压缩
unsigned int find(unsigned int i)
{
	unsigned int tmp = i;
	while (f[tmp] != tmp)
	{
		tmp = f[tmp];
	}
	while (i != tmp)
	{
		unsigned int k = i;
		i = f[i];
		f[k] = tmp;
	}
	return tmp;
}

//合并两个集合
bool join(unsigned int a, unsigned int b)
{
	unsigned int fa = find(a);
	unsigned int fb = find(b);
	if (fa != fb)
	{
		f[fb] = fa;
		return true;
	}
	return false;
}

int main()
{
	long m, ans = 0;
	unsigned int n, root, count = 0;;
	scanf("%u%ld%u", &n, &m, &root);
	for (long i = 0; i < m; i++)
	{
		scanf("%u%u%ld", &e[i].v, &e[i].u, &e[i].t);
	}
	init(n);
	sort(e, e + m);
	for (unsigned int i = 0; i < m; i++)
	{
		unsigned int a, b;
		a = e[i].v;
		b = e[i].u;
		if (join(a, b))
		{
			count++;
			ans = e[i].t;
			if (count == n - 1)
				break;
		}
	}
	printf("%ld", ans);
	return 0;
}
