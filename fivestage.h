#pragma once
#include "stdc++.h"
#include "memact.h"
#include "register.h"
#include "instruction.h"
using namespace std;
extern registers rs;
inline bool stage1()
{
	int insn = 0;
	insn = readins(rs.PC);

	instruction ins(insn);
	rs.tmp[0] = ins;

	if (insn == 0x00c68223) return false;

	

	/*static int i = 0;
	if (i == 0)
	{
		i++;
		rs.tmp[0].cas = 18;
		rs.tmp[0].rs1 = 1;
		rs.tmp[0].imm = 1000;
		rs.tmp[0].rs2 = 4;
	}
	else if (i == 1)
	{
		i++;
		rs.tmp[0].cas = 13;
		rs.tmp[0].rs1 = 2;
		rs.tmp[0].imm = 999;
		rs.tmp[0].rd = 10;
	}
	else return false;*/

	rs.PC += 4;
	return true;
}
inline bool stage2()
{
	if (rs.tmp[0].rs1 >= 0)
	{
		if (rs.chged[rs.tmp[0].rs1]) return false;
		rs.RS1 = rs.x[rs.tmp[0].rs1];
	}
	if (rs.tmp[0].rs2 >= 0)
	{
		if (rs.chged[rs.tmp[0].rs2]) return false;
		rs.RS2 = rs.x[rs.tmp[0].rs2];
	}
	rs.IMM = rs.tmp[0].imm;
	if (rs.tmp[0].rd > 0) rs.chged[rs.tmp[0].rd]++;
	rs.tmp[1] = rs.tmp[0];
	return true;
}
inline bool stage3()
{
	rs.chgPC = rs.tmp[1].chgRD = rs.chgmem = false;

	switch (rs.tmp[1].cas)
	{
	case 1:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.IMM;
		break;
	case 2:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.PC + rs.IMM;
		break;
	case 3:
		rs.tmp[1].chgRD = true;
		rs.chgPC = true;
		rs.RD = rs.PC + rs.IMM - 4;
		rs.tmp[1].rdval = rs.PC;
		break;
	case 4:
		rs.tmp[1].chgRD = true;
		rs.chgPC = true;
		rs.RD = rs.RS1 + rs.IMM;
		rs.tmp[1].rdval = rs.PC;
		break;
	case 5:
		if (rs.RS1 == rs.RS2)
		{
			rs.chgPC = true;
			rs.RD = rs.PC + rs.IMM - 4;
		}
		break;
	case 6:
		if (rs.RS1 != rs.RS2)
		{
			rs.chgPC = true;
			rs.RD = rs.PC + rs.IMM - 4;
		}
		break;
	case 7:
		if (rs.RS1 < rs.RS2)
		{
			rs.chgPC = true;
			rs.RD = rs.PC + rs.IMM - 4;
		}
		break;
	case 8:
		if (rs.RS1 >= rs.RS2)
		{
			rs.chgPC = true;
			rs.RD = rs.PC + rs.IMM - 4;
		}
		break;
	case 9:
		if (uint(rs.RS1) < uint(rs.RS2))
		{
			rs.chgPC = true;
			rs.RD = rs.PC + rs.IMM - 4;
		}
		break;
	case 10:
		if (uint(rs.RS1) >= uint(rs.RS2))
		{
			rs.chgPC = true;
			rs.RD = rs.PC + rs.IMM - 4;
		}
		break;
	case 11:
		rs.tmp[1].chgRD = true;
		rs.chgmem = true;
		rs.RS1 += rs.IMM;
		rs.chgmemtype = 2;
		break;
	case 12:
		rs.tmp[1].chgRD = true;
		rs.chgmem = true;
		rs.RS1 += rs.IMM;
		rs.chgmemtype = 1;
		break;
	case 13:
		rs.tmp[1].chgRD = true;
		rs.chgmem = true;
		rs.RS1 += rs.IMM;
		rs.chgmemtype = 0;
		break;
	case 14:
		rs.tmp[1].chgRD = true;
		rs.chgmem = true;
		rs.RS1 += rs.IMM;
		rs.chgmemtype = 4;
		break;
	case 15:
		rs.tmp[1].chgRD = true;
		rs.chgmem = true;
		rs.RS1 += rs.IMM;
		rs.chgmemtype = 3;
		break;
	case 16:
		rs.chgmem = true;
		rs.RS1 += rs.IMM;
		rs.chgmemtype = 7;
		break;
	case 17:
		rs.chgmem = true;
		rs.RS1 += rs.IMM;
		rs.chgmemtype = 6;
		break;
	case 18:
		rs.chgmem = true;
		rs.RS1 += rs.IMM;
		rs.chgmemtype = 5;
		break;
	case 19:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.RS1 + rs.IMM;
		break;
	case 20:
		rs.tmp[1].chgRD = true;
		if (rs.RS1 < rs.IMM) rs.tmp[1].rdval = 1;
		else rs.tmp[1].rdval = 0;
		break;
	case 21:
		rs.tmp[1].chgRD = true;
		if (uint(rs.RS1) < uint(rs.IMM)) rs.tmp[1].rdval = 1;
		else rs.tmp[1].rdval = 0;
		break;
	case 22:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.IMM ^ rs.RS1;
		break;
	case 23:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.IMM | rs.RS1;
		break;
	case 24:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.IMM & rs.RS1;
		break;
	case 25:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = uint(rs.RS1) << rs.IMM;
		break;
	case 26:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = uint(rs.RS1) >> rs.IMM;
		break;
	case 27:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.RS1 >> rs.IMM;
		break;
	case 28:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.RS1 + rs.RS2;
		break;
	case 29:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.RS1 - rs.RS2;
		break;
	case 30:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = uint(rs.RS1) << getseg(rs.RS2, 0, 4);
		break;
	case 31:
		rs.tmp[1].chgRD = true;
		if (rs.RS1 < rs.RS2) rs.tmp[1].rdval = 1;
		else rs.tmp[1].rdval = 0;
		break;
	case 32:
		rs.tmp[1].chgRD = true;
		if (uint(rs.RS1) < uint(rs.RS2)) rs.tmp[1].rdval = 1;
		else rs.tmp[1].rdval = 0;
		break;
	case 33:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.RS1 ^ rs.RS2;
		break;
	case 34:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = uint(rs.RS1) >> getseg(rs.RS2, 0, 4);
		break;
	case 35:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.RS1 >> getseg(rs.RS2, 0, 4);
		break;
	case 36:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.RS1 | rs.RS2;
		break;
	case 37:
		rs.tmp[1].chgRD = true;
		rs.tmp[1].rdval = rs.RS1 & rs.RS2;
		break;
	default:
		break;
	}
	rs.tmp[2] = rs.tmp[1];
	return true;
}
inline int stage4()
{
	static int cnt = -1;
	if (rs.chgmem)
	{
		if (cnt == -1)
		{
			cnt = 3;
			return -2;
		}
		else if (cnt == 2)
		{
			if (rs.chgmemtype == 0) rs.tmp[2].rdval = readnum(rs.RS1, 32);
			else if (rs.chgmemtype == 1) rs.tmp[2].rdval = readnum(rs.RS1, 16);
			else if (rs.chgmemtype == 2) rs.tmp[2].rdval = readnum(rs.RS1, 8);
			else if (rs.chgmemtype == 3) rs.tmp[2].rdval = readnumU(rs.RS1, 16);
			else if (rs.chgmemtype == 4) rs.tmp[2].rdval = readnumU(rs.RS1, 8);
			else if (rs.chgmemtype == 5) writenum(rs.RS1, 32, rs.RS2);
			else if (rs.chgmemtype == 6) writenum(rs.RS1, 16, getseg(rs.RS2, 0, 15));
			else if (rs.chgmemtype == 7) writenum(rs.RS1, 8, getseg(rs.RS2, 0, 7));
			cnt = -1;
		}
		else
		{
			cnt--;
			return -2;
		}
	}
	if (rs.chgPC)
	{
		rs.PC = rs.RD;
		rs.tmp[3] = rs.tmp[2];
		return rs.PC;
	}

	rs.tmp[3] = rs.tmp[2];
	return -1;
}
inline bool stage5()
{
	if (rs.tmp[3].chgRD&&rs.tmp[3].rd>0)//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		rs.x[rs.tmp[3].rd] = rs.tmp[3].rdval;
		rs.chged[rs.tmp[3].rd]--;
	}
	return true;
}
int run()
{
	/*rs.x[1] = 1;
	rs.x[2] = 2;
	rs.x[3] = 3;
	rs.x[4] = 1791;
	rs.x[10] = 10;*/



	rs.PC = 0;
	while (stage1())
	{
		
		stage2();
		stage3();
		while (stage4() == -2);
		stage5();


		/*instruction ins = rs.tmp[3];
		cout <<rs.PC<<" : "<< ins.cas << " " << int(ins.imm) << " " << ins.rs1 << " " << ins.rs2 << " " << ins.rd<<endl;
		if (rs.PC == 4364)
			puts("fuck");*/
		/*printf("%d ", rs.PC);
		for (int i = 0; i < 32; i++)
			printf("%d ", rs.x[i]);
		puts("");*/
	}
	return ((unsigned int)rs.x[10]) &255u;
}