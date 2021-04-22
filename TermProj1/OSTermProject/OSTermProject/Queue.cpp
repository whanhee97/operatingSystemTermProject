#include "Queue.h"
Queue::Queue() {
	this->head = NULL;
	this->tail = NULL;
}

void Queue::push(pcb& p1) {
	if (this->head == NULL) {
		this->head = &p1;
		this->tail = &p1;
		p1.setPointer(NULL);
	}
	else {
		pcb* temp;
		temp = this->head;
		this->head = &p1;
		p1.setPointer(temp);
	}

}

pcb& Queue::pop() {
	
	pcb* iter = head;
	pcb* temp;
	if (iter->getPointer() == NULL) { // 1개 있을때
		this->head = NULL;
		temp = this->tail;
		this->tail = NULL;
		return *temp;
	}
	if (iter == NULL) { // 아무것도 없을 때
		return *iter;
	}
	while (iter->getPointer() != tail) { // 그 외
		iter = iter->getPointer();
	}
	temp = this->tail;
	this->tail = iter;
	iter->setPointer(NULL);
	return *temp;
}

void Queue::printAll() {
	pcb* iter = this->head;
	if (iter == NULL) {
		cout << "큐가 비었습니다." << endl;
		return;
	}
	while (iter != NULL) {
		cout <<"[PID]" <<iter->getPid() <<"("<<iter->getProcessState()<<")"<< " ";
		iter = iter->getPointer();
	}
	cout << endl;
}
