#include "XeASM.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys\stat.h>
#include "XeASM_Error.h"

#define OPCODE_NOPARAM	0
#define OPCODE_1PARAM	1
#define OPCODE_2PARAMS	2
#define OPCODE_LABEL	3

struct OpCodeStruct
{
	// Esempio su mov #1, ax
	char *text;		// Testo dell'opcode. Es. mov
	char opcode;	// Codice operativo. Es 08
	char params;	// Numero dei parametri. Es 2
};

OpCodeStruct opcodetable[] =
{
	"mov",		0x01, OPCODE_2PARAMS,
	"move",		0x01, OPCODE_2PARAMS,
	"lea",		0x02, OPCODE_2PARAMS,
	"address",	0x02, OPCODE_2PARAMS,
	"nop",		0x03, OPCODE_NOPARAM,
	"noop",		0x03, OPCODE_NOPARAM,
	"jmp",		0x04, OPCODE_LABEL,
	"jump",		0x04, OPCODE_LABEL,
	"cal",		0x05, OPCODE_LABEL,
	"call",		0x05, OPCODE_LABEL,
	"ret",		0x06, OPCODE_NOPARAM,
	"return",	0x06, OPCODE_NOPARAM,
	"end",		0x07, OPCODE_NOPARAM,
	"add",		0x08, OPCODE_2PARAMS,
	"sub",		0x09, OPCODE_2PARAMS,
	"mul",		0x0A, OPCODE_2PARAMS,
	"div",		0x0B, OPCODE_2PARAMS,
	"mod",		0x0C, OPCODE_2PARAMS,
	"flip",		0x0D, OPCODE_1PARAM,
	"inc",		0x0E, OPCODE_1PARAM,
	"dec",		0x0F, OPCODE_1PARAM,
	"and",		0x10, OPCODE_2PARAMS,
	"or",		0x11, OPCODE_2PARAMS,
	"xor",		0x12, OPCODE_2PARAMS,
	"not",		0x13, OPCODE_1PARAM,
	"shl",		0x14, OPCODE_2PARAMS,
	"shiftl",	0x14, OPCODE_2PARAMS,
	"shr",		0x15, OPCODE_2PARAMS,
	"shiftr",	0x15, OPCODE_2PARAMS,
	"gbt",		0x16, OPCODE_2PARAMS,
	"getbit",	0x16, OPCODE_2PARAMS,
	"sbt",		0x17, OPCODE_2PARAMS,
	"setbit",	0x17, OPCODE_2PARAMS,
	"zer",		0x18, OPCODE_1PARAM,
	"zero",		0x18, OPCODE_1PARAM,
	"sin",		0x19, OPCODE_1PARAM,
	"cos",		0x1A, OPCODE_2PARAMS,
	"tg",		0x1B, OPCODE_2PARAMS,
	"ctg",		0x1C, OPCODE_2PARAMS,
	"cotg",		0x1C, OPCODE_2PARAMS,
	"rnd",		0x1D, OPCODE_2PARAMS,
	"rand",		0x1D, OPCODE_2PARAMS,
	"jz",		0x1E, OPCODE_NOPARAM,
	"jzero",	0x1E, OPCODE_NOPARAM,
	"jnz",		0x1F, OPCODE_NOPARAM,
	"jnzero",	0x1F, OPCODE_NOPARAM,
	"je",		0x20, OPCODE_LABEL,
	"jne",		0x21, OPCODE_LABEL,
	"jg",		0x22, OPCODE_LABEL,
	"jge",		0x23, OPCODE_LABEL,
	"jl",		0x24, OPCODE_LABEL,
	"jle",		0x25, OPCODE_LABEL,
	"lop",		0x26, OPCODE_LABEL,
	"loop",		0x26, OPCODE_LABEL,
	"loj",		0x27, OPCODE_LABEL,
	"looj",		0x27, OPCODE_LABEL,
	"cmp",		0x28, OPCODE_2PARAMS,
	"compare",	0x28, OPCODE_2PARAMS,
	"cmb",		0x29, OPCODE_2PARAMS,
	"compareb",	0x29, OPCODE_2PARAMS,
	"psh",		0x2A, OPCODE_1PARAM,
	"push",		0x2A, OPCODE_1PARAM,
	"pop",		0x2B, OPCODE_1PARAM,
	"op2C",		0x2C, OPCODE_NOPARAM,
	"op2D",		0x2D, OPCODE_NOPARAM,
	"op2E",		0x2E, OPCODE_NOPARAM,
	"op2F",		0x2F, OPCODE_NOPARAM,
	"op30",		0x30, OPCODE_NOPARAM,
};

