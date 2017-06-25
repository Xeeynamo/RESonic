#include "XeASM_Error.h"

XeASM_ErrorEntry xeasm_error_entries[XEASM_ERROR_ENTRIES] =
{
	XeASM_Error_NOERROR, "No error",
	XeASM_Error_NOTIMPLEMENTED, "Not implemented",
	XeASM_Error_FOPENFAIL, "fopen fail",
	XeASM_Error_FREADFAIL, "fread fail",
	XeASM_Error_FWRITEFAIL, "fwrite fail",
	XeASM_Error_STATFAIL, "stat fail",
	XeASM_Error_MALLOCFAIL, "malloc fail",

	XeASM_Assembly_RETURNUNEXCEPTED, "return unexcepted",
	XeASM_Assembly_COLONUNEXCEPTED, "colon unexcepted",
	XeASM_Assembly_PARAM2UNEXCEPTED, "param 2 unexcepted",
	XeASM_Assembly_PARAMUNEXCEPTED, "param unexcepted",
	XeASM_Assembly_CONSTUNEXCEPTED, "can't use a const as destination",
	XeASM_Assembly_NOTANUMBER, "not a number",
	XeASM_Assembly_OPCODEACCEPTZEROPARAMS, "the opcode doesn't accept params",
	XeASM_Assembly_OPCODEACCEPTONEPARAM, "the opcode accept only one param",
	XeASM_Assembly_OPCODEACCEPTTWOPARAMS, "the opcode accept only two params",
	XeASM_Assembly_OPCODEACCEPTLABEL, "the opcode accept only labels",
	XeASM_Assembly_COMMENTUNEXCEPTED, "comment unexcepted",

};
