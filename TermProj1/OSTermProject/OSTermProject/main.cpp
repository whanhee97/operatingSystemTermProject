#include<iostream>
#include<Windows.h>
#include"Queue.h"
using namespace std;

void runningState(Queue& jq, Queue& rq, Queue& dq1, Queue& dq2, pcb* cpu);
int main() {
	Queue jobQueue;
	Queue readyQueue;
	Queue keyboardQueue;
	Queue mouseQueue;
	pcb* runningPCB = NULL; // CPU���� �������� ���μ���
	pcb* temp;
	

	for (int i = 1; i <= 7; i++) { //��ť�� ���μ����� ����
		pcb* temp = new pcb(i);
		jobQueue.push(*temp);
		runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);
		
	}

	
	cout << endl << "job queue -> ready queue " << endl << endl;
	Sleep(1000);

	for (int i = 1; i <= 4; i++) { //����ť�� ��ġ
		
		temp = &jobQueue.pop();
		temp->setProcessState("ready");
		readyQueue.push(*temp);
		runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);
	}

	///// ���� ���� /////////

	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////////////////////////

	for (int i = 0; i < 3; i++) {
		cout << "timer interupt occur!" << endl << endl; // Ÿ�̸� ���ͷ�Ʈ �߻�
		Sleep(1000);

		runningPCB->setProcessState("ready"); // ������·� �ٲٰ�
		readyQueue.push(*runningPCB); // �ٽ� ����ť�� ��
		runningPCB = &readyQueue.pop();
		runningPCB->setProcessState("running");
		runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);
	}


	//////Ű���� �Է¹߻�
	cout << "keyboard input occur! (CPU -> Keyboar Queue)" << endl<< endl; // Ű���� �Է� �߻�
	Sleep(1000);

	runningPCB->setProcessState("waiting"); // waiting ���·� �ٲٰ�
	keyboardQueue.push(*runningPCB); // Ű���� ť�� ��
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////���μ��� ����
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	// ��ť���� �ϳ� ��������
	temp = &jobQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);


	cout << "keyboard input complete! (Keyboar Queue -> Ready Queue)" << endl << endl; // Ű���� �Է� �Ϸ�
	Sleep(1000);
	temp = &keyboardQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	cout << "Mouse input occur! (CPU -> Mouse Queue)" << endl << endl; // ���콺 �Է� �߻�
	Sleep(1000);
	runningPCB->setProcessState("waiting"); // waiting ���·� �ٲٰ� 
	mouseQueue.push(*runningPCB);
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	cout << "Mouse input occur! (CPU -> Mouse Queue)" << endl << endl; // ���콺 �Է� �߻�
	Sleep(1000);
	runningPCB->setProcessState("waiting"); // waiting ���·� �ٲٰ� 
	mouseQueue.push(*runningPCB);
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	cout << "Mouse input complete! (Mouse Queue -> Ready Queue)" << endl << endl; // ���콺 �Է� �Ϸ�
	Sleep(1000);
	temp = &mouseQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);


	/////���μ��� ����
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	// ��ť���� �ϳ� ��������
	temp = &jobQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);


	/////���μ��� ����
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	// ��ť���� �ϳ� �������� -> ��ť�� ��� PCB ����ť�� ������
	temp = &jobQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB); 


	cout << "Mouse input complete! (Mouse Queue -> Ready Queue)" << endl << endl; // ���콺 �Է� �Ϸ�
	Sleep(1000);
	temp = &mouseQueue.pop();
	temp->setProcessState("ready");
	readyQueue.push(*temp);
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////���μ��� ����
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////���μ��� ����
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ�
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////���μ��� ����
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB;
	runningPCB = &readyQueue.pop();
	runningPCB->setProcessState("running"); // ���׻��·� �ٲٰ� -> ����ť�� �ִ� ��� PCB �����
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	/////���μ��� ����
	runningPCB->setProcessState("terminated");
	runningPCB->speakMyState();
	cout << endl;
	Sleep(1000);
	delete runningPCB; // ��� PCB ����
	runningPCB = NULL;
	runningState(jobQueue, readyQueue, keyboardQueue, mouseQueue, runningPCB);

	return 0;
}

void runningState(Queue& jq, Queue& rq, Queue& dq1, Queue& dq2, pcb* cpu) {
	if (cpu != NULL) {
		cout << "Running : [PID]" << cpu->getPid() << "("<< cpu->getProcessState() << ")" << endl;
	}
	else {
		cout << "Running : "<< endl;
	}
	cout << "Ready Queue : "; rq.printAll();
	cout << "Keyboard Queue : "; dq1.printAll();
	cout << "Mouse Queue : "; dq2.printAll();
	cout << "Job Queue : "; jq.printAll();
	cout << endl;
	Sleep(1000);
}