#pragma once
#include"stdc++.h"
using namespace std;
class instruction
{
private:
	static const uint one = ((1 << 21) - 1) << 11;
	static const uint two = ((1 << 20) - 1) << 12;
	static const uint thr = ((1 << 1) - 1) << 31;
	static const uint fou = ((1 << 12) - 1) << 20;
	uint readI(uint ins)
	{
		uint ans = getseg(ins, 20, 30);
		if (getseg(ins, 31, 31) == 1)
		{
			ans |= one;
		}
		return ans;
	}
	uint readS(uint ins)
	{
		uint ans = getseg(ins, 7, 11) + (getseg(ins, 25, 30) << 5);
		if (getseg(ins, 31, 31) == 1)
		{
			ans |= one;
		}
		return ans;
	}
	uint readSB(uint ins)
	{
		uint ans = (getseg(ins, 8, 11) << 1) +
			(getseg(ins, 25, 30) << 5) +
			(getseg(ins, 7, 7) << 11);
		if (getseg(ins, 31, 31) == 1)
		{
			ans |= two;
		}
		return ans;
	}
	uint readU(uint ins)
	{
		uint ans = (getseg(ins, 12, 30) << 12);
		if (getseg(ins, 31, 31) == 1)
		{
			ans |= thr;
		}
		return ans;
	}
	uint readUJ(uint ins)
	{
		uint ans = (getseg(ins, 21, 30) << 1) +
			(getseg(ins, 20, 20) << 11) +
			(getseg(ins, 12, 19) << 12);
		if (getseg(ins, 31, 31) == 1)
		{
			ans |= fou;
		}
		return ans;
	}
public:
	
	int cas, rs1, rs2, rd, rdval, str, pc;
	bool chgRD = false;
	uint imm;
	instruction()
	{
		clear();
	}
	instruction(uint ins)
	{
		str = ins;
		cas = rs1 = rs2 = rd = -1;
		imm = 0;
		uint J = getseg(ins, 0, 6);
		int k, g;
		switch (J)
		{
		case 55:
			cas = 1;
			rd = getseg(ins, 7, 11);
			imm = readU(ins);
			break;
		case 23:
			cas = 2;
			rd = getseg(ins, 7, 11);
			imm = readU(ins);
			break;
		case 111:
			cas = 3;
			rd = getseg(ins, 7, 11);
			imm = readUJ(ins);
			break;
		case 103:
			cas = 4;
			rd = getseg(ins, 7, 11);
			rs1 = getseg(ins, 15, 19);
			imm = readI(ins);
			break;
		case 99:
			rs1 = getseg(ins, 15, 19);
			rs2 = getseg(ins, 20, 24);
			imm = readSB(ins);
			k = getseg(ins, 12, 14);
			if (k == 0) cas = 5;
			else if (k == 1) cas = 6;
			else if (k == 4) cas = 7;
			else if (k == 5) cas = 8;
			else if (k == 6) cas = 9;
			else if (k == 7) cas = 10;
			break;
		case 3:
			rd = getseg(ins, 7, 11);
			rs1 = getseg(ins, 15, 19);
			imm = readI(ins);
			k = getseg(ins, 12, 14);
			if (k == 0) cas = 11;
			else if (k == 1) cas = 12;
			else if (k == 2) cas = 13;
			else if (k == 4) cas = 14;
			else if (k == 5) cas = 15;
			break;
		case 0b0100011:
			rs1 = getseg(ins, 15, 19);
			rs2 = getseg(ins, 20, 24);
			imm = readS(ins);
			k = getseg(ins, 12, 14);
			if (k == 0) cas = 16;
			else if (k == 1) cas = 17;
			else if (k == 2) cas = 18;
			break;
		case 0b0010011:
			rd = getseg(ins, 7, 11);
			k = getseg(ins, 12, 14);
			if (k == 0)
			{
				cas = 19;
				rs1 = getseg(ins, 15, 19);
				imm = readI(ins);
			}
			else if (k == 0b010)
			{
				cas = 20;
				rs1 = getseg(ins, 15, 19);
				imm = readI(ins);
			}
			else if (k == 0b011)
			{
				cas = 21;
				rs1 = getseg(ins, 15, 19);
				imm = readI(ins);
			}
			else if (k == 0b100)
			{
				cas = 22;
				rs1 = getseg(ins, 15, 19);
				imm = readI(ins);
			}
			else if (k == 0b110)
			{
				cas = 23;
				rs1 = getseg(ins, 15, 19);
				imm = readI(ins);
			}
			else if (k == 0b111)
			{
				cas = 24;
				rs1 = getseg(ins, 15, 19);
				imm = readI(ins);
			}
			else if (k == 0b001)
			{
				cas = 25;
				rs1 = getseg(ins, 15, 19);
				imm = getseg(ins, 20, 24);
			}
			else if (k == 0b101)
			{
				g = getseg(ins, 25, 31);
				if (g == 0)
				{
					cas = 26;
					rs1 = getseg(ins, 15, 19);
					imm = getseg(ins, 20, 24);
				}
				else
				{
					cas = 27;
					rs1 = getseg(ins, 15, 19);
					imm = getseg(ins, 20, 24);
				}
			}
			break;
		case 0b0110011:
			rs1 = getseg(ins, 15, 19);
			rs2 = getseg(ins, 20, 24);
			rd = getseg(ins, 7, 11);
			k = getseg(ins, 12, 14);
			g = getseg(ins, 25, 31);
			if (k == 0) cas = (g == 0 ? 28 : 29);
			else if (k == 1) cas = 30;
			else if (k == 0b010) cas = 31;
			else if (k == 0b011) cas = 32;
			else if (k == 0b100) cas = 33;
			else if (k == 0b101) cas = (g == 0 ? 34 : 35);
			else if (k == 0b110) cas = 36;
			else if (k == 0b111) cas = 37;
			break;
		default:
			break;
		}
	}
	void clear()
	{
		pc = imm = str = rdval = cas = 0;
		rs1 = rs2 = rd = -1;
		chgRD = false;
	}
};