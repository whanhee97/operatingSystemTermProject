#pragma once
#include<iostream>
using namespace std;


/**
	프로세스 클래스
	멤버변수 접근하기 쉽도록 public으로 구현 - 사실상 구조체나 다름 없음.
*/

class Process
{	
public:
	int num; // 프로세스 넘버
	double ArrivalT;
	double BurstT;
	double WaitT;


	Process();
	Process(int n, double at,double bt);
	void TimeDown(); // 버스트 타임을 감소시킴
	void Wait(); // 웨이트 타임을 증가시킴
	bool operator<(const Process& p); // 최소 힙에서 버스트 타임값 비교를 위한 연산자 오버로딩
	friend ostream& operator<<(ostream& os, const Process& p); // cout을 위한 연산자 오버로딩

};
