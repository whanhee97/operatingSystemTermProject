#pragma once
#include<iostream>
using namespace std;
#define MAX 10


/**
	FCFS클래스 구현
	원형 큐로 구현. 큐자체가 FSFC 성질을 띔.
	Round Robin의 경우 round() 라는 함수를 통해 맨 앞 프로세스를 맨뒤로 보냄
*/

template<class T>
class FCFS
{
private:
	int front;
	int rear;
	int size;
	T* arr;

public:
	FCFS();
	~FCFS();

	void push(T value);
	T& pop();
	T& runningProcess();
	bool isEmpty();
	bool isFull();
	void CPUrun();
	void showAll();
	int getSize();
	void round(); // RR을 위한 라운드

};

template<class T>
inline FCFS<T>::FCFS()
{
	size = 0;
	arr = new T[MAX];
	front = 0;
	rear = 0;
}

template<class T>
inline FCFS<T>::~FCFS()
{
	delete[] arr;
}

template<class T>
inline void FCFS<T>::push(T value)
{
	if (!isFull())
	{
		arr[rear] = value;
		rear = (rear + 1) % MAX;
		size++;
	}
	else {
		cout << "Queue is Full" << endl;
	}
		

}

template<class T>
inline T& FCFS<T>::pop()
{
	if (!isEmpty()) {
		T temp = arr[front];
		front = (front + 1) % MAX;
		size--;
		return temp;
	}
	else {
		cout << "Queue is Empty" << endl;
		T temp;
		return temp;

	}
}

template<class T>
inline T& FCFS<T>::runningProcess()
{
	if (size == 0) {
		T temp;
		return temp;
	}
	return arr[front];
}

template<class T>
inline bool FCFS<T>::isEmpty()
{
	if (rear == front)
		return true;
	else
		return false;
}

template<class T>
inline bool FCFS<T>::isFull()
{
	if ((rear + 1) % MAX == front)
		return true;
	else
		return false;
}

template<class T>
inline void FCFS<T>::CPUrun()
{
	int iter = front;
	arr[front].TimeDown();
	iter = (iter + 1) % MAX;
	while (iter != rear) {
		arr[iter].Wait();
		iter = (iter + 1) % MAX;
	}
}

template<class T>
inline void FCFS<T>::showAll()
{
	int iter = front;

	
	if (!isEmpty()) {
		while (1) {
			cout << arr[iter] << " ";
			iter = (iter + 1) % MAX;
			if (iter == rear) { break; }
		}
	}
	cout << endl;
	
}

template<class T>
inline int FCFS<T>::getSize()
{
	return size;
}

template<class T>
inline void FCFS<T>::round()
{
	T temp = this->pop();
	this->push(temp);

	cout << endl << "round!!!!" << endl;
}
