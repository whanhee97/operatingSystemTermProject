#pragma once
#include"pcb.h"
class Queue
{
private:
	pcb* head;
	pcb* tail;

public:
	Queue();
	void push(pcb& p1);
	pcb& pop();
	void printAll();

};

