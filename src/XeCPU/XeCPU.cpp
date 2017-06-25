//////////////////////////////////////////////////////////////////////////
//
// Opcode format:
//  iiii iiii ttvv ttvv
//
// i = istruzione
// t = tipo parametro
// v = accesso parametro 
//
// Tipi:
//  char
//  short
//  int
//  non usato
// Accessi:
//  diretto
//  indiretto
//  esterno
//  non usato
//////////////////////////////////////////////////////////////////////////

#include "XeCPU.h"
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 64

#define OPCODE_NOPARAM	0
#define OPCODE_1PARAM	1
#define OPCODE_2PARAMS	2
#define OPCODE_LABEL	3
unsigned char opcodelength[][2] =
{
	0x00, 0,
	0x01, OPCODE_2PARAMS,
	0x02, OPCODE_2PARAMS,
	0x03, OPCODE_NOPARAM,
	0x04, OPCODE_LABEL,
	0x05, OPCODE_LABEL,
	0x06, OPCODE_NOPARAM,
	0x07, OPCODE_NOPARAM,
	0x08, OPCODE_2PARAMS,
	0x09, OPCODE_2PARAMS,
	0x0A, OPCODE_2PARAMS,
	0x0B, OPCODE_2PARAMS,
	0x0C, OPCODE_2PARAMS,
	0x0D, OPCODE_1PARAM,
	0x0E, OPCODE_1PARAM,
	0x0F, OPCODE_1PARAM,
	0x10, OPCODE_2PARAMS,
	0x11, OPCODE_2PARAMS,
	0x12, OPCODE_2PARAMS,
	0x13, OPCODE_1PARAM,
	0x14, OPCODE_2PARAMS,
	0x15, OPCODE_2PARAMS,
	0x16, OPCODE_2PARAMS,
	0x17, OPCODE_2PARAMS,
	0x18, OPCODE_1PARAM,
	0x19, OPCODE_1PARAM,
	0x1A, OPCODE_2PARAMS,
	0x1B, OPCODE_2PARAMS,
	0x1C, OPCODE_2PARAMS,
	0x1D, OPCODE_2PARAMS,
	0x1E, OPCODE_NOPARAM,
	0x1F, OPCODE_NOPARAM,
	0x20, OPCODE_LABEL,
	0x21, OPCODE_LABEL,
	0x22, OPCODE_LABEL,
	0x23, OPCODE_LABEL,
	0x24, OPCODE_LABEL,
	0x25, OPCODE_LABEL,
	0x26, OPCODE_LABEL,
	0x27, OPCODE_LABEL,
	0x28, OPCODE_2PARAMS,
	0x29, OPCODE_2PARAMS,
	0x2A, OPCODE_1PARAM,
	0x2B, OPCODE_1PARAM,
	0x2C, OPCODE_NOPARAM,
	0x2D, OPCODE_NOPARAM,
	0x2E, OPCODE_NOPARAM,
	0x2F, OPCODE_NOPARAM,
	0x30, OPCODE_NOPARAM,
};

XeCPU::XeCPU()
{

}
XeCPU::~XeCPU()
{

}

