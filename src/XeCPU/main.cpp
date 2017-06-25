#include <stdio.h>
#include <stdlib.h>
#include "XeASM.h"
#include "XeCPU.h"

int Main()
{
	char *srcFileName = "test.asm";
	char *dstMachineCode = "test.bin";
	XeASM a;
	XeCPU cpu;

	if (!a.LoadFromFile(srcFileName))
		return printf("%s on %s", a.GetLastError(), srcFileName);
	if (!a.SaveToFile(dstMachineCode))
		return printf("%s on %s", a.GetLastError(), dstMachineCode);

	cpu.Load(a.GetMachineCode());
	cpu.Run();
	printf("%04X", *(short*)cpu.cpu.mem);

	return 0;
}

int main()
{
	Main();
	system("pause>nul");
}