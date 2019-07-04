#include "stdc++.h"
#include "memact.h"
#include "signextern.h"
using namespace std;
char mem[0x20005];
inline int read()
{
	int r = 0; char ch = getchar();
	if (ch == EOF) return -2;
	while ((ch<'0' || ch>'9') && (ch<'A' || ch>'F'))
	{
		if (ch == '@') return -1;
		ch = getchar();
		if (ch == EOF) return -2;
	}
	while ((ch >= '0'&&ch <= '9') || (ch >= 'A'&&ch <= 'F'))
	{
		r = r * 16 + ch - (ch >= '0'&&ch <= '9' ? '0' : 'A' - 10);
		ch = getchar();
		if (ch == EOF) return -2;
	}
	return r;
}
void meminit()
{
	int p = 0, a;
	while ((a = read()) != -2)
	{
		if (a == -1) p = read();
		else
		{
			mem[p] = a;
			p++;
		}
	}
}
int readins(int pos)
{
	return (nsex8(mem[pos])) +
		(nsex8(mem[pos + 1]) << 8) +
		(nsex8(mem[pos + 2]) << 16) +
		(nsex8(mem[pos + 3]) << 24);
}
int readnum(int pos, int bit)
{
	if (bit == 32) return *reinterpret_cast<uint*>(mem + pos);
	else if (bit == 16)return *reinterpret_cast<short*>(mem + pos);
	else return *reinterpret_cast<char*>(mem + pos);
}
uint readnumU(int pos, int bit)
{
	if (bit == 32) return *reinterpret_cast<int*>(mem + pos);
	else if (bit == 16)return nsex16(*reinterpret_cast<short*>(mem + pos));
	else return nsex8(*reinterpret_cast<char*>(mem + pos));
}
void writenum(int pos, int bit, uint v)
{
	if (bit == 32) *reinterpret_cast<int*>(mem + pos) = v;
	else if (bit == 16) *reinterpret_cast<short*>(mem + pos) = v;
	else *reinterpret_cast<char*>(mem + pos) = v;
}