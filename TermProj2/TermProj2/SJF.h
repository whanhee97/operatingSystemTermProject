#pragma once
#include<iostream>
#define MAX 10
using namespace std;

/**
	SJFŬ���� ����
	�켱 ����ť(Heap)�� Burst time ���� �ּ� ��
*/


template<class T>
class SJF
{
	T* heap;
	int size;

public:
	SJF();
	~SJF();

	void push(T value);
	T& pop();
	T& runningProcess();
	void CPUrun();
	void showAll();
	int getSize();
	
};

template<class T>
inline SJF<T>::SJF()
{
	heap = new T[MAX];
	size = 0;
}

template<class T>
inline SJF<T>::~SJF()
{
	delete[] heap;
}

template<class T>
inline void SJF<T>::push(T value)
{
	size++;
	heap[size] = value;
	
	int child = size;
	int parent = child/2;
	while (child > 1 && heap[child] < heap[parent]) {
		T temp = heap[parent];
		heap[parent] = heap[child];
		heap[child] = temp;

		child = parent;
		parent = child / 2;
	}
	if (heap[1].num == value.num && size != 1) { //ó�� ���°� �ٷ� �Ǿ��� �Ǹ� wait time�� 0���� �����ؾ���(�� �� ó������ Ǫ���� ��� ����)
		heap[1].Wait();
	}
}

template<class T>
inline T& SJF<T>::pop()
{
	T result = heap[1];
	
	T temp = heap[1];
	heap[1] = heap[size];
	heap[size] = temp;

	size--;

	int parent = 1;
	int child = parent * 2;
	if (child + 1 <= size) {
		child = (heap[child] < heap[child + 1]) ? child : child + 1; // ���� ������ ���ؼ� ������ �ڽ����� ��
	}

	while (child <= size && heap[child] < heap[parent]) {
		T temp = heap[parent];
		heap[parent] = heap[child];
		heap[child] = temp;
		
		parent = child;
		child = child * 2;
		if (child + 1 <= size) {
			child = (heap[child] < heap[child + 1]) ? child : child + 1; // ���� ������ ���ؼ� ������ �ڽ����� ��
		}
	}
	
	return result;
}

template<class T>
inline T& SJF<T>::runningProcess()
{
	if (size == 0) {
		T temp;
		return temp;
	}
	return heap[1];
}

template<class T>
inline void SJF<T>::CPUrun()
{
	heap[1].TimeDown();
	if (size >= 2) {
		for (int i = 2; i <= size; i++) {
			heap[i].Wait();
		}
	}
}

template<class T>
inline void SJF<T>::showAll()
{
	for (int i = 1; i <= size; i++) {
		cout << heap[i] << " ";
	}
	cout << endl;
}

template<class T>
inline int SJF<T>::getSize()
{
	return size;
}