void XeCPU::Load(char *filename)
{

}
void XeCPU::Load(void *memory)
{
	Reset();
	code = (unsigned char*)memory;
	cpu.Status.execute = 1;
}
void XeCPU::Init()
{

}
void XeCPU::Clean()
{
	memset(&cpu, 0, sizeof(cpu));
}
void XeCPU::Reset()
{
	Clean();
	Init();
}
void XeCPU::Push(int, int size)
{

}
void XeCPU::Pop(char*, int size)
{

}
bool XeCPU::Run()
{
	if (!code) return false;
	if (!cpu.Status.execute) return false;

	while(cpu.Status.retfunc == 0)
	{
		opcode = code[cpu.pc++];
		if (opcodelength[opcode][1] == 1 || opcodelength[opcode][1] == 2)
		{
			param.p = code[cpu.pc++];
			ReadParams(&n1, &n2);
			if (cpu.Status.outofmem)
				return false;
		}
		else if (opcodelength[opcode][1] == 3)
		{
			ReadParams(&n1, &n2);
		}

		switch(opcode)
		{
		case 0x01: // MOV
			n1 = n2;
			break;
		case 0x02: // LEA
			n1 = param2Pos;
			break;
		case 0x03: // NOOP
			__noop;
			break;
		case 0x04: // JMP
			cpu.pc = n1;
			break;
		case 0x05: // CALL
			Push(cpu.pc, 2);
			cpu.pc = n1;
			break;
		case 0x06: // RET
			Pop((char*)&cpu.pc, 2);
			break;
		case 0x07: // END
			cpu.Status.execute = 0;
			return false;
		case 0x08: // ADD
			if (( n1+=n2 )==0) cpu.Status.zero = 1;
			else cpu.Status.zero = 0;
			break;
		case 0x09: // SUB
			if (( n1-=n2 )==0) cpu.Status.zero = 1;
			else cpu.Status.zero = 0;
			break;
		case 0x0A: // MUL
			if (( n1*=n2 )==0) cpu.Status.zero = 1;
			else cpu.Status.zero = 0;
			break;
		case 0x0B: // DIV
			if (( n1/=n2 )==0) cpu.Status.zero = 1;
			else cpu.Status.zero = 0;
			break;
		case 0x0C: // MOD
			if (( n1%=n2 )==0) cpu.Status.zero = 1;
			else cpu.Status.zero = 0;
			break;
		case 0x0D: // FLIP
			cpu.Status.zero = (n1 = -n1) == 0;
			break;
		case 0x0E: // INC
			if (( ++n1 )==0) cpu.Status.zero = 1;
			else cpu.Status.zero = 0;
			break;
		case 0x0F: // DEC
			if (( --n1 )==0) cpu.Status.zero = 1;
			else cpu.Status.zero = 0;
			break;

		case 0x18: // ZERO
			n1 = 0;
			cpu.Status.zero = 1;
			break;
		}
		WriteParam(n1);
	}
	return true;
}

void XeCPU::ReadParams(int *n1, int *n2)
{
	switch(opcodelength[opcode][1])
	{
	case OPCODE_2PARAMS:
		*n1 = GetParam(param.type1);
		switch(param.access1)
		{
		case 0:	// Diretto
			break;
		case 1: // Indiretto (indirizzamento)
			param1Pos = *n1;
			if (*n1 >= sizeof(cpu.mem))
			{
				cpu.Status.outofmem = 1;
				return;
			}
			*n1 = cpu.mem[*n1];
			break;
		case 2: // Esterno
			break;
		case 3: // Unused
			break;
		}
		*n2 = GetParam(param.type2);
		switch(param.access2)
		{
		case 0:	// Diretto
			break;
		case 1: // Indiretto (indirizzamento)
			param2Pos = *n2;
			if (*n2 >= sizeof(cpu.mem))
			{
				cpu.Status.outofmem = 1;
				return;
			}
			*n2 = cpu.mem[*n2];
			break;
		case 2: // Esterno
			break;
		case 3: // Unused
			break;
		}
		break;
	case OPCODE_1PARAM:
		*n1 = GetParam(param.type1);
		switch(param.access1)
		{
		case 0:	// Diretto
			break;
		case 1: // Indiretto (indirizzamento)
			param1Pos = *n1;
			*n1 = cpu.mem[*n1];
			break;
		case 2: // Esterno
			break;
		case 3: // Unused
			break;
		}
		break;
	case OPCODE_LABEL:
		*n1 = GetParam(2);
		break;
	}
}
void XeCPU::WriteParam(int n)
{
	if (opcodelength[opcode][1] == 0 || opcodelength[opcode][1] == 3) return;
	switch(param.access1)
	{
	case 0:
		break;
	case 1:
		switch(param.type1)
		{
		case 1:
			*(cpu.mem + param1Pos) = n;
			break;
		case 2:
			*(short*)(cpu.mem + param1Pos) = n;
			break;
		case 3:
			*(int*)(cpu.mem + param1Pos) = n;
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	}
}
int XeCPU::GetParam(unsigned char type)
{
	switch(type)
	{
	case 1:
		return code[cpu.pc++];
	case 2:
		cpu.pc += 2;
		return *(short*)(code + cpu.pc - 2);
	case 3:
		cpu.pc += 4;
		return *(int*)(code + cpu.pc - 4);
	}
	return 0;
}