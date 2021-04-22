#include "Process.h"
#include "Process.h"

Process::Process()
{
	this->num = 0;
	this->ArrivalT = 0;
	this->BurstT = 0;
	this->WaitT = 0;
}

Process::Process(int n, double at, double bt)
{
	this->num = n;
	this->ArrivalT = at;
	this->BurstT = bt;
	this->WaitT = -1;
}

void Process::TimeDown()
{
	this->BurstT -= 1;
}

void Process::Wait()
{
	this->WaitT += 1;
}
bool Process::operator<(const Process& p)
{
	if (this->BurstT < p.BurstT) {
		return true;
	}
	else {
		return false;
	}
}
ostream& operator<<(ostream& os, const Process& p)
{
	os << "[P" << p.num << ", AT:" << p.ArrivalT << ", BT:" << p.BurstT << ", WT:" << p.WaitT << "]";
	return os;
}
