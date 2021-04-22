#include "Program.h"
int Program::pid = 0;
pcb Program:: makeProcess() {
	pid++;
	pcb* nPCB = new pcb(pid);
	return *nPCB;
}
void Program::ProgramStart()
{

}
