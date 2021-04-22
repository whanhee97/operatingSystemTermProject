#pragma once
#include<string>
#include<iostream>
using namespace std;

class pcb
{
private:
	int pid;
	pcb* pointer;
	string processState; // new, running, waiting, ready, terminated

public:
	pcb(int pid);
	pcb(int pid, pcb* pointer, string processState);
	pcb(const pcb& p);
	void speakMyState();
	void setPid(int pid);
	void setProcessState(string processState);
	void setPointer(pcb* pointer);
	int getPid();
	string getProcessState();
	pcb* getPointer();
};

