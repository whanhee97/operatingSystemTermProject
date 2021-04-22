#include "pcb.h"
pcb::pcb(int pid) {
	this->pid = pid;
	this->pointer = NULL;
	this->processState = "new";
}
pcb::pcb(int pid, pcb* pointer, string processState) {
	this->pid = pid;
	this->pointer = pointer;
	this->processState = processState;
}

pcb::pcb(const pcb& p)
{
	pid = p.pid;
	pointer = NULL;
	processState = p.processState;
}

void pcb::speakMyState() {
	cout << this->pid << "(PID) is now " << this->processState << "(state)" << endl;
}

void pcb::setPid(int pid) {
	this->pid = pid;
}
void pcb::setProcessState(string processState) {
	this->processState = processState;
}
void pcb::setPointer(pcb* pointer) {
	this->pointer = pointer;
}

int pcb::getPid() {
	return this->pid;
}
string pcb::getProcessState() {
	return this->processState;
}
pcb* pcb::getPointer() {
	return this->pointer;
}