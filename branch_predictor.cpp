#include "stdc++.h"
#include "branch_predictor.h"
using namespace std;
const int N = 1000003;
struct node
{
	int pre;
	int to;
	int njal[4],jal[4];

	int v;
	node()
	{
		pre = 0; to = -1; v = -1;
		memset(njal, 0, sizeof(njal));
		memset(jal, 0, sizeof(jal));
	}
}h[N + 5];
inline node& H(int o)
{
	int k = (o%N);
	while (h[k].v >= 0 && h[k].v != o) k = (k + 1) % N;
	if (h[k].v == -1) h[k].v = o;
	return h[k];
}
queue<int> que;
int predict(int pos)
{
	node o = H(pos);
	que.push(pos);
	int n2 = getseg(o.pre, 0, 1);
	o.pre <<= 1;
	if (o.to == -1) return pos + 4;
	if (o.jal[n2] >= o.njal[n2])
	{
		o.pre += 1;
		return o.to;
	}
	return pos + 4;
}
bool check(int PC)
{
	int pos = que.front();
	que.pop();
	node o = H(pos);
	int n2 = getseg(o.pre, 1, 2);
	if (PC == pos + 4)
	{
		o.njal[n2]++;
		if ((o.pre & 1) == 1)
		{
			o.pre -= 1;
			return false;
		}
		return true;
	}
	o.jal[n2]++;
	if (o.to == -1)
	{
		o.to = PC;
		if ((o.pre & 1) == 0)
		{
			o.pre += 1;
		}
		return false;
	}
	if ((o.pre & 1) == 0)
	{
		o.pre += 1;
		return false;
	}
	return true;
}
void popone()
{
	que.pop();
}