enum LexMode
{
	LexMode_Normal,
	LexMode_CatchWord,
	LexMode_CatchOpCode,
	LexMode_CatchOpCodeParam1,
	LexMode_CatchOpCodeComma,
	LexMode_CatchOpCodeParam2,
	LexMode_CatchOpCodeLabel,
	LexMode_Comment,
};

XeASM::XeASM()
{
	out = NULL;
	lasterror = 0;
	filename = "out";
}
XeASM::~XeASM()
{

}

char *XeASM::GetLastError()
{
	for(int i=0; i<sizeof(xeasm_error_entries) / sizeof(XeASM_Error); i++)
	{
		if (xeasm_error_entries[i].error == lasterror)
			return xeasm_error_entries[i].string;
	}
	return "GetLastError WTF?";
}
bool XeASM::SetLastError(int error)
{
	lasterror = error;
	return false;
}
bool XeASM::LoadFromFile(char *filename)
{
	FILE *f = NULL;
	struct stat fileInfo;
	char *mem;
	int bytesreaded;

	if (stat(filename, &fileInfo))
		return SetLastError(XeASM_Error_STATFAIL);
	if (fopen_s(&f, filename, "r"))
		return SetLastError(XeASM_Error_FOPENFAIL);
	if (!(mem = (char*)malloc(fileInfo.st_size + 1)))
	{
		fclose(f);
		return SetLastError(XeASM_Error_MALLOCFAIL);
	}
	bytesreaded = fread(mem, 1, fileInfo.st_size, f);
	mem[bytesreaded] = 0;
	this->filename = filename;
	return LoadFromMemory(mem);
}
bool XeASM::LoadFromMemory(char *sourcecode)
{
	lex.filename = this->filename;
	lex.pos = sourcecode;
	lex.end = sourcecode + strlen(sourcecode);
	lex.source = lex.pos;
	lex.lines = 0;
	lex.charpos = 0;
	lex.mode = LexMode_Normal;
	return Compile(&lex) != 0;
}
bool XeASM::SaveToFile(char *filename)
{
	FILE *f;
	if (fopen_s(&f, filename, "w+b")) return false;
	fwrite(out, 1, pc, f);
	fclose(f);
	return true;
}
void *XeASM::GetMachineCode()
{
	return out;
}

