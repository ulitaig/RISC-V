#pragma once
#include "stdc++.h"
template<int bit>
struct us_bit
{
	uint val : bit;
};
uint nsex8(char o)
{
	return us_bit<8>{uint(o)}.val;
}
uint nsex16(short o)
{
	return us_bit<16>{uint(o)}.val;
}