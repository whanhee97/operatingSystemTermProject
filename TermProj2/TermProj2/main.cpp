#pragma once
#include"Process.h"
#include"FCFS.h"
#include"SJF.h"
#define TimeQuantum 3

void FCFS_showProgress(double time,FCFS<Process>& fcfs, FCFS<Process>& terminated) {
	cout << "time : " << time << "------------------------" << endl;
	cout << "running process : " << fcfs.runningProcess() << endl;
	cout << "FCFS : ";
	fcfs.showAll();
	cout << "terminated : ";
	terminated.showAll();
	cout << "-------------------------------" << endl;
}

void SJF_showProgress(double time, SJF<Process>& sjf, FCFS<Process>& terminated) {
	cout << "time : " << time << "------------------------" << endl;
	cout << "running process : " << sjf.runningProcess() << endl;
	cout << "sjf : ";
	sjf.showAll();
	cout << "terminated : ";
	terminated.showAll();
	cout << "-------------------------------" << endl;
}

void RR_showProgress(double time, FCFS<Process>& fcfs, FCFS<Process>& terminated) {
	cout << "time : " << time << "------------------------" << endl;
	cout << "running process : " << fcfs.runningProcess() << endl;
	cout << "RR : ";
	fcfs.showAll();
	cout << "terminated : ";
	terminated.showAll();
	cout << "-------------------------------" << endl;
}


/**
	메인함수
	
	for 문을 통하여 time이 흐른다고 가정하고 showProgress 함수를 통해 시간마다 상태를 출력해줌 
	
	컨테이너 내부에 첫번째 프로세스가 실행중인 프로세스로 가정함.
	runningProcess() 함수를 통해 실행중인(맨앞의) 프로세스를 보여줌.

	프로세스는 대괄호([]) 로 묶어서 [프로세스이름, Arrival time, Burst time, Wait time] 형식으로 출력하여 보여줌.

	프로세스의 버스트 타임이 끝나면 terminated 큐에 들어감.

	각각의 구현부 마지막에는 평균 Wait time 출력함.
*/


