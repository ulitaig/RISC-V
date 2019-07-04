#pragma once
#include"stdc++.h"
#include"instruction.h"
using namespace std;
struct registers
{
	int x[32];
	int PC, RS1, RS2, IMM, RD, address, chgmemtype;//0 LW; 1 LH; 2 LB; 3 LHU; 4 LBU; 5 SW; 6 SH; 7 SB
	bool chgPC,chgmem;
	int chged[32];
	instruction tmp[4];
	registers() :PC(0), RS1(0), RS2(0), RD(0), chgPC(false), IMM(0), chgmem(0)
	{
		memset(x, 0, sizeof(x));
		memset(chged, 0, sizeof(chged));
	}
	void clear()
	{
		if(tmp[1].rd>0)
			chged[tmp[1].rd]--;
		tmp[2].clear();
		tmp[1].clear();
		tmp[0].clear();
		RS1 = RS2 = IMM = RD = 0;
		chgPC = chgmem = false;
	}
};