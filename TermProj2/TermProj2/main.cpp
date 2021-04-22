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
	�����Լ�
	
	for ���� ���Ͽ� time�� �帥�ٰ� �����ϰ� showProgress �Լ��� ���� �ð����� ���¸� ������� 
	
	�����̳� ���ο� ù��° ���μ����� �������� ���μ����� ������.
	runningProcess() �Լ��� ���� ��������(�Ǿ���) ���μ����� ������.

	���μ����� ���ȣ([]) �� ��� [���μ����̸�, Arrival time, Burst time, Wait time] �������� ����Ͽ� ������.

	���μ����� ����Ʈ Ÿ���� ������ terminated ť�� ��.

	������ ������ ���������� ��� Wait time �����.
*/


int main() {

	Process p1(1, 0, 10); // ���μ����ѹ�, Arrival, Burst (Wait�� -1�� �׻� �ʱ�ȭ)
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

	

	//FCFS ����
	FCFS <Process> fcfs;
	FCFS <Process> terminated;

	cout << endl << endl <<"------------------------------------  FCFS  ---------------------------------------------" << endl;
	cout << "<< AT : Arrival Time, BT : Burst Time, WT : Waiting Time >>" << endl<<endl;
	for (time = 0; time < 55; time++) {
		for (int i = 0; i < 6; i++) {
			if (processList[i].ArrivalT == time) {
				if (i == 0) {
					processList[i].WaitT = 0; // ��ó�� ���μ����� waiting time�� ó���� - 1 �� �������־����Ƿ� �ϳ� �÷���
				}
				fcfs.push(processList[i]);
			}
		}
		if (time == 0) {
			FCFS_showProgress(time, fcfs, terminated); // FCFS���� �����ִ� �Լ�
			continue;
		}
		if (fcfs.runningProcess().BurstT > 0) { // �������� ���μ����� ����ƮŸ���� �����ִٸ�
			fcfs.CPUrun(); // FCFS ť�� ù��° ���μ��� ����Ʈ �ð� ����, ������ ���μ������� waiting time ����
		}
		else { //�������� ���μ����� ����ƮŸ���� �� ������
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
		sum += terminated.pop().WaitT; // ���� ���μ��� ť���� �ϳ��� ������ waiting time�� �� ����
	}
	Average = sum / 6; // 6���� ������ ��� ����
	cout << "FCFS ��� waiting time : " << Average << endl;




	//SJF ����
	SJF<Process> sjf;
	FCFS <Process> terminated2;
	cout <<endl<<endl << endl << endl << endl <<"------------------------------------  SJF  ---------------------------------------------" << endl;
	cout << "<< AT : Arrival Time, BT : Burst Time, WT : Waiting Time >>" << endl<<endl;
	for (time = 0; time < 60; time++) {
		for (int i = 0; i < 6; i++) {
			if (processList[i].ArrivalT == time) { // ���� arrival time �� �Ǹ� sjf�� Ǫ��
				if (i == 0) {
					processList[i].WaitT = 0; // ��ó�� ���μ����� waiting time�� ó���� - 1 �� �������־����Ƿ� �ϳ� �÷���
				}
				sjf.push(processList[i]);
			}
		}
		
		if (time == 0) {
			SJF_showProgress(time, sjf, terminated2);
			continue;
		}

		if (sjf.runningProcess().BurstT > 0) { // ����Ʈ Ÿ���� �� �� ������ 
			sjf.CPUrun(); // ù��° ���μ���(�������� ���μ���) ����Ʈ Ÿ�� ������ ������ ���μ����� ������ Ÿ�� �ø���
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
	cout << "SJF ��� waiting time : " << Average << endl;
	




	//RR ���� - FCFS Ŭ���� Ȱ���Ͽ� round��� �޼ҵ常 �߰��Ͽ� ����.
	FCFS<Process> RR;
	FCFS <Process> terminated3;


	cout << endl << endl << endl << endl << endl << "------------------------------------  RR  ---------------------------------------------" << endl;
	cout << "<< AT : Arrival Time, BT : Burst Time, WT : Waiting Time >>" << endl << endl;
	for (time = 0; time < 55; time++) {
		for (int i = 0; i < 6; i++) {
			if (processList[i].ArrivalT == time) {
				if (i == 0) {
					processList[i].WaitT = 0; // ��ó�� ���μ����� waiting time�� ó���� - 1 �� �������־����Ƿ� �ϳ� �÷���(���ö��� wait time �����ϸ� �ȵǹǷ�)
				}
				RR.push(processList[i]);
			}
		}
		if (time == 0) {
			RR_showProgress(time, RR, terminated3); // RR���� �����ִ� �Լ�
			continue;
		}
		if (roundCnt >= TimeQuantum && RR.runningProcess().BurstT != 0) { // ���� ī���Ͱ� 3�̰� ����ƮŸ���� �� �ȵ����� ����

			RR.round();
			roundCnt = 0;
		}
		if (RR.runningProcess().BurstT > 0) { // �������� ���μ����� ����ƮŸ���� �����ִٸ�

			RR.CPUrun(); // FCFS ť�� ù��° ���μ��� ����Ʈ �ð� ����, ������ ���μ������� waiting time ����
			roundCnt++;
		}
		else { //�������� ���μ����� ����ƮŸ���� �� ������
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
	cout << "RR ��� waiting time : " << Average << endl;

	return 0;
}