//////////////////////////////////////////////////////////////////////////
struct ASMOpCodeParam
{
	union
	{
		unsigned char p;
		struct  
		{
			unsigned char type1		: 2;
			unsigned char access1	: 2;
			unsigned char type2		: 2;
			unsigned char access2	: 2;
		};
	};
};
int XeASM::Hash(char *string)
{
	int r = 0;
	for(int i=0; *string; i++, string++)
	{
		r ^= *string << 24;
		r ^= *string << 16;
		r ^= *string << 8;
		r ^= *string;
		for(int v=0; v<4; v++)
		{
			r = 2 * r ^ 0x4C11DB5;
		}
	}
	return r;
}
int XeASM::GetOpcodeSize(OpCodeContainer *c)
{
	int n=2;
	int nx;
	for(nx=0; opcodetable[nx].opcode != c->opcode; nx++);
	if (opcodetable[nx].params == OPCODE_LABEL)
		n = 3;
	else if (opcodetable[nx].params == OPCODE_NOPARAM)
		n = 1;
	else
	{
		switch(((ASMOpCodeParam*)&c->param)->type1)
		{
		case 1:	n++;	break;
		case 2:	n+=2;	break;
		case 3:	n+=4;	break;
		}
		switch(((ASMOpCodeParam*)&c->param)->type2)
		{
		case 1:	n++;	break;
		case 2:	n+=2;	break;
		case 3:	n+=4;	break;
		}
	}
	return n;
}
int XeASM::Compile(LexStat *lex)
{
	lex->mode = LexMode_Normal;
	lex->lines = 0;
	lex->charpos = 0;
	if (Analyze(lex) != 1) return 0;
	printf("Analyze completed!\n");
	if (Assemble(lex) != 1) return 0;
	printf("Compilation completed!\n");
	return 1;
}
int XeASM::Assemble(LexStat *lex)
{
	if (out) free(out);
	out = (unsigned char*)malloc(pc);

	OpCodeContainer cont;
	OpCodeContainer *contx;
	LabelContainer label;
	labelList.First();
	while(labelList.Next(&label))
	{
		opcodeList.First();
		while(contx = opcodeList.GetNext())
		{
			if (contx->labelhash == label.labelhash)
			{
				contx->n1 = label.position;
			}
		}
	}

	opcodeList.First();
	ASMOpCodeParam cicici;
	int tmp = 0;
	for(int i=0, n; opcodeList.Next(&cont); i+=GetOpcodeSize(&cont))
	{
		out[i+0] = cont.opcode;
		for(n=0; opcodetable[n].opcode != out[i+0]; n++);
		switch(opcodetable[n].params)
		{
		case 0: // NULLA! XD
			break;
		case 1: // 1 param
			out[i+1] = cont.param;
			cicici.p = cont.param;
			switch(cicici.type1)
			{
			case 1: *(char*)(out+i+2) = cont.n1;
				break;
			case 2: *(short*)(out+i+2) = cont.n1;
				break;
			case 3: *(int*)(out+i+2) = cont.n1;
				break;
			}
			break;
		case 2: // 2 params
			out[i+1] = cont.param;
			cicici.p = cont.param;
			switch(cicici.type1)
			{
			case 1: *(char*)(out+i+2) = cont.n1;
				tmp = 1;
				break;
			case 2: *(short*)(out+i+2) = cont.n1;
				tmp = 2;
				break;
			case 3: *(int*)(out+i+2) = cont.n1;
				tmp = 4;
				break;
			}
			switch(cicici.type2)
			{
			case 1: *(char*)(out+i+2+tmp) = cont.n2;
				break;
			case 2: *(short*)(out+i+2+tmp) = cont.n2;
				break;
			case 3: *(int*)(out+i+2+tmp) = cont.n2;
				break;
			}
			break;
		case 3: // 3 label
			out[i+1] = cont.n1 & 0xFF;
			out[i+2] = cont.n1 >> 8;
			break;
		}
	}
	return 1;
}
int XeASM::Analyze(LexStat *lex)
{
	unsigned char o = 0;
	char c;
	char *w;
	int n;
	int n1, n2;
	ASMOpCodeParam param;
	OpCodeContainer cont;

	pc = 0;
	while(lex->pos != lex->end)
	{
		if (0)
		{
lex_analyze_redo:
			lex->charpos++;
			lex->pos++;
		}
		c = *lex->pos;
		
		switch(c)
		{
		case 0:
			return true;
		case '\n': // New line
			if (lex->mode == LexMode_Comment)
			{
				lex->mode = LexMode_Normal;
			}
			if (o != 0)
			{
				cont.labelhash = 0;
				for(n=0; opcodetable[n].opcode != o; n++);
				switch(opcodetable[n].params)
				{
				case OPCODE_NOPARAM:
					if (lex->mode != LexMode_CatchOpCode)
						SetLastError(XeASM_Assembly_OPCODEACCEPTZEROPARAMS);
					param.p = 0;
					break;
				case OPCODE_1PARAM:
					if (lex->mode != LexMode_CatchOpCodeParam1)
						SetLastError(XeASM_Assembly_OPCODEACCEPTONEPARAM);
					param.access2 = param.type2 = 0;
					break;
				case OPCODE_2PARAMS:
					if (lex->mode != LexMode_CatchOpCodeParam2)
						SetLastError(XeASM_Assembly_OPCODEACCEPTTWOPARAMS);
					break;
				case OPCODE_LABEL:
					if (lex->mode != LexMode_CatchOpCode)
						SetLastError(XeASM_Assembly_OPCODEACCEPTLABEL);
					param.type1 = 2;
					param.access1 = 1;
					param.access2 = param.type2 = 0;
					n1 = n2 = 0;
					cont.labelhash = Hash(w);
					break;
				}
				cont.opcode = o;
				cont.param = param.p;
				cont.n1 = n1;
				cont.n2 = n2;
				pc += GetOpcodeSize(&cont);
				opcodeList.Add(cont);
			}
			lex->mode = LexMode_Normal;
			lex->charpos = -1;
			lex->lines++;
		case ' ':
		case '\t':
			lex->charpos++;
			lex->pos++;
			break;
		case ':':
			if (lex->mode == LexMode_Comment) goto lex_analyze_redo;
			if (lex->mode == LexMode_CatchWord)
			{
				lex->charpos++;
				lex->pos++;
				LabelContainer label;
				label.labelhash = Hash(w);
				label.position = pc;
				labelList.Add(label);
				lex->mode = LexMode_Normal;
			}
			else 
				return SetLastError(XeASM_Assembly_COLONUNEXCEPTED);
			break;
		case '$': // Address
			if (lex->mode == LexMode_Comment) goto lex_analyze_redo;
			if (lex->mode != LexMode_CatchOpCodeComma && lex->mode != LexMode_CatchOpCode)
				return SetLastError(XeASM_Assembly_PARAM2UNEXCEPTED);
			lex->charpos++;
			lex->pos++;
			if (!ConvertWordAsNumber(lex, &n))
				return SetLastError(XeASM_Assembly_NOTANUMBER);
			if (lex->mode == LexMode_CatchOpCode)
			{
				n1 = n;
				param.access1 = 1;
				if (abs(n) < 0x100)
					param.type1 = 1;
				else if (abs(n) < 0x10000)
					param.type1 = 2;
				else
					param.type1 = 3;
				lex->mode = LexMode_CatchOpCodeParam1;
			}
			else if (lex->mode == LexMode_CatchOpCodeComma)
			{
				n2 = n;
				param.access2 = 1;
				if (n < 0x100)
					param.type2 = 1;
				else if (n < 0x10000)
					param.type2 = 2;
				else
					param.type2 = 3;
				lex->mode = LexMode_CatchOpCodeParam2;
			}
			break;
		case '#': // Const
			if (lex->mode == LexMode_Comment) goto lex_analyze_redo;
			if (lex->mode == LexMode_CatchOpCodeComma)
			{
				lex->charpos++;
				lex->pos++;
				if (!ConvertWordAsNumber(lex, &n))
					return SetLastError(XeASM_Assembly_NOTANUMBER);
				if (lex->mode == LexMode_CatchOpCodeComma)
				{
					n2 = n;
					param.access2 = 0;
					if (n < 0x100)
						param.type2 = 1;
					else if (n < 0x10000)
						param.type2 = 2;
					else
						param.type2 = 3;
					lex->mode = LexMode_CatchOpCodeParam2;
				}
				else
				{
					SetLastError(XeASM_Assembly_CONSTUNEXCEPTED);
				}
			}
			else 
				return SetLastError(XeASM_Assembly_PARAMUNEXCEPTED);
			break;
		case ',': // Params separator
			if (lex->mode == LexMode_Comment) goto lex_analyze_redo;
			if (lex->mode != LexMode_CatchOpCodeParam1)
				return SetLastError(XeASM_Assembly_PARAM2UNEXCEPTED);
			lex->charpos++;
			lex->pos++;
			lex->mode = LexMode_CatchOpCodeComma;
			// Const
			break;
		case ';':
			lex->mode = LexMode_Comment;
			lex->charpos++;
			lex->pos++;
			break;
		default:
			if (lex->mode == LexMode_Comment) goto lex_analyze_redo;
			w = GetWord(lex);
			if (!w)
			{
				switch(lex->mode)
				{
				case LexMode_Normal:
					break;
				case LexMode_CatchOpCode:
					break;
				}
			}
			else if (lex->mode == LexMode_Normal)
			{
				lex->mode = LexMode_CatchWord;
				if ((o = GetOpCode(w)) != 0)
				{
					lex->mode = LexMode_CatchOpCode;
					param.p = 0;
				}
			}
		}
	}
	return 1;
}
char *XeASM::GetWord(LexStat *lex)
{
	int size;
	char *startpos = lex->pos;
	while(isalnum(*lex->pos))
	{
		lex->charpos++;
		lex->pos++;
	}
	size = lex->pos - startpos;
	if (size == 0) return NULL;
	memcpy_s(buf, sizeof(buf) - 1, startpos, size);
	buf[size] = 0;
	return buf;
}
int XeASM::GetOpCode(char *w)
{
	for(int i=0; i<sizeof(opcodetable) / sizeof(OpCodeStruct); i++)
	{
		if (strcmp(opcodetable[i].text, w) == 0)
		{
			return opcodetable[i].opcode;
		}
	}
	return 0;
}

bool XeASM::ConvertWordAsNumber(LexStat *lex, int *n)
{
	bool hex = false;
	bool dodo = true;
	char *w = GetWord(lex);
	if (!w) return false;

	if (*w == 'x')
	{
		hex = true;
		w++;
	}

	if (hex)
	{
		char *wx = w;
		while(*w)
		{
			*w++ = tolower(*w);
		}
		sscanf_s(wx, "%x", n);
	}
	else
	{
		char *wx = w;
		while(*w)
		{
			if (isdigit(*w++) == 0)
				return false;
		}
		*n = atoi(wx);
	}
	return true;
}