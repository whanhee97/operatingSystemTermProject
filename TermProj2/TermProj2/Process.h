#pragma once
#include<iostream>
using namespace std;


/**
	���μ��� Ŭ����
	������� �����ϱ� ������ public���� ���� - ��ǻ� ����ü�� �ٸ� ����.
*/

class Process
{	
public:
	int num; // ���μ��� �ѹ�
	double ArrivalT;
	double BurstT;
	double WaitT;


	Process();
	Process(int n, double at,double bt);
	void TimeDown(); // ����Ʈ Ÿ���� ���ҽ�Ŵ
	void Wait(); // ����Ʈ Ÿ���� ������Ŵ
	bool operator<(const Process& p); // �ּ� ������ ����Ʈ Ÿ�Ӱ� �񱳸� ���� ������ �����ε�
	friend ostream& operator<<(ostream& os, const Process& p); // cout�� ���� ������ �����ε�

};