int main() {

	Process p1(1, 0, 10); // 프로세스넘버, Arrival, Burst (Wait은 -1로 항상 초기화)
	Process p2(2, 3, 12);
	Process p3(3, 7, 4);
	Process p4(4, 10, 6);
	Process p5(5, 14, 8);
	Process p6(6, 15, 7);
	Process processList[6] = { p1,p2,p3,p4,p5,p6 };
	

	double time;
	double sum;
	double Average;
	int roundCnt = 0;

	

	//FCFS 구현
	FCFS <Process> fcfs;
	FCFS <Process> terminated;

	cout << endl << endl <<"------------------------------------  FCFS  ---------------------------------------------" << endl;
	cout << "<< AT : Arrival Time, BT : Burst Time, WT : Waiting Time >>" << endl<<endl;
	for (time = 0; time < 55; time++) {
		for (int i = 0; i < 6; i++) {
			if (processList[i].ArrivalT == time) {
				if (i == 0) {
					processList[i].WaitT = 0; // 맨처음 프로세스만 waiting time을 처음에 - 1 로 설정해주었으므로 하나 올려줌
				}
				fcfs.push(processList[i]);
			}
		}
		if (time == 0) {
			FCFS_showProgress(time, fcfs, terminated); // FCFS과정 보여주는 함수
			continue;
		}
		if (fcfs.runningProcess().BurstT > 0) { // 실행중인 프로세스가 버스트타임이 남아있다면
			fcfs.CPUrun(); // FCFS 큐의 첫번째 프로세스 버스트 시간 감소, 나머지 프로세스들의 waiting time 증가
		}
		else { //실행중인 프로세스가 버스트타임을 다 썼으면
			Process temp = fcfs.pop();
			terminated.push(temp);
			fcfs.CPUrun();
			
		}
		FCFS_showProgress(time, fcfs, terminated);	
		if (fcfs.getSize() == 0) {
			break;
		}
	}
	sum = 0;
	for (int j = 0; j < 6; j++) {
		sum += terminated.pop().WaitT; // 종료 프로세스 큐에서 하나씩 꺼내서 waiting time을 다 더함
	}
	Average = sum / 6; // 6으로 나눠서 평균 구함
	cout << "FCFS 평균 waiting time : " << Average << endl;




	//SJF 구현
	SJF<Process> sjf;
	FCFS <Process> terminated2;
	cout <<endl<<endl << endl << endl << endl <<"------------------------------------  SJF  ---------------------------------------------" << endl;
	cout << "<< AT : Arrival Time, BT : Burst Time, WT : Waiting Time >>" << endl<<endl;
	for (time = 0; time < 60; time++) {
		for (int i = 0; i < 6; i++) {
			if (processList[i].ArrivalT == time) { // 만약 arrival time 이 되면 sjf에 푸쉬
				if (i == 0) {
					processList[i].WaitT = 0; // 맨처음 프로세스만 waiting time을 처음에 - 1 로 설정해주었으므로 하나 올려줌
				}
				sjf.push(processList[i]);
			}
		}
		
		if (time == 0) {
			SJF_showProgress(time, sjf, terminated2);
			continue;
		}

		if (sjf.runningProcess().BurstT > 0) { // 버스트 타임이 다 안 됐으면 
			sjf.CPUrun(); // 첫번째 프로세스(실행중인 프로세스) 버스트 타임 내리고 나머지 프로세스들 웨이팅 타임 올리고
		}
		else { 
			Process temp = sjf.pop();
			terminated2.push(temp);
			sjf.CPUrun();
		}
		SJF_showProgress(time, sjf, terminated2);
		if (sjf.getSize()== 0) {
			break;
		}
	}
	sum = 0;
	for (int j = 0; j < 6; j++) {
		sum += terminated2.pop().WaitT;
	}
	Average = sum / 6;
	cout << "SJF 평균 waiting time : " << Average << endl;
	




	//RR 구현 - FCFS 클래스 활용하여 round라는 메소드만 추가하여 구현.
	FCFS<Process> RR;
	FCFS <Process> terminated3;


	cout << endl << endl << endl << endl << endl << "------------------------------------  RR  ---------------------------------------------" << endl;
	cout << "<< AT : Arrival Time, BT : Burst Time, WT : Waiting Time >>" << endl << endl;
	for (time = 0; time < 55; time++) {
		for (int i = 0; i < 6; i++) {
			if (processList[i].ArrivalT == time) {
				if (i == 0) {
					processList[i].WaitT = 0; // 맨처음 프로세스만 waiting time을 처음에 - 1 로 설정해주었으므로 하나 올려줌(들어올때는 wait time 증가하면 안되므로)
				}
				RR.push(processList[i]);
			}
		}
		if (time == 0) {
			RR_showProgress(time, RR, terminated3); // RR과정 보여주는 함수
			continue;
		}
		if (roundCnt >= TimeQuantum && RR.runningProcess().BurstT != 0) { // 라운드 카운터가 3이고 버스트타임이 다 안됐으면 라운드

			RR.round();
			roundCnt = 0;
		}
		if (RR.runningProcess().BurstT > 0) { // 실행중인 프로세스가 버스트타임이 남아있다면

			RR.CPUrun(); // FCFS 큐의 첫번째 프로세스 버스트 시간 감소, 나머지 프로세스들의 waiting time 증가
			roundCnt++;
		}
		else { //실행중인 프로세스가 버스트타임을 다 썼으면
			Process temp = RR.pop();
			terminated3.push(temp);
			RR.CPUrun();
			roundCnt = 1;
		}
		RR_showProgress(time, RR, terminated3);
		if (RR.getSize() == 0) {
			break;
		}
	}
	sum = 0;
	for (int j = 0; j < 6; j++) {
		sum += terminated3.pop().WaitT;
	}
	Average = sum / 6;
	cout << "RR 평균 waiting time : " << Average << endl;

	return 0;
}