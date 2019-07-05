#pragma once
#include "stdc++.h"
template<int bit>
struct us_bit
{
	uint val : bit;
};
inline uint nsex8(char o)
{
	return us_bit<8>{uint(o)}.val;
}
inline uint nsex16(short o)
{
	return us_bit<16>{uint(o)}.val;
}