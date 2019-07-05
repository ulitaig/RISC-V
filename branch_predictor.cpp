#include "stdc++.h"
#include "branch_predictor.h"
using namespace std;
const int N = 1000003;
struct node
{
	static const int n1 = 6, m1 = 3, n2 = 4, m2 = 2;
	uint pre;
	int to;
	short state[4], cplex[4];
	int njal[16], jal[16];

	int v;
	node()
	{
		pre = 0; to = -1; v = -1;
		for (int i = 0; i < 4; i++)
			cplex[i] = m2-1 , state[i] = m1 - 1;

		memset(njal, 0, sizeof(njal));
		memset(jal, 0, sizeof(jal));
	}
	void chs(const int &k)
	{
		if (state[k] > 0) state[k]--;
	}
	void nchs(const int &k)
	{
		if (state[k] < n1 - 1) state[k]++;
	}

	void is_right(const int &k)
	{
		if (cplex[k] > 0) cplex[k]--;
	}
	void not_right(const int &k)
	{
		if (cplex[k] < n2 - 1) cplex[k]++;
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
	node &o = H(pos);
	que.push(pos);
	int n2 = getseg(o.pre, 0, 1);
	o.pre <<= 1;
	if (o.to == -1) return pos + 4;
	if (o.cplex[n2] < node::m2)//using Two-level adaptive predictor
	{
		if (o.state[n2] < node::m1)
		{
			o.pre += 1;
			return o.to;
		}
	}
	else//overriding, and using local branch predictor
	{
		int n4 = getseg(o.pre, 0, 3);
		if (o.jal[n2] >= o.njal[n2])
		{
			o.pre += 1;
			return o.to;
		}
	}
	return pos + 4;
}
bool check(int PC)
{
	int pos = que.front();
	que.pop();
	node &o = H(pos);
	int n2 = getseg(o.pre, 1, 2), n4 = getseg(o.pre, 1, 4);;
	if (PC == pos + 4)
	{
		if (o.state[n2] < node::m1) o.not_right(n2);
		else o.is_right(n2);

		o.nchs(n2);
		o.njal[n4]++;
		if ((o.pre & 1) == 1)
		{
			o.pre -= 1;
			return false;
		}
		return true;
	}
	o.chs(n2);
	o.jal[n4]++;
	if (o.to == -1)
	{
		o.to = PC;
		if ((o.pre & 1) == 0)
		{
			o.pre += 1;
		}
		return false;
	}

	if (o.state[n2] < node::m1) o.is_right(n2);
	else o.not_right(n2);

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