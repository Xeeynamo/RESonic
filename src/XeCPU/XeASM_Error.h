#pragma once

#define XEASM_ERROR_ENTRIES	30

enum XeASM_Error
{
	XeASM_Error_NOERROR			= 0,
	XeASM_Error_NOTIMPLEMENTED,
	XeASM_Error_FOPENFAIL,
	XeASM_Error_FREADFAIL,
	XeASM_Error_FWRITEFAIL,
	XeASM_Error_STATFAIL,
	XeASM_Error_MALLOCFAIL,
	XeASM_Assembly_RETURNUNEXCEPTED,
	XeASM_Assembly_COLONUNEXCEPTED,
	XeASM_Assembly_PARAM2UNEXCEPTED,
	XeASM_Assembly_PARAMUNEXCEPTED,
	XeASM_Assembly_CONSTUNEXCEPTED,
	XeASM_Assembly_NOTANUMBER,
	XeASM_Assembly_OPCODEACCEPTZEROPARAMS,
	XeASM_Assembly_OPCODEACCEPTONEPARAM,
	XeASM_Assembly_OPCODEACCEPTTWOPARAMS,
	XeASM_Assembly_OPCODEACCEPTLABEL,
	XeASM_Assembly_COMMENTUNEXCEPTED,
};

struct XeASM_ErrorEntry
{
	XeASM_Error error;
	char *string;
};

extern XeASM_ErrorEntry xeasm_error_entries[XEASM_ERROR_ENTRIES];